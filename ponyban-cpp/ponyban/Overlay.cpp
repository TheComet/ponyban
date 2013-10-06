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

#include <Overlay.hpp>
#include <GUIButton.hpp>

// ----------------------------------------------------------------------------
Overlay::Overlay( const unsigned int& left, const unsigned int& top,
                  const unsigned int& right, const unsigned int& bottom ) :
    m_OverlayBoundaries( left, top, right, bottom ),
    m_ReferenceResolution( 1, 1 )
{
}

// ----------------------------------------------------------------------------
Overlay::~Overlay( void )
{
    for( std::map<std::string, GUIButton*>::iterator it = m_ButtonMap.begin(); it != m_ButtonMap.end(); ++it )
        delete it->second;
}

// ----------------------------------------------------------------------------
bool Overlay::createButton( const std::string& reference, const std::string& fileName )
{

    // check for existance
    std::map<std::string, GUIButton*>::iterator it = m_ButtonMap.find(reference);
    if( it != m_ButtonMap.end() )
        return false;

    // create the button
    GUIButton* newButton = new GUIButton();
    if( !newButton->load(fileName) )
    {
        delete newButton;
        return false;
    }
    m_ButtonMap[reference] = newButton;
}

// ----------------------------------------------------------------------------
void Overlay::destroyButton( const std::string& reference )
{
    std::map<std::string, GUIButton*>::iterator it = m_ButtonMap.find(reference);
    if( it == m_ButtonMap.end() )
        return;
    delete it->second;
    m_ButtonMap.erase( it );
}

// ----------------------------------------------------------------------------
void Overlay::render( sf::RenderTarget* target )
{
    for( std::map<std::string, GUIButton*>::iterator it = m_ButtonMap.begin(); it != m_ButtonMap.end(); ++it )
        it->second->render( target );
}
