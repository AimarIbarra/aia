# Aimar Ibarra's Arena (AIA)
This is a simple implementation of a memory arena, alongside it's respective allocator.

## Install
Use CMake:
```cmake
add_subdirectory(<PATH_TO_THIS_PROJECT>)
target_link_libraries(<YOUR_EXECUTABLE> aia)
```

## Usage
```c++
int main() {
  aia::Arena arena;
  auto alloc = arena.make_allocator<int>();

  int *number = alloc.allocate(1);
  int *array = alloc.allocate(10);
  // `number` and `array` are freed here
}
```

Additionally you may use the allocator with any stl template:
```c++
auto alloc = arena.make_allocator<int>();
std::vector<int, aia::ArenaAllocator<int>> vec(alloc);
std::forward_list<int, decltype(alloc)> list(alloc);
```

## Documentation
The file `aia.hpp` is documented with doxygen.