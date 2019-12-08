#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
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

void InputManager::UpdatePressed(cocos2d::EventKeyboard::KeyCode keyCode)
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
		std::cout << "Input action name not found" << std::endl;
	}
}
