#pragma once
#include <iostream>
#include <vector>
#include "cocos2d.h"

class InputAction
{
public:
	InputAction();
	~InputAction();

	void AddBinding(cocos2d::EventKeyboard::KeyCode binding);
	void RemoveBinding(cocos2d::EventKeyboard::KeyCode binding);
	void SetName(std::string name_);
	void SetEnabled(bool enabled_);

	bool Pressed();
	bool Released();
	bool Held();

	std::string Name();

	void UpdatePressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void UpdateReleased(cocos2d::EventKeyboard::KeyCode keyCode);
	void Update();

private:
	std::string name;
	std::vector<cocos2d::EventKeyboard::KeyCode> bindings;

	bool pressed;
	bool released;
	bool held;
	bool enabled;
};

