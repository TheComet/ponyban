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

#ifndef __GAME_HPP__
#define __GAME_HPP__

// ----------------------------------------------------------------------------
// include files

#include <SFML/System/Vector2.hpp>
#include <EventDispatcher.hpp>

#include <ChocobunInterface.hpp>

#include <string>

// ----------------------------------------------------------------------------
// forward declrations

namespace Chocobun {
    class Collection;
}
namespace sf {
    class RenderTarget;
    class Time;
}

class AnimatedSprite;

class Game :
    public EventDispatcherListener,
    public Chocobun::LevelListener
{
public:

    /*!
     * @brief Default constructor
     */
    Game( void );

    /*!
     * @brief Default destructor
     */
    ~Game( void );

    /*!
     * @brief Sets the resolution of the screen
     * This is required so the game can scale all of the sprites correctly
     * @param x The x size of the screen in pixels
     * @param y The y size of the screen in pixels
     */
    void setScreenResolution( const unsigned int& x, const unsigned int& y );

    /*!
     * @brief Sets the resolution of the screen
     * This is required sot hte game can scale all o fthe sprites correctly
     * @param x The x size of the screen in pixels
     * @param y The y size of the screen in pixels
     */
    void setScreenResolution( const sf::Vector2u& resolution );

    /*!
     * @brief Loads and parses a collection into memory
     * Once a collection is loaded, a list of levels can be retrieved
     * to determine which map to play on.
     * @remarks If a collection is already loaded when this method is called,
     * it is unloaded and replaced by the new one. If the new collection fails
     * to load, the old one will remain unloaded.
     * @param fileName The name of the collection file to parse
     * @return Returns true if loading the collection was successful
     */
    bool loadCollection( const std::string& fileName );

    /*!
     * @brief Loads a level so it can be played on
     *
     * @remarks The collection must be loaded first for this method to work.
     * If the level doesn't exist in the collection, this method will fail.
     * If a level is already loaded when this method is called, it is
     * unloaded and replaced by the new one. If the new level fails to load,
     * the old one will remain unloaded.
     * @param levelName The name of the level to load
     */
    bool loadLevel( const std::string& levelName );

    /*!
     * @brief Renders all graphics to a render target
     * @param target The render target to render to
     */
    void render( sf::RenderTarget* target );

private:

    /*!
     * @brief Update listener
     */
    void onUpdate( const sf::Time& delta );

    /*!
     * @brief Key press listener
     */
    void onKeyPress( sf::Event& event );

    /*!
     * @brief Tile set listener
     */
    void onSetTile( const std::size_t& x, const std::size_t& y, const char& tile );

    sf::Vector2u m_ScreenResolution;

    Chocobun::Collection* m_Collection;

    std::vector<AnimatedSprite*> m_StaticMap;
    std::vector<AnimatedSprite*> m_Boxes;
};

#endif // __GAME_HPP__
