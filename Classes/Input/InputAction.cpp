#include "InputAction.h"
#include "InputManager.h"

InputAction::InputAction()
{
	pressed = false;
	released = false;
	held = false;
	enabled = true;
	InputManager inputManager;
	inputManager.GetInstance()->AddAction(this);
}


InputAction::~InputAction()
{
}

void InputAction::AddBinding(cocos2d::EventKeyboard::KeyCode binding)
{
	for (int i = 0; i < bindings.size(); i++)
	{
		if (bindings[i] == binding)
			return;
	}
	bindings.push_back(binding);
	return;
}

void InputAction::RemoveBinding(cocos2d::EventKeyboard::KeyCode binding)
{
	for (int i = 0; i < bindings.size(); i++)
	{
		if (bindings[i] == binding)
		{
			bindings.erase(bindings.begin() + i);
			return;
		}
	}
}

void InputAction::SetName(std::string name_)
{
	name = name_;
}

void InputAction::SetEnabled(bool enabled_)
{
	if (!enabled_)
	{
		held = false;
		released = false;
		pressed = false;
	}
	enabled = enabled_;
}

bool InputAction::Pressed()
{
	return pressed;
}

bool InputAction::Released()
{
	return released;
}

bool InputAction::Held()
{
	return held;
}

std::string InputAction::Name()
{
	return name;
}

void InputAction::UpdatePressed(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (!enabled)
		return;
	for (int i = 0; i < bindings.size(); i++)
	{
		if (bindings[i] == keyCode)
		{
			pressed = true;
			held = true;
			return;
		}
	}
}

void InputAction::UpdateReleased(cocos2d::EventKeyboard::KeyCode keyCode)
{
	if (!enabled)
		return;
	for (int i = 0; i < bindings.size(); i++)
	{
		if (bindings[i] == keyCode)
		{
			released = true;
			held = false;
			return;
		}
	}
}

void InputAction::Update()
{
	if (!enabled)
		return;
	pressed = false;
	released = false;
}
