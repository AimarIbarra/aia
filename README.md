# Aimar Ibarra's Arena (AIA)
This is a simple implementation of a memory arena, alongside it's respective allocator.
Written in C++ for C++.

## Install
Use CMake:
```cmake
add_subdirectory(<PATH_TO_THIS_PROJECT>)
target_link_libraries(<YOUR_EXECUTABLE> aia)
```

## Usage
```c++
#include <aia/aia.hpp>

int main() {
    aia::Arena arena;
    aia::ArenaAllocator alloc = arena.make_allocator<int>();

    int *number = alloc.allocate(1);
    int *array = alloc.allocate(10);
    // `number` and `array` are freed when the destructor of `arena` is called
    //  unless the arena is moves elsewhere
}
```

Additionally you may use the allocator with any stl contatiners:
```c++
#include <aia/aia.hpp>

int main() {
    aia::Arena arena;
    auto alloc = arena.make_allocator<int>();
    std::vector<int, aia::ArenaAllocator<int>> vec(alloc);
    std::forward_list<int, decltype(alloc)> list(alloc);
}
```

Or you could use the aliases provided for all stl containers defined in C++11:
```c++
#include <aia/vector.hpp>

int main() {
    aia::Arena arena;
    auto alloc = arena.make_allocator<int>();
    aia::vector<int> vec(alloc);
    vec.push_back(3);
}
```

## Documentation
The file `include/aia/aia.hpp` is documented with doxygen style comments.

## License
GPL3, see `LICENSE`.
