add_library(transmogrify
  transmogrify.cpp
  stub.s)

target_include_directories(transmogrify
  PUBLIC .)

target_link_libraries(transmogrify PRIVATE fmt::fmt)
