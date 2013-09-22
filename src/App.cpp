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

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <ChocobunInterface.hpp>

// ----------------------------------------------------------------------------
App::App( void ) :
    m_Window( 0 ),
    m_EventDispatcher( 0 ),
    m_Shutdown( false )
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

    // create collection
    Chocobun::Collection* m_Collection = new Chocobun::Collection( "collections/ksokoban-original.sok" );
    m_Collection->initialise();
    m_Collection->setActiveLevel( "Level #1" );

    // load textures
    sf::Texture* m_BoxTexture = new sf::Texture;
    if( !m_BoxTexture->loadFromFile("assets/textures/box.gif"))
        return;

    // set up tiles
    std::vector<sf::Sprite*> m_Map;
    float tileSize = 800/m_Collection->getSizeY();
    for( std::size_t x = 0; x != m_Collection->getSizeX(); ++x )
    {
        for( std::size_t y = 0; y != m_Collection->getSizeY(); ++y )
        {
            char tile = m_Collection->getTile( x, y );
            sf::Sprite* newSprite;
            switch( tile )
            {
                case '$' :
                    newSprite = new sf::Sprite( *m_BoxTexture );
                break;
                default: break;
            }
            m_Map.push_back( newSprite );
            newSprite->setPosition( x*tileSize, y*tileSize );
            newSprite->setScale( tileSize/96, tileSize/96 );
        }
    }

    while( !m_Shutdown )
    {

        // handle events
        m_EventDispatcher->processEventLoop();

        for( std::vector<sf::Sprite*>::iterator it = m_Map.begin(); it != m_Map.end(); ++it )
            m_Window->draw( **it );

        m_Window->display();

    }
}

// ----------------------------------------------------------------------------
void App::onShutdown( void )
{
    m_Shutdown = true;
}
