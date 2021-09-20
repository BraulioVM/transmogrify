# `transmogrify`

> Hook a `void(*)()` function by re-writing its assembly code at runtime.

Caveats:

1. Only x86-64 code is supported.
2. Only 4 hooks can be installed. There is no way to uninstall a hook
3. Only functions with a specific preamble can be hooked
   ```
   endbr64
   push %rbp
   mov %rsp, %rbp
   ```

# Example

```c++
#include <transmogrify.h>
#include <fmt/format.h>

void f() {
    fmt::print("executing f\n");
}

void hook() {
    fmt::print("executing hook\n");
}

int main() {
    if (!transmogrify::hook(&f, &hook))
    {
        fmt::print("failed to install hook\n");
    }
    
    f();

    return 0;
}
```

Then

```
$ ./program
executing hook
executing f
$
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
