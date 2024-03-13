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

#include "aia.hpp"

void Arena::grow() {
    arena_pool.emplace_front(arena_size);
    free_space = arena_size;
    current_position = arena_pool.begin()->data;
}

void *Arena::emplace(std::size_t size, std::size_t align) {
    arena_pool.emplace_after(arena_pool.begin(), size + align);
    return std::align(align, 1, (++arena_pool.begin())->data, size);
}

Arena::Arena(std::size_t size = 65536) : arena_size(size) { grow(); }

Arena::Arena(Arena &&arena) noexcept {
    arena_size = arena.arena_size;
    free_space = arena.free_space;
    current_position = arena.current_position;
    arena_pool = std::move(arena.arena_pool);
}

Arena &Arena::operator=(Arena &&arena) noexcept {
    arena_size = arena.arena_size;
    free_space = arena.free_space;
    current_position = arena.current_position;
    arena_pool = std::move(arena.arena_pool);
    return *this;
}

void Arena::set_arena_size(std::size_t newsiz) noexcept { arena_size = newsiz; }

void *Arena::allocate(std::size_t size, std::size_t align) {
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