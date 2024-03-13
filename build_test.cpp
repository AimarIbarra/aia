#include <aia.hpp>

using namespace aia;

int main() {
    Arena a;
    auto alloc = a.make_allocator<int>();
    auto alloc2 = std::move(alloc);
    ArenaAllocator<int> alloc3(std::move(alloc2));
    return 0;
}