#ifndef __HUDLayer__
#define __HUDLayer__

#pragma once
#include "cocos2d.h"
#include "JoyStick.h"


USING_NS_CC;


class HUDLayer : public Layer
{
private:
	cocos2d::Label *TestLabel;
public:
	HUDLayer();
	~HUDLayer();
	virtual bool init();
	CREATE_FUNC(HUDLayer);
	void addJoystickToLayer();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	JoyStick* joyStick;
};

#endif