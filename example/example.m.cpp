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


