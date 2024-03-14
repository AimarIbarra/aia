#ifndef AIA_SET_HPP_INCLUDED_P
#define AIA_SET_HPP_INCLUDED_P

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

#include <set>
#include "aia.hpp"

namespace aia {
    template <typename T, typename Compare = std::less<T>>
    using set = std::set<T, Compare, aia::ArenaAllocator<T>>;
    
    template <typename T, typename Compare = std::less<T>>
    using multiset = std::multiset<T, Compare, aia::ArenaAllocator<T>>;
} // namespace aia

#endif