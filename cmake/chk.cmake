include_guard()

include(CMakeParseArguments)
include(GenerateExportHeader)

function(chk_check_var VAR NAME)
  if(NOT DEFINED ${VAR})
    message(FATAL_ERROR "${NAME} is required")
  endif()
endfunction()

function(chk_check_var_or VAR NAME DEFAULT)
  if(NOT DEFINED ${VAR})
    set(${VAR} ${DEFAULT} PARENT_SCOPE)
  endif()
endfunction()

function(chk_check_var_list VAR NAME OPTIONS)
  if(NOT DEFINED ${VAR})
    message(FATAL_ERROR "${NAME} is required")
  endif()

  if(NOT ${VAR} IN_LIST OPTIONS)
    message(FATAL_ERROR "${NAME} must be one of: ${OPTIONS}")
  endif()
endfunction()

function(chk_add)
  cmake_parse_arguments(CHK "" "NAME;KIND;PREFIX;PREFIX_SEP;SRCBASE;BINBASE" "SRC;HDR;PUB;PRV" ${ARGN})

  chk_check_var(CHK_NAME NAME)
  chk_check_var_list(CHK_KIND KIND "lib;exe")
  chk_check_var_or(CHK_PREFIX PREFIX "chk")
  chk_check_var_or(CHK_PREFIX_SEP PREFIX_SEP "_")
  chk_check_var_or(CHK_SRCBASE SRCBASE "${CMAKE_CURRENT_SOURCE_DIR}")
  chk_check_var_or(CHK_BINBASE BINBASE "${CMAKE_CURRENT_BINARY_DIR}")

  set(CHK_TARGET "${CHK_PREFIX}${CHK_PREFIX_SEP}${CHK_NAME}")
  set(CHK_ALIAS ${CHK_PREFIX}::${CHK_NAME})
  string(TOUPPER ${CHK_NAME} CHK_NAME_UPPER)
  string(TOUPPER ${CHK_PREFIX} CHK_PREFIX_UPPER)
  string(TOUPPER ${CHK_TARGET} CHK_TARGET_UPPER)
  string(TOLOWER ${CHK_PREFIX} CHK_PREFIX_LOWER)
  string(TOLOWER ${CHK_NAME} CHK_NAME_LOWER)

  list(TRANSFORM CHK_SRC PREPEND "${CHK_SRCBASE}/src/${CHK_PREFIX_LOWER}/${CHK_NAME_LOWER}/")
  list(TRANSFORM CHK_HDR PREPEND "${CHK_SRCBASE}/include/${CHK_PREFIX_LOWER}/${CHK_NAME_LOWER}/")

  if(CHK_KIND STREQUAL "lib")
    add_library(${CHK_TARGET})
    add_library(${CHK_ALIAS} ALIAS ${CHK_TARGET})

    set(CHK_API_DIR "${CHK_BINBASE}/include/${CHK_PREFIX_LOWER}/${CHK_NAME_LOWER}")
    set(CHK_API_HDR "${CHK_API_DIR}/api.h")
    file(MAKE_DIRECTORY ${CHK_API_DIR})
    generate_export_header(${CHK_TARGET}
      EXPORT_FILE_NAME ${CHK_API_HDR}
      EXPORT_MACRO_NAME ${CHK_NAME_UPPER}_API
      NO_EXPORT_MACRO_NAME ${CHK_NAME_UPPER}_LOCAL
    )
    list(APPEND CHK_HDR ${CHK_API_HDR})
  elseif(CHK_KIND STREQUAL "exe")
    add_executable(${CHK_TARGET})

    if(WIN32 AND BUILD_SHARED_LIBS)
      add_custom_target("_${CHK_TARGET}_copy_dlls" ALL
        COMMAND ${CMAKE_COMMAND} -E copy -t
        $<TARGET_FILE_DIR:${CHK_TARGET}>
        $<TARGET_RUNTIME_DLLS:${CHK_TARGET}>
        COMMAND_EXPAND_LISTS
        DEPENDS ${CHK_TARGET}
      )
    endif()
  endif()

  target_sources(${CHK_TARGET}
    PRIVATE ${CHK_SRC}
    PUBLIC FILE_SET "${CHK_TARGET}_hdr" TYPE HEADERS
    BASE_DIRS ${CHK_SRCBASE}/include ${CHK_BINBASE}/include
    FILES ${CHK_HDR}
  )

  target_include_directories(${CHK_TARGET}
    PUBLIC
    $<BUILD_INTERFACE:${CHK_SRCBASE}/include>
    $<BUILD_INTERFACE:${CHK_BINBASE}/include>
    $<INSTALL_INTERFACE:include>
  )

  target_link_libraries(${CHK_TARGET}
    PUBLIC ${CHK_PUB}
    PRIVATE ${CHK_PRV}
  )

  target_compile_features(${CHK_TARGET} PUBLIC c_std_11)
endfunction()
