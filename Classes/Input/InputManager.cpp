#include "InputManager.h"

InputManager::InputManager()
{
	mouseData = nullptr;
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

void InputManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->UpdatePressed(keyCode);
	}
}

void InputManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->UpdateReleased(keyCode);
	}
}

void InputManager::onMouseDown(cocos2d::EventMouse * e)
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->UpdatePressed(e->getMouseButton());
	}
}

void InputManager::onMouseUp(cocos2d::EventMouse * e)
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->UpdateReleased(e->getMouseButton());
	}
}

void InputManager::onMouseMove(cocos2d::EventMouse * e)
{
	delete mouseData;
	mouseData = nullptr;
	mouseData = new cocos2d::EventMouse(*e);
}

void InputManager::SetListeners(cocos2d::Node * node)
{
	//Keyboard Event
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
	//Mouse Event
	auto listenerMouse = cocos2d::EventListenerMouse::create();
	listenerMouse->onMouseDown = CC_CALLBACK_1(InputManager::onMouseDown, this);
	listenerMouse->onMouseUp = CC_CALLBACK_1(InputManager::onMouseUp, this);
	listenerMouse->onMouseMove = CC_CALLBACK_1(InputManager::onMouseMove, this);
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerMouse, node);
}

void InputManager::Update()
{
	for (int i = 0; i < actions.size(); i++)
	{
		actions[i]->Update();
	}
}

cocos2d::EventMouse* InputManager::GetMouseData()
{
	return mouseData;
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
