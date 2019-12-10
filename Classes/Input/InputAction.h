#pragma once
#include <iostream>
#include <vector>
#include "cocos2d.h"

class InputAction
{
public:
	InputAction(std::string name_);
	~InputAction();

	void AddBinding(cocos2d::EventKeyboard::KeyCode binding);
	void AddBinding(cocos2d::EventMouse::MouseButton binding);
	void RemoveBinding(cocos2d::EventKeyboard::KeyCode binding);
	void RemoveBinding(cocos2d::EventMouse::MouseButton binding);
	void SetName(std::string name_);
	void SetEnabled(bool enabled_);

	bool Pressed();
	bool Released();
	bool Held();

	std::string Name();

	void UpdatePressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void UpdatePressed(cocos2d::EventMouse::MouseButton keyCode);
	void UpdateReleased(cocos2d::EventKeyboard::KeyCode keyCode);
	void UpdateReleased(cocos2d::EventMouse::MouseButton keyCode);
	void Update();

private:
	std::string name;
	std::vector<cocos2d::EventKeyboard::KeyCode> bindings;
	std::vector<cocos2d::EventMouse::MouseButton> mouseBindings;

	bool pressed;
	bool released;
	bool held;
	bool enabled;
};

