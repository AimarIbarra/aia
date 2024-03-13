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

/** @file aia.hpp
  * @brief A simple implementation of an arena allocator.
  * @author Aimar Ibarra <greenerclay@gmail.com>
  */

#include <forward_list>
#include <memory>

/** @namespace aia
  */
namespace aia {

// Forward declaration of the allocator
template <typename T>
class ArenaAllocator;

/** @class Arena
  * @brief The arena that holds the data of the objects.
  */
class Arena {
    /** @struct arena_type
      * @brief Datatype representing one memory arena.
      */
    struct arena_type {
        void *data;
        arena_type(std::size_t size) : data(::operator new(size)) {}
        ~arena_type() { ::operator delete(data); }
    };

    /** @typedef arena_pool_type
      * @brief Chain of different memory arenas.
      */
    using arena_pool_type = std::forward_list<arena_type>;

    /** @brief The size used to create new memory arenas.
      */
    std::size_t arena_size;

    /** @brief Chain of memory arenas.
      */
    arena_pool_type arena_pool;

    /** @brief The avaliable memory for the current arena.
      */
    std::size_t free_space;

    /** @brief The position where the last allocation succeded.
      */
    void *current_position;

    /** @brief Creates a new arena.
      */
    void grow();

    /** @brief Creates a new arena with at least `size` bytes and `align` alignment.
      */
    void *emplace(std::size_t size, std::size_t align);

   public:
    /** @brief Default constructor.
      * @param size The size of the memory arenas allocated.
      */
    Arena(std::size_t size = 65536);
    
    /** @brief Copy constructor; deleted.
      */
    Arena(const Arena &other) = delete;

    /** @brief Copy assigment operator; deleted.
      */
    Arena &operator=(const Arena &other) = delete;
    
    /** @brief Move constructor.
      * The resources are moved from one arena to the other.
      * @param arena The arena from which the resources are taken.
      */
    Arena(Arena &&arena) noexcept;
    
    /** @brief Move assigment operator.
      * The resources are moved from one arena to the other.
      * @param arena The arena from which the resources are taken.
      */
    Arena &operator=(Arena &&arena) noexcept;

    /** @brief Setter for the memory arena size.
      * @param newsiz The new size that will be used to allocate arenas.
      */
    void set_arena_size(std::size_t newsiz);

    /** @brief Arena memory allocation method.
      * Note that this function won't fail even if more bytes than `arena_size` are requested.
      * @param size  The bytes requested for allocation.
      * @param align The alignment requirement of the memory.
      * @return non-null void pointer to the allocated memory.
      */
    void *allocate(std::size_t size, std::size_t align);

    /** @brief Helper to create a stl compatible allocator.
      * @tparam T The type the allocator will allocate.
      * @return Allocator related with the arena.
      */
    template <typename T>
    ArenaAllocator<T> make_allocator() {
        return ArenaAllocator<T>(*this);
    }
};

/** @class ArenaAllocator
  * @brief Allocator for a given arena.
  * @tparam T The type the allocator allocates.
  */
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
        : ArenaAllocator(other.get_arena()) {}

    template <typename U>
    ArenaAllocator(ArenaAllocator<U> &&other) noexcept
        : ArenaAllocator(other.get_arena()) {}

    Arena &get_arena() {
        return arena;
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

}  // namespace aia

#endif
