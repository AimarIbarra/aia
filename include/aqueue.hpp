#ifndef AQUEUE_HPP_INCLUDED
#define AQUEUE_HPP_INCLUDED

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

#include <queue>
#include "aia.hpp"
#include "aqueue.hpp"
#include "avector.hpp"

namespace aia {
    template <typename T>
    using aqueue = std::queue<T, aia::adeque<T>>;

    template <typename T, typename Compare = std::less<typename aia::avector<T>::value_type>>
    using apriority_queue = std::priority_queue<T, aia::avector<T>, Compare>;
} // namespace aia

#endif