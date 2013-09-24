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
#include <AnimatedSprite.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <ChocobunInterface.hpp>

#include <iostream>

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
    m_Collection = new Chocobun::Collection( "collections/ksokoban-original.sok" );
    m_Collection->initialise();
    m_Collection->setActiveLevel( "Level #1" );
    m_Collection->validateLevel();
    m_Collection->addLevelListener( this );

    // set up static tiles
    float tileSize = 800.0 / static_cast<float>(m_Collection->getSizeX());
    if( tileSize > 600.0 / static_cast<float>(m_Collection->getSizeY()) ) tileSize = 600.0 / static_cast<float>(m_Collection->getSizeY());
    std::cout << "dimensions: " << m_Collection->getSizeX() << "," << m_Collection->getSizeY() << std::endl;
    std::cout << "tile size: " << tileSize << std::endl;
    for( std::size_t y = 0; y != m_Collection->getSizeY(); ++y )
    {
        for( std::size_t x = 0; x != m_Collection->getSizeX(); ++x )
        {
            char tile = m_Collection->getTile( x, y );
            std::cout << tile;
            AnimatedSprite* newSprite;

            switch( tile )
            {
                case '*' : newSprite = new AnimatedSprite(); newSprite->loadFromFile("assets/textures/goal.gif"); break;
                case '+' : newSprite = new AnimatedSprite(); newSprite->loadFromFile("assets/textures/goal.gif"); break;
                case '.' : newSprite = new AnimatedSprite(); newSprite->loadFromFile("assets/textures/goal.gif",2,2); break;
                case '#' : newSprite = new AnimatedSprite(); newSprite->loadFromFile("assets/textures/stone_1.gif"); break;
                default: newSprite = new AnimatedSprite(); newSprite->loadFromFile("assets/textures/background.jpg"); break;
            }

            m_Map.push_back( newSprite );
            newSprite->setPosition( x*tileSize, y*tileSize );
            newSprite->setScale( tileSize/96, tileSize/96 );
            newSprite->setFrameDelay( sf::milliseconds(200) );
            newSprite->play();
        }
        std::cout << std::endl;
    }

    sf::Clock clock;
    clock.restart();
    while( !m_Shutdown )
    {

        // handle events
        m_EventDispatcher->processEventLoop();

        sf::Time elapsed = clock.restart();
        for( std::vector<AnimatedSprite*>::iterator it = m_Map.begin(); it != m_Map.end(); ++it )
        {
            (*it)->updateFrame( elapsed );
            m_Window->draw( (*it)->getSprite() );
        }

        m_Window->display();

    }
}

// ----------------------------------------------------------------------------
void App::onShutdown( void )
{
    m_Shutdown = true;
}

void App::onKeyPress( sf::Event& event )
{
    if( event.key.code == sf::Keyboard::Up )
        m_Collection->moveUp();
    if( event.key.code == sf::Keyboard::Down )
        m_Collection->moveDown();
    if( event.key.code == sf::Keyboard::Left )
        m_Collection->moveLeft();
    if( event.key.code == sf::Keyboard::Right )
        m_Collection->moveRight();
}

void App::onSetTile( const std::size_t& x, const std::size_t& y, const char& tile )
{
    std::size_t pos = y*m_Collection->getSizeX() + x;
}
