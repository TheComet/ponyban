/*
 * This file is part of Chocobun.
 *
 * Chocobun is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Chocobun is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Chocobun.  If not, see <http://www.gnu.org/licenses/>.
 */

// ----------------------------------------------------------------------------
// include files

#include <ChocobunInterface.hpp>

#include <App.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// ----------------------------------------------------------------------------
App::App( void ) :
    m_Window( 0 )
{
    m_Window = new sf::RenderWindow( sf::VideoMode(800,600), "Ponyban" );
    m_Window->clear( sf::Color::Black );
}

// ----------------------------------------------------------------------------
App::~App( void )
{
    delete m_Window;
}

// ----------------------------------------------------------------------------
void App::go( void )
{

    while( m_Window->isOpen() )
    {

        // handle events
        sf::Event event;
        while( m_Window->pollEvent(event) )
        {

            // window close event
            if( event.type == sf::Event::Closed )
                m_Window->close();

        }

    }
}
