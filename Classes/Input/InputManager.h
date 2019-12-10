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

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void onMouseDown(cocos2d::EventMouse* e);
	void onMouseUp(cocos2d::EventMouse* e);
	void onMouseMove(cocos2d::EventMouse* e);

	void SetListeners(cocos2d::Node* node);

	void Update();

	cocos2d::EventMouse* GetMouseData();

	InputAction* GetAction(std::string name);
	InputActionMap* GetActionMap(std::string name);

private:
	cocos2d::EventMouse* mouseData;
	std::vector<InputAction*> actions;
	std::vector<InputActionMap*> actionMaps;
};

