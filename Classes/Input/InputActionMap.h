#pragma once
#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "SingletonTemplate.h"
#include "InputAction.h"

class InputActionMap
{
public:
	InputActionMap(std::string name_);
	~InputActionMap();

	void AddAction(InputAction* action);
	void SetEnabled(bool enabled_);
	void SetName(std::string name_);
	std::string Name();
	bool Enabled();

	InputAction* GetAction(std::string name);

private:
	bool enabled;
	std::string name;
	std::vector<InputAction*> actions;
};

