#pragma once

namespace transmogrify {
    using void_function = void(*)();

    bool hook(void_function target,
              void_function hook);
}
