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

#include <AnimatedSprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

// ----------------------------------------------------------------------------
AnimatedSprite::AnimatedSprite( void ) :
    m_IsPlaying( false ),
    m_FrameDelay( sf::milliseconds(15) ), // default setting
    m_TileX(0),
    m_TileY(0)
{
}

// ----------------------------------------------------------------------------
AnimatedSprite::~AnimatedSprite( void )
{


}

// ----------------------------------------------------------------------------
bool AnimatedSprite::loadFromFile( const std::string& fileName, const unsigned long& splitX, const unsigned long& splitY, const unsigned long& frameCount )
{

    // load texture
    if( !this->loadTextureFromFile( fileName ) )
        return false;

    if( !frameCount ) m_FrameMax = splitX * splitY - 1; else m_FrameMax = frameCount-1; // frame count starts at 0, not 1
    m_Split.x = splitX;
    m_Split.y = splitY;
    m_Size = this->getTexturePtr()->getSize();
    m_Size.x /= splitX;
    m_Size.y /= splitY;
    m_Sprite.setTexture( this->getTexture() );
    this->setFrame(0);

    return true;
}

// ----------------------------------------------------------------------------
void AnimatedSprite::setPosition( const float& x, const float& y )
{
    m_Sprite.setPosition( x, y );
}

// ----------------------------------------------------------------------------
void AnimatedSprite::setTilePosition( const std::size_t& x, const std::size_t& y, const float& tileSize )
{
    m_Sprite.setPosition( x*tileSize, y*tileSize );
    this->m_TileX = x;
    this->m_TileY = y;
}

// ----------------------------------------------------------------------------
std::size_t AnimatedSprite::getTilePositionX( void )
{
    return m_TileX;
}

// ----------------------------------------------------------------------------
std::size_t AnimatedSprite::getTilePositionY( void )
{
    return m_TileY;
}

// ----------------------------------------------------------------------------
void AnimatedSprite::setScale( const float& x, const float& y )
{
    m_Sprite.setScale( x*static_cast<float>(m_Split.x), y*static_cast<float>(m_Split.y) );
}

// ----------------------------------------------------------------------------
void AnimatedSprite::updateFrame( const sf::Time& timePassed )
{
    if( !m_IsPlaying ) return;
    m_TimePassed += timePassed;
    while( m_TimePassed > m_FrameDelay )
    {
        m_TimePassed -= m_FrameDelay;
        if( ++m_CurrentFrame > m_FrameMax ) m_CurrentFrame = 0;
        this->setFrame( m_CurrentFrame );
    }
}

// ----------------------------------------------------------------------------
void AnimatedSprite::setFrame( const unsigned long& frame )
{
    if( frame > m_FrameMax ) return;
    sf::IntRect r( 0, 0, 0, 0 );
    while( (r.top+1)*m_Split.x <= frame ) ++r.top;
    r.left = frame - (r.top*m_Split.x);
    r.left *= m_Size.x;
    r.top *= m_Size.y;
    r.width = m_Size.x;
    r.height = m_Size.y;
    m_CurrentFrame = frame;
    m_Sprite.setTextureRect( r );
}

// ----------------------------------------------------------------------------
void AnimatedSprite::play( void )
{
    this->play( 0, m_FrameMax );
}
void AnimatedSprite::play( const unsigned long& frameStart, const unsigned long& frameEnd )
{
    if( frameStart > m_FrameMax || frameEnd > m_FrameMax ) this->play( 0, m_FrameMax );
    m_IsPlaying = true;
}

// ----------------------------------------------------------------------------
void AnimatedSprite::stop( void )
{
    m_IsPlaying = false;
}

// ----------------------------------------------------------------------------
void AnimatedSprite::setFrameDelay( const sf::Time& time )
{
    if( time <= sf::milliseconds(0) ) return;
    m_FrameDelay = time;
}

// ----------------------------------------------------------------------------
const sf::Sprite& AnimatedSprite::getSprite( void ) const
{
    return m_Sprite;
}
