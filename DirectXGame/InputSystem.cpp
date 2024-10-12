#include "InputSystem.h"
#include <Windows.h>

#include "DebugUtils.h"


InputSystem::InputSystem()
= default;


InputSystem::~InputSystem()
= default;

void InputSystem::update()
{
	if (::GetKeyboardState(keysState))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (keysState[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = setListeners.begin();

				while (it != setListeners.end())
				{
					(*it)->onKeyDown(i);
					++it;
				}
			}
			else // KEY IS UP
			{
				if (keysState[i] != oldKeysState[i])
				{
					std::unordered_set<InputListener*>::iterator it = setListeners.begin();

					while (it != setListeners.end())
					{
						(*it)->onKeyUp(i);
						++it;
					}
				}

			}

		}
		// store current keys state to old keys state buffer
		::memcpy(oldKeysState, keysState, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	setListeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	setListeners.erase(listener);
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}