#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

// Forward Declarations
enum class EventType;
struct EventInfo;
struct EventDetails;
struct Binding;
template<class T> struct Callback;

// Type aliases for managing events, bindings, and callbacks
using Events = std::vector<std::pair<EventType, EventInfo>>;
using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

/*
> Couple any mix of keys, buttons, or events (bindings) with desired functionality identified by a string

> Binding of said functionalities to methods that get called if all the conditions are met

> A way through which the event manager can deal with actual SFML events being polled

> Loading the bindings from a config. file
*/

// Enumeration representing the types of events we'll be dealing with
enum class EventType {
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1,
    Mouse,
    Joystick
};

// Structure to hold event information
struct EventInfo {
    EventInfo()
    {
        code = 0;
    }

    EventInfo(int event)
    {
        code = event;
    }

    union
    {
        int code;    // Event code
    };
};

// Structure to hold detailed event information
struct EventDetails
{
    EventDetails(const std::string& bindName)
        : name(bindName)
    {
        Clear();
    }

    std::string name;

    sf::Vector2i size;
    sf::Uint32 textEntered;
    sf::Vector2i mouse;
    int mouseWheelDelta;
    int keyCode;    // Single key code

    void Clear() {
        size = sf::Vector2i(0, 0);
        textEntered = 0;
        mouse = sf::Vector2i(0, 0);
        mouseWheelDelta = 0;
        keyCode = 0; // Represents any scancode not present in this enum
    }
};

// Structure representing a binding of events to functionalities
struct Binding {
    Binding(const std::string& name) : name(name), details(name), c(0) {}

    // Bind an event to the functionality
    void BindEvent(EventType type, EventInfo info = EventInfo()) {
        events.emplace_back(type, info);
    }

    Events events;
    std::string name;
    int c; // Count for events that are "happening" - active event counter

    EventDetails details;
};

// Structure representing a callback
template<class T>
struct Callback {
    std::string name;
    T* CallbackInstance; // Pointer to instance
    void (T::* callback)(); // Pointer to a member function

    // Call the callback function
    void Call() {
        CallbackInstance->*callback();
    }
};

/*
Explanation:
Let's say, we want the character to jump when the spacebar is hit. We would create
a binding with a name "Jump", which is our action name, and add a single event of
type KeyDown and code sf::Keyboard::Space to it. For argument sake, let's say
the character has a method called Jump(). That's our callback. We want to bind that
method to the name "Jump" and have the event manager call the character's Jump()
method when the space key is pressed. That, in a nutshell, is how we're going to be
handling input with this new system.
*/
class EventManager {

public:
    EventManager();
    ~EventManager();

    // Test function for demonstration
    void Test(int x) {
        std::cout << x << std::endl;
    }

    // Add a binding to the manager
    bool AddBinding(Binding* binding);

    // Remove a binding from the manager
    bool RemoveBinding(std::string name);

    // Add a callback to a state
    template<class T>
    bool AddCallback(StateType state, const std::string& name,
        void(T::* func)(EventDetails*), T* instance)
    {
        // std::placeholders::_1 is the argument of func; it has to be given first when it's called
        auto itr = callbacks.emplace(state, CallbackContainer()).first;
        auto temp = std::bind(func, instance, std::placeholders::_1);

        return itr->second.emplace(name, temp).second;
    }

    // Remove a callback from a state
    bool RemoveCallback(StateType state, const std::string& name) {
        auto itr = callbacks.find(state);
        if (itr == callbacks.end())
        {
            return false;
        }

        auto itr2 = itr->second.find(name);
        if (itr2 == itr->second.end())
        {
            return false;
        }

        itr->second.erase(name);
        return true;
    }

    // Handle an SFML event
    void HandleEvent(sf::Event& event);

    // Update the event manager
    void Update();

    // Set the current state of the manager
    void SetCurrentState(StateType state);

    // Get the mouse position
    sf::Vector2i GetMousePos(sf::RenderWindow* wind = nullptr)
    {
        return (wind ? sf::Mouse::getPosition(*wind) : sf::Mouse::getPosition());
    }

    // Load bindings from a config file
    void LoadBindings(std::string keyFilePath);

private:
    // Collections of bindings and callbacks
    Bindings bindings;
    Callbacks callbacks;

    // Current state and focus status
    StateType currentState;
    bool hasFocus;
};
