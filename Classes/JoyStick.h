#pragma once
#include "cocos2d.h"
USING_NS_CC;

class JoyStick
{
private:
	bool active;
public:
	JoyStick();
	~JoyStick();
	JoyStick(std::string backGround, std::string joyStick, float scale);
	void Active();
	void Inactive();
	void SetJoyStickPos(Vec2 position);
	Sprite* backGroundSP;
	Sprite* joyStickSP;
	float radius;
	CCPoint centerPoint;    // center
	CCPoint currentPoint;   // current position

	float DistanceBetweenCenterAndJoyStick();
	float GetPercentageDistanceBetweenCenterAndJoyStick();
};
