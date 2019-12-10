#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
	for (int i = 0; i < actions.size(); i++)
	{
		delete actions[i];
		actions[i] = nullptr;
	}
	for (int i = 0; i < actionMaps.size(); i++)
	{
		delete actionMaps[i];
		actionMaps[i] = nullptr;
	}
}

void InputManager::AddAction(InputAction* action)
{
	for (int i = 0; i < actions.size(); i++)
	{
		if (actions[i]->Name() == action->Name())
			return;
	}
	actions.push_back(action);
}

void InputManager::AddActionMap(InputActionMap * action)
{
	for (int i = 0; i < actionMaps.size(); i++)
	{
		if (actionMaps[i]->Name() == action->Name())
			return;
	}
	actionMaps.push_back(action);
}

void InputManager::UpdatePressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->UpdatePressed(keyCode);
	}
}

void InputManager::UpdatePressed(cocos2d::EventMouse::MouseButton keyCode)
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->UpdatePressed(keyCode);
	}
}

void InputManager::UpdateReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->UpdateReleased(keyCode);
	}
}

void InputManager::UpdateReleased(cocos2d::EventMouse::MouseButton keyCode)
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->UpdateReleased(keyCode);
	}
}

void InputManager::Update()
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->Update();
	}
}

InputAction* InputManager::GetAction(std::string name)
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

InputActionMap * InputManager::GetActionMap(std::string name)
{
	try
	{
		for (int i = 0; i < actionMaps.size(); i++)
		{
			if (actionMaps[i]->Name() == name)
				return actionMaps[i];
		}
		throw 1;
	}
	catch (int e)
	{
		cocos2d::log("Input action map name not found");
	}
}
