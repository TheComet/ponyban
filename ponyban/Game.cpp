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
    m_ScreenResolution( 0, 0 ),
    m_Player( 0 )
{
}

// ----------------------------------------------------------------------------
Game::~Game( void )
{
    this->unload();
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
        this->unload();
    m_Collection = new Chocobun::Collection( fileName );
    m_Collection->initialise();
    m_Collection->addLevelListener( this );
    return true;
}

// ----------------------------------------------------------------------------
void Game::unload( void )
{

    // delete all sprites
    if( m_Player ){ delete m_Player; m_Player = 0; }
    for( std::vector<AnimatedSprite*>::iterator it = m_Boxes.begin(); it != m_Boxes.end(); ++it )
        delete (*it);
    for( std::vector<AnimatedSprite*>::iterator it =m_StaticMap.begin(); it != m_StaticMap.end(); ++it )
        delete (*it);
    m_Boxes.clear();
    m_StaticMap.clear();

    // delete collection
    if( m_Collection ){ delete m_Collection; m_Collection = 0; }

}

// ----------------------------------------------------------------------------
bool Game::loadLevel( const std::string& levelName )
{
    if( !m_Collection ) return false;

    m_Collection->setActiveLevel( levelName );
    if( !m_Collection->validateLevel() )
        return false;

    // prerequisits
    m_TileSize = m_ScreenResolution.x / static_cast<float>(m_Collection->getSizeX());
    if( m_TileSize > m_ScreenResolution.y / static_cast<float>(m_Collection->getSizeY()) )
        m_TileSize = m_ScreenResolution.y / static_cast<float>(m_Collection->getSizeY());
    std::cout << "dimensions: " << m_Collection->getSizeX() << "," << m_Collection->getSizeY() << std::endl;
    std::cout << "tile size: " << m_TileSize << std::endl;


    // set up static tiles
    for( std::size_t y = 0; y != m_Collection->getSizeY(); ++y )
    {
        for( std::size_t x = 0; x != m_Collection->getSizeX(); ++x )
        {
            char tile = m_Collection->getTile( x, y );
            AnimatedSprite* newSprite = new AnimatedSprite();

            if( tile == '.' || tile == '*' || tile == '+' )
            {
                if( !newSprite->loadFromFile("assets/textures/goal.png") )
                    return false;
            }
            else if( tile == '#' )
            {
                if( !newSprite->loadFromFile("assets/textures/wall.png") )
                    return false;
            }
            else
            {
                if( !newSprite->loadFromFile("assets/textures/background.jpg") )
                    return false;
            }

            newSprite->setTilePosition( x, y, m_TileSize );
            newSprite->setScale( m_TileSize/128, m_TileSize/128 );
            m_StaticMap.push_back( newSprite );
        }
    }

    // set up dynamic tiles
    for( std::size_t y = 0; y != m_Collection->getSizeY(); ++y )
    {
        for( std::size_t x = 0; x != m_Collection->getSizeX(); ++x )
        {
            char tile = m_Collection->getTile( x, y );

            if( tile == '$' || tile == '*' )
            {
                AnimatedSprite* newSprite = new AnimatedSprite();
                if( !newSprite->loadFromFile("assets/textures/box.png") )
                    return false;
                newSprite->setTilePosition( x, y, m_TileSize );
                newSprite->setScale( m_TileSize/128, m_TileSize/128 );
                m_Boxes.push_back( newSprite );
            }
            if( !m_Player && tile == '@' )
            {
                m_Player = new AnimatedSprite();
                if( !m_Player->loadFromFile("assets/textures/player.png") )
                    return false;
                m_Player->setTilePosition( x, y, m_TileSize );
                m_Player->setScale( m_TileSize/128, m_TileSize/128 );
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

    target->draw( m_Player->getSprite() );
}

// ----------------------------------------------------------------------------
void Game::onUpdate( const sf::Time& delta )
{

}

// ----------------------------------------------------------------------------
void Game::onKeyPress( sf::Event& event )
{
    if( !m_Collection ) return;

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
    std::cout << "updating tile " << tile << " at position " << x << "," << y << std::endl;

    // new player position
    if( tile == '@' || tile == '+' )
        m_Player->setPosition( x*m_TileSize, y*m_TileSize );

    // new book position
    if( tile == '$' || tile == '*' );

}

// ----------------------------------------------------------------------------
void Game::onMoveTile( const std::size_t& oldX, const std::size_t& oldY, const std::size_t& newX, const std::size_t& newY )
{
    std::cout << "moving tile at position " << oldX << "," << oldY << " to position " << newX << "," << newY << std::endl;

    // move boxes
    for( std::vector<AnimatedSprite*>::iterator it = m_Boxes.begin(); it != m_Boxes.end(); ++it )
    {
        if( (*it)->getTilePositionX() == oldX && (*it)->getTilePositionY() == oldY )
        {
            (*it)->setTilePosition( newX, newY, m_TileSize );
            break;
        }
    }
}
