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

#include <App.hpp>
#include <Game.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

// ----------------------------------------------------------------------------
App::App( void ) :
    m_Window( 0 ),
    m_EventDispatcher( 0 ),
    m_Shutdown( false ),
    m_Game( 0 )
{
    m_Window = new sf::RenderWindow( sf::VideoMode(800,600), "Ponyban" );
    m_Window->clear( sf::Color::Black );
    m_Window->display();

    m_EventDispatcher = new EventDispatcher( m_Window );
    m_EventDispatcher->registerListener( this );
}

// ----------------------------------------------------------------------------
App::~App( void )
{
    delete m_EventDispatcher;
    delete m_Window;
}

// ----------------------------------------------------------------------------
void App::go( void )
{

    m_Game = new Game();
    m_Game->setScreenResolution( m_Window->getSize().x, m_Window->getSize().y );
    m_Game->loadCollection("collections/ksokoban-original.sok");
    m_Game->loadLevel("Level #1");

    sf::Clock clock;
    clock.restart();
    while( !m_Shutdown )
    {

        // handle events
        m_EventDispatcher->processEventLoop();

        // dispatch udpdate event with delta time
        sf::Time elapsed = clock.restart();
        m_EventDispatcher->dispatchUpdate( elapsed );

        m_Game->render( m_Window );

        m_Window->display();

    }
}

// ----------------------------------------------------------------------------
void App::onShutdown( void )
{
    m_Shutdown = true;
}

