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

#ifndef __ANIMATED_SPRITE_HPP__
#define __ANIMATED_SPRITE_HPP__

// ----------------------------------------------------------------------------
// include files

#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

// ----------------------------------------------------------------------------
// forward declarations

class AnimatedSprite
{
public:

    /*!
     * @brief Default constructor
     */
    AnimatedSprite( void );

    /*!
     * @brief Default Destructor
     */
    ~AnimatedSprite( void );

    /*! @brief Loads an image file and creates an animated sprite from it
     *
     * Animated sprites are usually saved as a sheet of frames arranged in a grid.
     * This class handles loading them, splitting them, and playing the animation.
     * Sometimes, animations don't have enough frames to fill a sprite sheet symmetrically,
     * in which case the number of frames can optionally be provided. If not, it is assumed there
     * are splitX*splitY frames.
     * In the case of an animation having only one frame, splitX and splitY don't have to be
     * provided. They will default to 1.
     *
     * @param fileName The image file to load
     * @param splitX How many frames exist horizontally on the image
     * @param splitY How many frames exist vertically on the image
     * @return Returns true if creating the sprite was successful, false if otherwise
     */
    bool loadFromFile( const std::string& fileName, const unsigned long& splitX = 1, const unsigned long& splitY = 1, const unsigned long& frameCount = 0 );

    /*!
     * @brief Sets the position of the sprite
     */
    void setPosition( const float& x, const float& y );

    /*!
     * @brief Sets the global scale of the sprite
     */
    void setScale( const float& x, const float& y );

    /*!
     * @brief Starts playing the animation
     */
    void play( void );

    /*!
     * @brief Starts playing the animation between startFrame and endFrame
     */
    void play( const unsigned long& startFrame, const unsigned long& endFrame );

    /*!
     * @brief Stops playing the animation
     */
    void stop( void );

    /*!
     * @brief Sets the current frame of the animatino
     */
    void setFrame( const unsigned long& frame );

    /*!
     * @brief Sets the time between animation frames
     * Default is 15ms
     * @param time The time to set it to
     */
    void setFrameDelay( const sf::Time& time );

    /*!
     * @brief Updates the animation
     * This should be called every loop so the animation can update.
     * The delta time is used to determine when to switch frames.
     * @param timePassed How much time has passed since the last call to this function.
     */
    void updateFrame( const sf::Time& timePassed );

    /*!
     * @brief Gets the underlying sprite
     */
    const sf::Sprite& getSprite( void ) const;

private:

    sf::Texture m_Texture;
    sf::Sprite m_Sprite;
    sf::Time m_FrameDelay;
    sf::Time m_TimePassed;
    sf::Vector2u m_Split;
    sf::Vector2u m_Size;

    unsigned long m_FrameMax;
    unsigned long m_CurrentFrame;

    bool m_IsPlaying;
};

#endif // __ANIMATED_SPRITE_HPP__
