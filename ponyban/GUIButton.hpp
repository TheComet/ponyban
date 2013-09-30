/*
 * This file is part of Ponyban.
 *
 * Ponyban is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ponyban is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ponyban.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

// ----------------------------------------------------------------------------
// include files

#include <EventDispatcher.hpp>
#include <TextureResource.hpp>

// ----------------------------------------------------------------------------
// forward declarations

class Button :
    public EventDispatcherListener,
    public TextureResource
{
public:

    /*!
     * @brief Default constructor
     */
    Button( void );

    /*!
     * @brief Default destructor
     */
    ~Button( void );

private:

};

#endif // __BUTTON_HPP__
