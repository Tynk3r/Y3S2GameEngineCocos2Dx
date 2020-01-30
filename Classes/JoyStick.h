#pragma once
#include "cocos2d.h"
USING_NS_CC;

class JoyStick
{
private:
	Sprite backGround;
	Sprite joyStick;
public:
	JoyStick();
	~JoyStick();
	JoyStick(std::string backGround, std::string joyStick);
	Node* JSNode;
	void SetJoyStickPos(Vec2 position);

};
