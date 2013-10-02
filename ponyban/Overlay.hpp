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

// ----------------------------------------------------------------------------
// include files

#include <map>
#include <string>

#include <SFML/Graphics/Rect.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace sf {
    class RenderTarget;
}

class GUIButton;

class Overlay
{
public:

    /*!
     * @brief Default constructor
     * Creates an overlay covering the specified region of the screen. The area
     * is defined using pixels, meaning it is not independant of screen size.
     * @param left The left extreme of the rectangle
     * @param top The top extreme of the rectangle
     * @param right The right extreme of the rectangle
     * @param bottom The bottom extreme of the rectangle
     */
    Overlay( const unsigned int& left, const unsigned int& top, const unsigned int& right, const unsigned int& bottom );

    /*!
     * @brief Default destructor
     */
    ~Overlay( void );

    /*!
     * @brief Sets the reference resolution of this overlay
     * A reference resolution is used to make positioning and scaling of the
     * GUI elements completely independant of screen resolution. If for
     * instance a reference resolution of 1024x768 were to be specified, and
     * the game were to run in 1024x768 graphics mode, all sprites would be
     * scaled 1:1. If the game were to run in 1280x1024 instead of 1024x768,
     * all sprites would be scaled slightly larger in order to compensate.
     * @param x The x-dimension of the reference resolution
     * @param y The y-dimension of the reference resolution
     */
    void setReferenceResolution( const unsigned int& x, const unsigned int& y );

    /*!
     * @brief Creates a button
     */
    bool createButton( const std::string& reference, const std::string& fileName );
    void destroyButton( const std::string& reference );

    void render( sf::RenderTarget* target );

private:

    std::map<std::string, GUIButton*> m_ButtonMap;

    sf::Rect<unsigned int> m_OverlayBoundaries;
    sf::Vector2<unsigned int> m_ReferenceResolution;
};
