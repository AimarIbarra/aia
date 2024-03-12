# Aimar Ibarra's Arena (AIA)
This is a simple implementation of a memory arena, alongside it's respective allocator.

## Install
Just copy the header file somewhere in your project, since it is a single header library.

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
The library will be documentated in the near future.
