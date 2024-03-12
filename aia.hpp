#ifndef AALLOC_HPP_INCLUDED_P
#define ALLLOC_HPP_INCLUDED_P

/* This program is free software: you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>. 
 */

/**
  * @author Aimar Ibarra <greenerclay@gmail.com>
  */

#include <forward_list>
#include <memory>

namespace aia {

template <typename T>
class ArenaAllocator;

class Arena {
    struct arena_type {
        void *data;
        arena_type(std::size_t size) : data(::operator new(size)) {}
        ~arena_type() { ::operator delete(data); }
    };

    using arena_pool_type = std::forward_list<arena_type>;

    std::size_t arena_size;
    arena_pool_type arena_pool;
    std::size_t free_space;
    void *current_position;

    void grow() {
        arena_pool.emplace_front(arena_size);
        free_space = arena_size;
        current_position = arena_pool.begin()->data;
    }

    void *emplace(std::size_t size, std::size_t align) {
        arena_pool.emplace_after(arena_pool.begin(), size + align);
        return std::align(align, 1, (++arena_pool.begin())->data, size);
    }

   public:
    Arena(std::size_t size = 65536) : arena_size(size) { grow(); }
    Arena(const Arena &other) = delete;
    Arena &operator=(const Arena &other) = delete;
    Arena(Arena &&arena) {
        arena_size = arena.arena_size;
        free_space = arena.free_space;
        current_position = arena.current_position;
        arena_pool = std::move(arena.arena_pool);
    }
    Arena &operator=(Arena &&arena) {
        arena_size = arena.arena_size;
        free_space = arena.free_space;
        current_position = arena.current_position;
        arena_pool = std::move(arena.arena_pool);
        return *this;
    }

    void set_arena_size(std::size_t newsiz) { arena_size = newsiz; }

    void *allocate(std::size_t size, std::size_t align) {
        if (size + align > arena_size) {
            return emplace(size, align);
        }

        void *ptr = std::align(align, size, current_position, free_space);
        if (!ptr) {
            grow();
            ptr = std::align(align, size, current_position, free_space);
        }
        current_position = static_cast<std::byte *>(current_position) + size;
        free_space -= size;

        return ptr;
    }

    template <typename T>
    ArenaAllocator<T> make_allocator() {
        return ArenaAllocator<T>(*this);
    }
};

template <typename T>
class ArenaAllocator {
    Arena &arena;

   public:
    using allocator_type = ArenaAllocator<T>;
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using void_pointer = void *;
    using const_void_pointer = const void *;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

    using is_always_equal = std::false_type;

    template <typename U>
    using rebind = ArenaAllocator<U>;

    ArenaAllocator(Arena &a) noexcept : arena(a) {}

    template <typename U>
    ArenaAllocator(const ArenaAllocator<U> &other) noexcept
        : ArenaAllocator(other.template duplicate<T>()) {}

    template <typename U>
    ArenaAllocator(ArenaAllocator<U> &&other) noexcept
        : arena(other.template duplicate<T>()) {}

    template <typename U>
    ArenaAllocator<U> duplicate() const {
        return ArenaAllocator<U>(arena);
    }

    T *allocate(size_type n) {
        return static_cast<T *>(arena.allocate(sizeof(T[n]), alignof(T)));
    }

    void deallocate([[maybe_unused]] pointer ptr,
                    [[maybe_unused]] size_type size) {}

    template <typename U>
    constexpr bool operator==(const ArenaAllocator<U> &other) const noexcept {
        return std::addressof(arena) == std::addressof(other.arena);
    }

    template <typename U>
    constexpr bool operator!=(const ArenaAllocator<U> &other) const noexcept {
        return std::addressof(arena) != std::addressof(other.arena);
    }
};

}  // namespace aalloc

#endif
