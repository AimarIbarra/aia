#ifndef AIA_MAP_HPP_INCLUDED_P
#define AIA_MAP_HPP_INCLUDED_P

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

#include <map>
#include "aia.hpp"

namespace aia {
    template <
        typename Key,
        typename T,
        typename Compare = std::less<Key>
    > using map = std::map<Key, T, Compare, aia::ArenaAllocator<T>>;
    
    template <
        typename Key,
        typename T,
        typename Compare = std::less<Key>
    > using multimap = std::multimap<Key, T, Compare, aia::ArenaAllocator<T>>;
} // namespace aia

#endif