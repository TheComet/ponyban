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

    // load textures
    sf::Texture* m_BoxTexture = new sf::Texture();
    sf::Texture* m_BoxOnGoalTexture = new sf::Texture();
    sf::Texture* m_GoalTexture = new sf::Texture();
    m_PlayerTexture = new sf::Texture();
    sf::Texture* m_PlayerOnGoalTexture = new sf::Texture();
    sf::Texture* m_WallTexture = new sf::Texture();
    if( !m_BoxTexture->loadFromFile("assets/textures/box.gif") ) return;
    if( !m_BoxOnGoalTexture->loadFromFile("assets/textures/box-on-goal.gif") ) return;
    if( !m_GoalTexture->loadFromFile("assets/textures/goal.gif") ) return;
    if( !m_PlayerTexture->loadFromFile("assets/textures/player.gif") ) return;
    if( !m_PlayerOnGoalTexture->loadFromFile("assets/textures/player-on-goal.gif") ) return;
    if( !m_WallTexture->loadFromFile("assets/textures/stone_1.gif") ) return;

    // set up tiles
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
            sf::Sprite* newSprite;

            switch( tile )
            {
                case '$' : newSprite = new sf::Sprite( *m_BoxTexture ); break;
                case '*' : newSprite = new sf::Sprite( *m_BoxOnGoalTexture ); break;
                case '@' : newSprite = new sf::Sprite( *m_PlayerTexture ); break;
                case '+' : newSprite = new sf::Sprite( *m_PlayerOnGoalTexture ); break;
                case '.' : newSprite = new sf::Sprite( *m_GoalTexture ); break;
                case '#' : newSprite = new sf::Sprite( *m_WallTexture ); break;
                default: newSprite = new sf::Sprite(); break;
            }

            m_Map.push_back( newSprite );
            newSprite->setPosition( x*tileSize, y*tileSize );
            newSprite->setScale( tileSize/96, tileSize/96 );
        }
        std::cout << std::endl;
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

void App::onKeyPress( sf::Event& event )
{
    if( event.key.code == sf::Keyboard::Up )
    {
        m_Collection->moveUp();
    }
}

void App::onSetTile( const std::size_t& x, const std::size_t& y, const char& tile )
{
    std::size_t pos = 0;
    for( std::size_t fy = 0; fy != m_Collection->getSizeY(); ++fy )
    {
        for( std::size_t fx = 0; fx != m_Collection->getSizeX(); ++fx )
        {
            if( fx == x && fy == y )
                break;
            ++pos;
        }
    }

    switch( tile )
    {
        case '@' : m_Map.at(pos)->setTexture( *m_PlayerTexture ); break;
    }
}
