/*
 * This file is part of Chocobun.
 *
 * Chocobun is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Chocobun is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Chocobun.  If not, see <http://www.gnu.org/licenses/>.
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

        // window close event
        if( event.type == sf::Event::Closed )
            this->dispatchShutdown();
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
