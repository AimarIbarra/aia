#include <aia.hpp>
#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <forward_list>

using namespace aia;

Arena arena;

TEST_CASE("Works with std::vector") {
    auto alloc = arena.make_allocator<int>();
    std::vector<int, decltype(alloc)> v(alloc);
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
    }
    for (int i = 0; i < 1000; ++i) {
        REQUIRE(v[i] == i);
    }
}

TEST_CASE("Works with std::forward_list") {
    auto alloc = arena.make_allocator<int>();
    std::forward_list<int, decltype(alloc)> l(alloc);
        for (int i = 0; i < 1000; ++i) {
        l.push_front(i);
    }
    int i = 1000;
    for (auto n : l) {
        --i;
        REQUIRE(n == i);
    }
    REQUIRE(i == 0);
}