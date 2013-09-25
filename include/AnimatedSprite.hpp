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
#include <map>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

// ----------------------------------------------------------------------------
// forward declarations

/*!
 * @brief Handles animated sprites
 * Animated sprites are usually saved as one image containing a grid
 * of frames. This class handles loading, splitting, and playing them.
 * You are able to customize how many frames are contained within an image,
 * and you have control over playing only parts of an animation.
 *
 * Example code:
 * @code
 * // load the sprite
 * AnimatedSprite mySprite;
 * if( !mySprite.loadFromFile("test.gif", 8, 8 ) // the sprite sheet contains 8x8 frames (64)
 *     return;
 *
 * // our idle frame is from frame 2-15
 * mySprite.play(2,15);
 *
 * // in your main loop...
 * sf::Clock clock;
 * while(1)
 * {
 *
 *     // calculate elapsed time, which is used to update all animated sprites
 *     sf::Time elapsedTime = clock.restart();
 *
 *     // update sprites here (if you have more, some kind of for loop)
 *     mySprite.updateFrame( elapsedTime );
 * }
 * @endcode
 */
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
     * Animated sprites are usually saved as a single image of frames arranged in a grid.
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
     * The position is relative to the top-left corner of the sprite,
     * and sets the position in pixels on the screen.
     * @param x The x-coordinate to set it to
     * @param y The y-coordinate to set it to
     */
    void setPosition( const float& x, const float& y );

    /*!
     * @brief Sets the global scale of the sprite
     * The scale is a factor of the original size, which by
     * default is 1,1
     * @param x The x-scale
     * @param y The y-scale
     */
    void setScale( const float& x, const float& y );

    /*!
     * @brief Starts playing the animation
     * The animation will begin to play with the specified
     * time delay between frames (see @a setFrameDelay). When the animation
     * reaches the end of its frames, it will loop around and begin playing
     * from the beginning again. If there is only one frame, nothing will
     * happen.
     */
    void play( void );

    /*!
     * @brief Starts playing the animation between startFrame and endFrame
     * The animation will begin to play with the specified time delay between
     * frames (see @a setFrameDelay) from the beginning frame to the end frame.
     * When the animation reaches the end of its frames, it will loop around and
     * begin playing from the beginning again. If there is only one frame, nothing
     * will happend.
     * @param startFrame The frame to begin playing from
     * @param endFrame The frame to stop at and wrap around again
     */
    void play( const unsigned long& startFrame, const unsigned long& endFrame );

    /*!
     * @brief Stops playing the animation
     * Will halt the animation and display the current frame, until the animation
     * is resumed again.
     */
    void stop( void );

    /*!
     * @brief Sets the current frame of the animatino
     * If the specified frame is larger than the total frames of the animation,
     * this method will silently fail.
     * @param frame The frame to set
     */
    void setFrame( const unsigned long& frame );

    /*!
     * @brief Sets the time between animation frames
     * Default is 15ms. Sets the time between frames when playing.
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
     * @brief Gets the underlying sprite object. This object is read-only.
     */
    const sf::Sprite& getSprite( void ) const;

    /*!
     * @brief Gets a pointer to the underlying texture object.
     */
    const sf::Texture* const getTexturePtr( void ) const;

private:

    sf::Texture* m_Texture;
    sf::Sprite m_Sprite;
    sf::Time m_FrameDelay;
    sf::Time m_TimePassed;
    sf::Vector2u m_Split;
    sf::Vector2u m_Size;

    unsigned long m_FrameMax;
    unsigned long m_CurrentFrame;

    bool m_IsPlaying;

    static std::vector<AnimatedSprite*> m_AnimatedSpriteList;
    static std::map<std::string, sf::Texture*> m_TextureMap;
};

#endif // __ANIMATED_SPRITE_HPP__
