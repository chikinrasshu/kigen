# chkKigen

Simple 2D engine for testing

Uses vcpkg for dependencies, and cmake for building.

Ensure that `VCPKG_ROOT` environment variable is set before building,
and that `CMAKE_TOOLCHAIN_FILE` points to `%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake`
Then run cmake as always.
