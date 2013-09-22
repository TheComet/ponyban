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

#include <EventDispatcher.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

// ----------------------------------------------------------------------------
EventDispatcher::EventDispatcher( sf::RenderWindow* window ) :
    m_Window( window )
{
}

// ----------------------------------------------------------------------------
EventDispatcher::~EventDispatcher( void )
{
}

// ----------------------------------------------------------------------------
void EventDispatcher::processEventLoop( void )
{
    sf::Event event;
    while( m_Window->pollEvent( event ) )
    {
        switch( event.type )
        {

            // window close event
            case sf::Event::Closed :
                this->dispatchShutdown();
            break;

            // keypresses
            case sf::Event::KeyPressed :

                // shutdown with escape key
                if( event.key.code == sf::Keyboard::Escape )
                    this->dispatchShutdown();

                // dispatch key event
                this->dispatchKeyPress( event );

            break;

            // key releases
            case sf::Event::KeyReleased :
                this->dispatchKeyRelease( event );
            break;

            default:break;
        }

    }
}

// ----------------------------------------------------------------------------
bool EventDispatcher::registerListener( EventDispatcherListener* listener )
{
    for( std::vector<EventDispatcherListener*>::iterator it = m_EventListeners.begin(); it != m_EventListeners.end(); ++it )
        if( listener == *it ) return false;
    m_EventListeners.push_back( listener );
    return true;
}

// ----------------------------------------------------------------------------
bool EventDispatcher::unregisterListener( EventDispatcherListener* listener )
{
    for( std::vector<EventDispatcherListener*>::iterator it = m_EventListeners.begin(); it != m_EventListeners.end(); ++it )
        if( listener == *it )
        {
            m_EventListeners.erase( it );
            return true;
        }
    return false;
}

// ----------------------------------------------------------------------------
void EventDispatcher::dispatchShutdown( void )
{
    for( std::vector<EventDispatcherListener*>::iterator it = m_EventListeners.begin(); it != m_EventListeners.end(); ++it )
        (*it)->onShutdown();
}

// ----------------------------------------------------------------------------
void EventDispatcher::dispatchKeyPress( sf::Event& event )
{
    for( std::vector<EventDispatcherListener*>::iterator it = m_EventListeners.begin(); it != m_EventListeners.end(); ++it )
        (*it)->onKeyPress( event );
}

// ----------------------------------------------------------------------------
void EventDispatcher::dispatchKeyRelease( sf::Event& event )
{
    for( std::vector<EventDispatcherListener*>::iterator it = m_EventListeners.begin(); it != m_EventListeners.end(); ++it )
        (*it)->onKeyRelease( event );
}

// ----------------------------------------------------------------------------
void EventDispatcher::dispatchPlayerMove( const char direction )
{
    for( std::vector<EventDispatcherListener*>::iterator it = m_EventListeners.begin(); it != m_EventListeners.end(); ++it )
        (*it)->onPlayerMove( direction );
}
