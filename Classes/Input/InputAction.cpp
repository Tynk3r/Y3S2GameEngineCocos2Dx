#include "InputAction.h"
#include "InputManager.h"

InputAction::InputAction(std::string name_)
{
	pressed = false;
	released = false;
	held = false;
	enabled = true;
	name = name_;
	//Adds to input manager immediately so it can update and get referenced through the manager.
	InputManager::GetInstance()->AddAction(this);
}


InputAction::~InputAction()
{
}

void InputAction::AddBinding(cocos2d::EventKeyboard::KeyCode binding)
{
	for (int i = 0; i < bindings.size(); i++)
	{
		if (bindings[i] == binding) //Doesn't add if already there
			return;
	}
	bindings.push_back(binding);
	return;
}

void InputAction::AddBinding(cocos2d::EventMouse::MouseButton binding)
{
	for (int i = 0; i < mouseBindings.size(); i++)
	{
		if (mouseBindings[i] == binding) //Doesn't add if already there
			return;
	}
	mouseBindings.push_back(binding);
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

void InputAction::RemoveBinding(cocos2d::EventMouse::MouseButton binding)
{
	for (int i = 0; i < mouseBindings.size(); i++)
	{
		if (mouseBindings[i] == binding)
		{
			mouseBindings.erase(mouseBindings.begin() + i);
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
	if (!enabled_) //Resets and stops all updates
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

void InputAction::UpdatePressed(cocos2d::EventMouse::MouseButton keyCode)
{
	if (!enabled)
		return;
	for (int i = 0; i < mouseBindings.size(); i++)
	{
		if (mouseBindings[i] == keyCode)
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

void InputAction::UpdateReleased(cocos2d::EventMouse::MouseButton keyCode)
{
	if (!enabled)
		return;
	for (int i = 0; i < mouseBindings.size(); i++)
	{
		if (mouseBindings[i] == keyCode)
		{
			released = true;
			held = false;
			return;
		}
	}
}

void InputAction::Update()
{
	//So pressed and released is true only for one frame
	if (!enabled)
		return;
	pressed = false;
	released = false;
}
