#ifndef __HUDLayer__
#define __HUDLayer__

#pragma once
#include "cocos2d.h"
#include "JoyStick.h"


USING_NS_CC;


class HUDLayer : public Layer
{
private:
	JoyStick* joyStick;
	cocos2d::Label *TestLabel;
public:
	HUDLayer();
	~HUDLayer();
	virtual bool init();
	CREATE_FUNC(HUDLayer);
};

#endif