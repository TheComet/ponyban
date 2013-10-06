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

#ifndef __TEXTURE_BASE_HPP__
#define __TEXTURE_BASE_HPP__

// ----------------------------------------------------------------------------
// include files

#include <string>
#include <vector>
#include <map>

// ----------------------------------------------------------------------------
// forward declarations

namespace sf {
    class Texture;
}

/*!
 * @brief Makes sure textre resources are used optimally
 * This class makes sure each texture resource used is only loaded into memory
 * once. Sprites can use this texture to render it to the screen. If no more
 * sprites are referencing a texture, the texture is destroyed and removed
 * from memory.
 */
class TextureResource
{
public:

    /*!
     * @brief Default constructor, loads a texture from a file
     * If the texture isn't already loaded, it is loaded from a file
     */
    TextureResource( void );

    /*!
     * @brief Default destructor
     */
    virtual ~TextureResource( void );

protected:

    /*!
     * @brief Loads a texture from a given file
     * @param fileName The file name of the texture to load
     * @return Returns true if the texture could be loaded, false if otherwise
     */
    bool loadTextureFromFile( const std::string& fileName );

    /*!
     * @brief Gets a pointer to the underlying texture object
     * @note The texture should be loaded before this is called.
     * If it isn't, a null-pointer is returned.
     */
    const sf::Texture* getTexturePtr( void ) const;

    /*!
     * @brief Gets the underlying texture object
     * @note The texture should be loaded before this is called.
     * If it isn't, the program will crash.
     */
    const sf::Texture& getTexture( void ) const;

private:

    sf::Texture* m_Texture;

    static std::map<std::string, sf::Texture*> m_TextureMap;
    static std::vector<TextureResource*> m_TextureResourceList;
};

#endif // __TEXTURE_BASE_HPP__
