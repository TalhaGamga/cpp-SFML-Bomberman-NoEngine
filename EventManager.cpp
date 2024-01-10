#include "EventManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor for EventManager class, initializes focus state
EventManager::EventManager() : hasFocus(true) {}

// Destructor for EventManager class, deallocates memory for bindings
EventManager::~EventManager()
{
    for (auto& itr : bindings)
    {
        delete itr.second;
        itr.second = nullptr;
    }
}

// Add a binding to the manager
bool EventManager::AddBinding(Binding* binding)
{
    // Check for existing bindings with the same name
    if (bindings.find(binding->name) != bindings.end())
    {
        return false;
    }

    // Insert the new binding into the container
    return bindings.emplace(binding->name, binding).second;
}

// Remove a binding from the manager by name
bool EventManager::RemoveBinding(std::string name)
{
    auto itr = bindings.find(name);

    // Check if the binding with the given name exists
    if (itr == bindings.end())
    {
        return false;
    }

    // Deallocate memory for the binding and remove it from the container
    delete itr->second;
    bindings.erase(itr);

    return true;
}

// Handle SFML events and update binding details
void EventManager::HandleEvent(sf::Event& event)
{
    // Handling SFML events
    for (auto& b_itr : bindings)
    {
        Binding* bind = b_itr.second;

        for (auto& e_itr : bind->events)
        {
            EventType sfmlEventType = (EventType)event.type;

            // Check if the event type matches
            if (e_itr.first != sfmlEventType)
            {
                continue;
            }

            // Handle KeyDown and KeyUp events
            if (sfmlEventType == EventType::KeyDown || sfmlEventType == EventType::KeyUp)
            {
                if (e_itr.second.code == event.key.code)
                {
                    // Matching event/keystroke, update details
                    if (bind->details.keyCode != -1)
                    {
                        bind->details.keyCode = e_itr.second.code;
                    }

                    ++(bind->c);
                    break;
                }
            }
            // Handle MButtonDown and MButtonUp events
            else if (sfmlEventType == EventType::MButtonDown || sfmlEventType == EventType::MButtonUp)
            {
                if (e_itr.second.code == event.mouseButton.button)
                {
                    // Matching event/mouse button, update details
                    bind->details.mouse.x = event.mouseButton.x;
                    bind->details.mouse.y = event.mouseButton.y;
                    if (bind->details.keyCode != -1)
                    {
                        bind->details.keyCode = e_itr.second.code;
                    }
                    ++(bind->c);
                    break;
                }
            }
            else
            {
                // Handle other events (MouseWheel, WindowResized, TextEntered)
                if (sfmlEventType == EventType::MouseWheel)
                {
                    bind->details.mouseWheelDelta = event.mouseWheel.delta;
                }
                else if (sfmlEventType == EventType::WindowResized)
                {
                    bind->details.size.x = event.size.width;
                    bind->details.size.y = event.size.height;
                }
                else if (sfmlEventType == EventType::TextEntered)
                {
                    bind->details.textEntered = event.text.unicode;
                }

                ++(bind->c);
            }
        }
    }
}

// Update the bindings and execute callbacks
void EventManager::Update()
{
    if (!hasFocus)
    {
        return;
    }

    for (auto& b_itr : bindings)
    {
        Binding* bind = b_itr.second;

        for (auto& e_itr : bind->events)
        {
            switch (e_itr.first)
            {
            case(EventType::Keyboard):
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.code)))
                {
                    if (bind->details.keyCode != -1)
                    {
                        bind->details.keyCode = e_itr.second.code;
                    }
                    ++(bind->c);
                }
                break;

            case(EventType::Mouse):
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.code)))
                {
                    if (bind->details.keyCode != -1)
                    {
                        bind->details.keyCode = e_itr.second.code;
                    }
                    ++(bind->c);
                }
                break;
            case(EventType::Joystick):
                // Up for expansion
                break;
            }
        }

        // Control here.
        if (bind->events.size() == bind->c)
        {
            auto stateCallbacks = callbacks.find(currentState);
            auto otherCallbacks = callbacks.find(StateType(0));

            if (stateCallbacks != callbacks.end())
            {
                auto callItr = stateCallbacks->second.find(bind->name);
                if (callItr != stateCallbacks->second.end())
                {
                    // Execute callback with information about events.
                    callItr->second(&bind->details);
                }
            }

            if (otherCallbacks != callbacks.end())
            {
                auto callItr = otherCallbacks->second.find(bind->name);
                if (callItr != otherCallbacks->second.end())
                {
                    // Execute callback with information about events.
                    callItr->second(&bind->details);
                }
            }
        }

        bind->c = 0;
    }
}

// Set the current state of the event manager
void EventManager::SetCurrentState(StateType state)
{
    currentState = state;
}

// Load bindings from a configuration file
void EventManager::LoadBindings(std::string keyFilePath)
{
    std::string delimiter = ":";

    std::ifstream bindingConfigs;
    bindingConfigs.open(keyFilePath);
    if (!bindingConfigs.is_open())
    {
        std::cout << "! Failed loading keys.cfg." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(bindingConfigs, line))
    {
        std::stringstream keystream(line);
        std::string callbackName;
        keystream >> callbackName;

        // Create a new binding with the specified name
        Binding* bind = new Binding(callbackName);

        while (!keystream.eof())
        {
            std::string keyval;
            keystream >> keyval;
            int start = 0;
            int end = keyval.find(delimiter);

            // Check for valid key-value pair
            if (end == std::string::npos)
            {
                delete bind;
                bind = nullptr;
                break;
            }

            // Extract event type and code from the key-value pair
            EventType type = EventType(stoi(keyval.substr(start, end - start)));
            int code = stoi(keyval.substr(end + delimiter.length(),
                keyval.find(delimiter, end + delimiter.length())));
            EventInfo eventInfo;
            eventInfo.code = code;

            // Bind the event to the current binding
            bind->BindEvent(type, eventInfo);
        }

        // Add the binding to the manager or deallocate memory if unsuccessful
        if (!AddBinding(bind))
        {
            delete bind;
        }

        bind = nullptr;
    }

    bindingConfigs.close();
}
