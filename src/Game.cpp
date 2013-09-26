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

#include <Game.hpp>
#include <AnimatedSprite.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <ChocobunInterface.hpp>

// ----------------------------------------------------------------------------
Game::Game( void ) :
    m_Collection( 0 ),
    m_ScreenResolution( 0, 0 )
{
}

// ----------------------------------------------------------------------------
Game::~Game( void )
{
}

// ----------------------------------------------------------------------------
void Game::setScreenResolution( const unsigned int& x, const unsigned int& y )
{
    m_ScreenResolution.x = x;
    m_ScreenResolution.y = y;
}

// ----------------------------------------------------------------------------
void Game::setScreenResolution( const sf::Vector2u& resolution )
{
    m_ScreenResolution = resolution;
}

// ----------------------------------------------------------------------------
bool Game::loadCollection( const std::string& fileName )
{
    if( m_Collection )
        delete m_Collection;
    m_Collection = new Chocobun::Collection( fileName );
    m_Collection->initialise();
    m_Collection->addLevelListener( this );
    return true;
}

// ----------------------------------------------------------------------------
bool Game::loadLevel( const std::string& levelName )
{
    if( !m_Collection ) return false;

    m_Collection->setActiveLevel( levelName );
    if( !m_Collection->validateLevel() )
        return false;

    // prerequisits
    float tileSize = m_ScreenResolution.x / static_cast<float>(m_Collection->getSizeX());
    if( tileSize > m_ScreenResolution.y / static_cast<float>(m_Collection->getSizeY()) )
        tileSize = m_ScreenResolution.y / static_cast<float>(m_Collection->getSizeY());
    std::cout << "dimensions: " << m_Collection->getSizeX() << "," << m_Collection->getSizeY() << std::endl;
    std::cout << "tile size: " << tileSize << std::endl;


    // set up static tiles
    for( std::size_t y = 0; y != m_Collection->getSizeY(); ++y )
    {
        for( std::size_t x = 0; x != m_Collection->getSizeX(); ++x )
        {
            char tile = m_Collection->getTile( x, y );
            AnimatedSprite* newSprite = new AnimatedSprite();

            switch( tile )
            {
                case '*' || '+' || '.' :
                    newSprite->loadFromFile("assets/textures/goal.gif");
                    break;
                case '#' :
                    newSprite->loadFromFile("assets/textures/stone_1.gif");
                    break;
                default:
                    newSprite->loadFromFile("assets/textures/background.jpg");
                    break;
            }
            m_StaticMap.push_back( newSprite );
            newSprite->setPosition( x*tileSize, y*tileSize );
            newSprite->setScale( tileSize/96, tileSize/96 );
        }
        std::cout << std::endl;
    }

    // set up dynamic tiles
    for( std::size_t y = 0; y != m_Collection->getSizeY(); ++y )
    {
        for( std::size_t x = 0; x != m_Collection->getSizeX(); ++x )
        {
            char tile = m_Collection->getTile( x, y );
            AnimatedSprite* newSprite = new AnimatedSprite();

            switch( tile )
            {
                case '$' || '*' :
                    newSprite->loadFromFile("assets/textures/box.gif");
                    break;
            }
        }
    }

    return true;
}

// ----------------------------------------------------------------------------
void Game::render( sf::RenderTarget* target )
{
    for( std::vector<AnimatedSprite*>::iterator it = m_StaticMap.begin(); it != m_StaticMap.end(); ++it )
        target->draw( (*it)->getSprite() );

    for( std::vector<AnimatedSprite*>::iterator it = m_Boxes.begin(); it != m_Boxes.end(); ++it )
        target->draw( (*it)->getSprite() );
}

// ----------------------------------------------------------------------------
void Game::onUpdate( const sf::Time& delta )
{

}

// ----------------------------------------------------------------------------
void Game::onKeyPress( sf::Event& event )
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

// ----------------------------------------------------------------------------
void Game::onSetTile( const std::size_t& x, const std::size_t& y, const char& tile )
{
    std::size_t pos = y*m_Collection->getSizeX() + x;
}
