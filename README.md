# `transmogrify`

> Hook a `void(*)()` function by re-writing its assembly code at runtime.

It currently only has support for overriding functions like the ones generated
by my compiler version. You can only install one hook. See the `example.cpp`.

# Build instructions

This project uses `vcpkg` for managing its dependencies. Build it with:

```
$ ./vcpkg/boostrap-vcpkg.sh
$ ./vcpkg/vcpkg install fmt
$ cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build
$ cd build && ctest
```
