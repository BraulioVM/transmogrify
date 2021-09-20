# `transmogrify`

> Hook a `void(*)()` function by re-writing its assembly code at runtime.

Caveats:

1. Only x86-64 code is supported.
2. Only one hook can be installed.
3. Only functions with a specific preamble can be hooked
   ```
   endbr64
   push %rbp
   mov %rsp, %rbp
   ```

# Build instructions

This project uses `vcpkg` for managing its dependencies. Build it with:

```
$ ./vcpkg/boostrap-vcpkg.sh
$ ./vcpkg/vcpkg install fmt gtest
$ cmake -S . -B build \
    -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build
$ cd build && ctest
```
