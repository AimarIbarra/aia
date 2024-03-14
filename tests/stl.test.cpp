#include <catch2/catch_test_macros.hpp>

#include <aia/vector.hpp>
#include <aia/forward_list.hpp>
#include <aia/deque.hpp>
#include <aia/list.hpp>

#include <aia/set.hpp>
#include <aia/map.hpp>

#include <aia/unordered_map.hpp>
#include <aia/unordered_set.hpp>

#include <aia/stack.hpp>
#include <aia/queue.hpp>

aia::Arena arena;

TEST_CASE("Works with std::vector") {
    auto alloc = arena.make_allocator<int>();
    aia::vector<int> v(alloc);
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
    }
    for (int i = 0; i < 1000; ++i) {
        REQUIRE(v[i] == i);
    }
}

TEST_CASE("Works with std::forward_list") {
    auto alloc = arena.make_allocator<int>();
    aia::forward_list<int> l(alloc);
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

TEST_CASE("Works with std::list") {
    auto alloc = arena.make_allocator<int>();
    aia::list<int> l(alloc);
    for (int i = 0; i < 1000; ++i) {
        l.push_back(i);
    }
    int i = 0;
    for (auto n : l) {
        REQUIRE(n == i);
        ++i;
    }
    REQUIRE(i == 1000);
}

TEST_CASE("Works with std::deque") {
    auto alloc = arena.make_allocator<int>();
    aia::deque<int> d(alloc);
    for (int i = 0; i < 1000; ++i) {
        d.push_back(i);
    }
    int i = 0;
    for (auto n : d) {
        REQUIRE(n == i);
        ++i;
    }
    REQUIRE(i == 1000);
}

TEST_CASE("Works with std::set") {
    auto alloc = arena.make_allocator<int>();
    aia::set<int> s(alloc);
    for (int i = 0; i < 1000; ++i) {
        s.insert(i);
    }
    for (int i = 0; i < 1000; ++i) {
        REQUIRE(s.find(i) != s.end());
    }
}

TEST_CASE("Works with std::multiset") {
    auto alloc = arena.make_allocator<int>();
    aia::multiset<int> ms(alloc);
    for (int i = 0; i < 1000; ++i) {
        ms.insert(i);
    }
    for (int i = 0; i < 1000; ++i) {
        REQUIRE(ms.count(i) == 1);
    }
}

TEST_CASE("Works with std::map") {
    auto alloc = arena.make_allocator<int>();
    aia::map<int, int> m(alloc);
    for (int i = 0; i < 1000; ++i) {
        m.emplace(i, i * 2);
    }
    for (int i = 0; i < 1000; ++i) {
        REQUIRE(m[i] == i * 2);
    }
}

TEST_CASE("Works with std::multimap") {
    auto alloc = arena.make_allocator<int>();
    aia::map<int, int> mm(alloc);
    for (int i = 0; i < 1000; ++i) {
        mm.emplace(i, i * 2);
    }
    for (int i = 0; i < 1000; ++i) {
        REQUIRE(mm.count(i) == 1);
    }
}

TEST_CASE("Works with std::unordered_set") {
    auto alloc = arena.make_allocator<int>();
    aia::unordered_set<int> s(alloc);
    for (int i = 0; i < 1000; ++i) {
        s.insert(i);
    }
    for (int i = 0; i < 1000; ++i) {
        REQUIRE(s.find(i) != s.end());
    }
}

TEST_CASE("Works with std::unordered_multiset") {
    auto alloc = arena.make_allocator<int>();
    aia::unordered_multiset<int> ms(alloc);
    for (int i = 0; i < 1000; ++i) {
        ms.insert(i);
    }
    for (int i = 0; i < 1000; ++i) {
        REQUIRE(ms.count(i) == 1);
    }
}

TEST_CASE("Works with std::unordered_map") {
    auto alloc = arena.make_allocator<int>();
    aia::unordered_map<int, int> m(alloc);
    for (int i = 0; i < 1000; ++i) {
        m.emplace(i, i * 2);
    }
    for (int i = 0; i < 1000; ++i) {
        REQUIRE(m[i] == i * 2);
    }
}

TEST_CASE("Works with std::unordered_multimap") {
    auto alloc = arena.make_allocator<int>();
    aia::unordered_map<int, int> mm(alloc);
    for (int i = 0; i < 1000; ++i) {
        mm.emplace(i, i * 2);
    }
    for (int i = 0; i < 1000; ++i) {
        REQUIRE(mm.count(i) == 1);
    }
}

TEST_CASE("Works with std::stack") {
    auto alloc = arena.make_allocator<int>();
    aia::stack<int> s(alloc);
    for (int i = 0; i < 1000; ++i) {
        s.emplace(i);
    }
    int i = 1000;
    while (!s.empty()) {
        --i;
        REQUIRE(s.top() == i);
        s.pop();
    }
    REQUIRE(i == 0);
}

TEST_CASE("Works with std::queue") {
    auto alloc = arena.make_allocator<int>();
    aia::queue<int> q(alloc);
    for (int i = 0; i < 1000; ++i) {
        q.emplace(i);
    }
    int i = 0;
    while (!q.empty()) {
        REQUIRE(q.front() == i);
        q.pop();
        ++i;
    }
    REQUIRE(i == 1000);
}

TEST_CASE("Works with std::priority_queue") {
    auto alloc = arena.make_allocator<int>();
    aia::priority_queue<int> q(alloc);
    for (int i = 0; i < 1000; ++i) {
        q.emplace(i);
    }
    int i = 1000;
    while (!q.empty()) {
        --i;
        REQUIRE(q.top() == i);
        q.pop();
    }
    REQUIRE(i == 0);
}