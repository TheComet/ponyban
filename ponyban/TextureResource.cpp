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

#include <TextureResource.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

std::vector<TextureResource*> TextureResource::m_TextureResourceList;
std::map<std::string, sf::Texture*> TextureResource::m_TextureMap;

// ----------------------------------------------------------------------------
TextureResource::TextureResource( void ) :
    m_Texture(0)
{
    m_TextureResourceList.push_back( this );
}

// ----------------------------------------------------------------------------
TextureResource::~TextureResource( void )
{

    // erase from texture resource list and check if texture
    // is referenced by any other texture resources
    bool doErase = true;
    for( std::vector<TextureResource*>::iterator it = m_TextureResourceList.begin(); it != m_TextureResourceList.end(); ++it )
    {
        if( (*it) == this )
            it = m_TextureResourceList.erase( it );
        if( it == m_TextureResourceList.end() )
            break;

        if( (*it)->getTexturePtr() == m_Texture )
            doErase = false;
    }

    // erase texture from list if it is not referenced any more
    if( doErase )
    {
        for( std::map<std::string, sf::Texture*>::iterator it = m_TextureMap.begin(); it != m_TextureMap.end(); ++it )
        {
            if( it->second == m_Texture )
            {
                delete it->second;
                std::cout << "Texture resource \"" << it->first << "\" destroyed." << std::endl;
                m_TextureMap.erase( it );
                break;
            }
        }
    }
}

// ----------------------------------------------------------------------------
bool TextureResource::loadTextureFromFile( const std::string& fileName )
{
    std::map<std::string, sf::Texture*>::iterator textureIt = m_TextureMap.find( fileName );
    if( textureIt == m_TextureMap.end() )
    {
        m_Texture = new sf::Texture();
        if( !m_Texture->loadFromFile(fileName) )
        {
            delete m_Texture;
            return false;
        }
        m_Texture->setSmooth( true );
        m_TextureMap[fileName] = m_Texture;
        std::cout << "loaded texture " << fileName << std::endl;
    }else
    {
        m_Texture = textureIt->second;
        std::cout << "re-used texture " << fileName << std::endl;
    }
}

// ----------------------------------------------------------------------------
const sf::Texture* TextureResource::getTexturePtr( void ) const
{
    return m_Texture;
}

// ----------------------------------------------------------------------------
const sf::Texture& TextureResource::getTexture( void ) const
{
    return *m_Texture;
}
