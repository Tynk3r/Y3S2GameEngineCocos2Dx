#pragma once
#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "SingletonTemplate.h"
#include "InputAction.h"

class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;
public:
	InputManager();
	~InputManager();

	void AddAction(InputAction* action);

	void UpdatePressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void UpdateReleased(cocos2d::EventKeyboard::KeyCode keyCode);
	void Update();

	InputAction* GetAction(std::string name);

private:
	std::vector<InputAction*> actions;
};

