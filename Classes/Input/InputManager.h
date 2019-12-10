#pragma once
#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "SingletonTemplate.h"
#include "InputAction.h"
#include "InputActionMap.h"

class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;
public:
	InputManager();
	~InputManager();

	void AddAction(InputAction* action);
	void AddActionMap(InputActionMap* action);

	void UpdatePressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void UpdatePressed(cocos2d::EventMouse::MouseButton keyCode);
	void UpdateReleased(cocos2d::EventKeyboard::KeyCode keyCode);
	void UpdateReleased(cocos2d::EventMouse::MouseButton keyCode);
	void Update();

	InputAction* GetAction(std::string name);
	InputActionMap* GetActionMap(std::string name);

private:
	std::vector<InputAction*> actions;
	std::vector<InputActionMap*> actionMaps;
};

