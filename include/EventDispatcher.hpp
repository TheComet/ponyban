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

#ifndef __EVENT_DISPATCHER_HPP__
#define __EVENT_DISPATCHER_HPP__

// ----------------------------------------------------------------------------
// include files

#include <vector>

// ----------------------------------------------------------------------------
// forward declarations

namespace sf {
    class RenderWindow;
    class Event;
}

/*!
 * @brief Allows any inheriting class to listen to dispatched events
 */
class EventDispatcherListener
{
public:

    /*!
     * @brief When the application has begin its shutdown process
     */
    virtual void onShutdown( void ){}

    /*!
     * @brief When a key was pressed.
     * Consult the SFML documentation for more information.
     */
    virtual void onKeyPress( sf::Event& event ){}

    /*!
     * @brief When a key was released.
     * Consult the SFML documentation for more information.
     */
    virtual void onKeyRelease( sf::Event& event){}

    /*!
     * @brief When the player moves.
     */
    virtual void onPlayerMove( const char& direction ){}
};

/*!
 * @brief Handles dispatching events to registered classes
 */
class EventDispatcher
{
public:

    /*!
     * @brief Default constructor
     */
    EventDispatcher( sf::RenderWindow* window );

    /*!
     * @brief Default destructor
     */
    ~EventDispatcher( void );

    /*!
     * @brief Registers a listener
     *
     */
    bool registerListener( EventDispatcherListener* listener );

    /*!
     * @brief Unregisters a listener
     */
    bool unregisterListener( EventDispatcherListener* listener );

    /*!
     * @brief Processes the event loop and dispatches messages
     */
    void processEventLoop( void );

    /*!
     * @brief Dispatches the shutdown signal
     */
    void dispatchShutdown( void );

    /*!
     * @brief Dispatches the key press signal
     */
    void dispatchKeyPress( sf::Event& event );

    /*!
     * @brief Dispatches the key release signal
     */
    void dispatchKeyRelease( sf::Event& event );

    /*!
     * @brief Dispatches the player move signal
     */
    void dispatchPlayerMove( const char direction );

private:

    sf::RenderWindow* m_Window;
    std::vector<EventDispatcherListener*> m_EventListeners;

};

#endif // __EVENT_DISPATCHER_HPP__
