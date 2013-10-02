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

#include <GUIButton.hpp>
#include <AnimatedSprite.hpp>

#include <ChocobunInterface.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

// ----------------------------------------------------------------------------
GUIButton::GUIButton( void )
{
}

// ----------------------------------------------------------------------------
GUIButton::~GUIButton( void )
{
}

// ----------------------------------------------------------------------------
bool GUIButton::load( const std::string& fileName )
{
    if( !m_Sprite.loadFromFile(fileName) )
        return false;
    return true;
}

// ----------------------------------------------------------------------------
void GUIButton::setPosition( const float& x, const float& y )
{
    m_Sprite.setPosition( x, y );
}

// ----------------------------------------------------------------------------
void GUIButton::render( sf::RenderTarget* target )
{
    target->draw( m_Sprite.getSprite() );
}
