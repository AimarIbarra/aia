#ifndef AIA_UNORDERED_MAP_HPP_INCLUDED_P
#define AIA_UNORDERED_MAP_HPP_INCLUDED_P

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

#include <unordered_map>
#include "aia.hpp"

namespace aia {
    template <
        typename Key,
        typename T,
        typename Hash = std::hash<Key>,
        typename KeyEqual = std::equal_to<Key>
    > using unordered_map = std::unordered_map<Key, T, Hash, KeyEqual, aia::ArenaAllocator<std::pair<const Key, T>>>;
    
    template <
        typename Key,
        typename T,
        typename Hash = std::hash<Key>,
        typename KeyEqual = std::equal_to<Key>
    > using unordered_multimap = std::unordered_multimap<Key, T, Hash, KeyEqual, aia::ArenaAllocator<std::pair<const Key, T>>>;
} // namespace aia

#endif