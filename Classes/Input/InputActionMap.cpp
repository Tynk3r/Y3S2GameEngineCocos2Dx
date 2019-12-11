#include "InputActionMap.h"
#include "InputManager.h"

InputActionMap::InputActionMap(std::string name_)
{
	name = name_;
	enabled = true;
	//Adds to input manager immediately so it can get referenced through the manager.
	InputManager::GetInstance()->AddActionMap(this);
}

InputActionMap::~InputActionMap()
{
}

void InputActionMap::AddAction(InputAction * action)
{
	for (int i = 0; i < actions.size(); i++)
	{
		if (actions[i]->Name() == action->Name()) //Doesn't add if already there
			return;
	}
	actions.push_back(action);
}

void InputActionMap::SetEnabled(bool enabled_)
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->SetEnabled(enabled_);
	}
	enabled = enabled_;
}

void InputActionMap::SetName(std::string name_)
{
	name = name_;
}

std::string InputActionMap::Name()
{
	return name;
}

bool InputActionMap::Enabled()
{
	return enabled;
}

InputAction * InputActionMap::GetAction(std::string name)
{
	try
	{
		for (int i = 0; i < actions.size(); i++)
		{
			if (actions[i]->Name() == name)
				return actions[i];
		}
		throw 1;
	}
	catch (int e)
	{
		cocos2d::log("Input action name not found");
	}
}
