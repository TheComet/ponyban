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

#include <vector>

// ----------------------------------------------------------------------------
// forward declarations

namespace sf {
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
    EventDispatcher( void );

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

private:

    sf::Event* m_Event;
    std::vector<EventDispatcherListener*> m_EventListeners;

};
