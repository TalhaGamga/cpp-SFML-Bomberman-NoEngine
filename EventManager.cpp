#include "EventManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

EventManager::EventManager() :hasFocus(true) {}

// We store the bindings on the heap, so this dynamic memory has to be de-allocated
EventManager::~EventManager()
{
	for (auto& itr : bindings)
	{
		delete itr.second;
		itr.second = nullptr;
	}
}

/*
 It checks if the binding container already has a binding with the same name. If it does,
 the method returns 'false', which is useful for error-checking. ýf there are no name clashed,
 the new binding gets inserted into the container.
*/
bool EventManager::AddBinding(Binding* binding)
{
	if (bindings.find(binding->name) != bindings.end())
	{
		return false;
	}

	return bindings.emplace(binding->name, binding).second;
}

bool EventManager::RemoveBinding(std::string name)
{
	auto itr = bindings.find(name);

	if (itr == bindings.end())
	{
		return false;
	}

	delete itr->second;
	bindings.erase(itr);

	return true;
}

/*
 We need a way to process the SFML events that are being polled in each iteration
 in order to look at them and see if there's anything in there we're interested in.
 This is where 'HandleEvent' comes in.
*/
void EventManager::HandleEvent(sf::Event& event)    /// Will set bindings
{
	// Handling SFML events
	for (auto& b_itr : bindings) // iterate over bindings(bindName,binding)
	{
		Binding* bind = b_itr.second;

		for (auto& e_itr : bind->events) // iterate over events in the binding
		{
			EventType sfmlEventType = (EventType)event.type;

			if (e_itr.first != sfmlEventType)
			{
				continue;
			}

			if (sfmlEventType == EventType::KeyDown || sfmlEventType == EventType::KeyUp) // find the type of event coming
			{
				if (e_itr.second.code == event.key.code)
				{
					// Matching event/keystroke
					// Increase count
					//std::cout << "code:" << e_itr.second.code << "\n";
					if (bind->details.keyCode != -1)
					{
						//std::cout << "keyCode:" << bind->details.keyCode << "\n";
						bind->details.keyCode = e_itr.second.code;
					}

					++(bind->c);
					break;
				}
			}

			else if (sfmlEventType == EventType::MButtonDown || sfmlEventType == EventType::MButtonUp) // find the type of event coming
			{
				if (e_itr.second.code == event.mouseButton.button)
				{
					// Matching event/keystroke
					// Increase count
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

			else {
				// No need for additional checking
				if (sfmlEventType == EventType::MouseWheel)
				{
					bind->details.mouseWheelDelta = event.mouseWheel.delta;
				}

				else if (sfmlEventType == EventType::WindowResized) {
					bind->details.size.x = event.size.width;
					bind->details.size.y = event.size.height;
				}

				else if (sfmlEventType == EventType::TextEntered) {
					bind->details.textEntered = event.text.unicode;
				}

				++(bind->c);
			}
		}
	}
}

void EventManager::Update() // will run bindings!!
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.code))) {
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

		//Control here.
		if (bind->events.size() == bind->c)
		{
			auto stateCallbacks = callbacks.find(currentState);
			auto otherCallbacks = callbacks.find(StateType(0));

			if (stateCallbacks != callbacks.end())
			{
				auto callItr = stateCallbacks->second.find(bind->name);
				if (callItr != stateCallbacks->second.end())
				{
					// Pass in information about events.
					callItr->second(&bind->details);
				}
			}

			if (otherCallbacks != callbacks.end())
			{
				auto callItr = otherCallbacks->second.find(bind->name);
				if (callItr != otherCallbacks->second.end())
				{
					// Pass in information about events
					callItr->second(&bind->details);
				}
			}
		}

		bind->c = 0;
		//bind->details.Clear();
	}
}

void EventManager::SetCurrentState(StateType state)
{
	currentState = state;
}

void EventManager::LoadBindings(std::string keyFilePath) {

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
		keystream >> callbackName; // extraction from the 'keystream' into the variable 'callbackName'.

		Binding* bind = new Binding(callbackName);

		while (!keystream.eof())
		{
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);

			if (end == std::string::npos) // (std::string::npos is typically used for invalid or not-found pos.)
			{
				delete bind;
				bind = nullptr;
				break;
			}

			EventType type = EventType(stoi(keyval.substr(start, end - start))); //<-::

			int code = stoi(keyval.substr(end + delimiter.length(), //::->
				keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo.code = code;

			bind->BindEvent(type, eventInfo);
		}

		if (!AddBinding(bind))
		{
			delete bind;
		}

		bind = nullptr;

	}

	bindingConfigs.close();
}