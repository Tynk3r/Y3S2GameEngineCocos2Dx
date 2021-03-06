#include "JoyStick.h"



JoyStick::JoyStick()
{
}

JoyStick::~JoyStick()
{
}

JoyStick::JoyStick(std::string backGroundFile, std::string joyStickFile, float scale)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Texture2D *backGroundtexture = Director::getInstance()->getTextureCache()->addImage(backGroundFile);
	Rect backGroundrect = Rect::ZERO;
	backGroundrect.size = backGroundtexture->getContentSize();
	Sprite *backGroundframe = Sprite::createWithTexture(backGroundtexture, backGroundrect);
	

	Texture2D *joySticktexture = Director::getInstance()->getTextureCache()->addImage(joyStickFile);
	Rect joyStickrect = Rect::ZERO;
	joyStickrect.size = joySticktexture->getContentSize();
	Sprite *joyStickframe = Sprite::createWithTexture(joySticktexture, joyStickrect);

	backGroundSP = backGroundframe;
	backGroundSP->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backGroundSP->setName("BackGroundJoyStick");
	backGroundSP->setScale(scale * 2);

	joyStickSP = joyStickframe;
	joyStickSP->setPosition(backGroundSP->getPosition());
	joyStickSP->setName("JoyStick");
	joyStickSP->setScale(scale);

	backGroundSP->setVisible(false);
	joyStickSP->setVisible(false);

	radius = backGroundSP->getContentSize().width * 0.3f;
}

void JoyStick::Active()
{
	if (!active)
	{
		backGroundSP->setVisible(true);
		joyStickSP->setVisible(true);
		active = true;
	}
}

void JoyStick::Inactive()
{
	if (active)
	{
		backGroundSP->setVisible(false);
		joyStickSP->setVisible(false);
		active = false;
	}
}

bool JoyStick::IsActive()
{
	return active;
}

float JoyStick::DistanceBetweenCenterAndJoyStick()
{
	return joyStickSP->getPosition().distance(backGroundSP->getPosition());
}

float JoyStick::GetPercentageDistanceBetweenCenterAndJoyStick()
{
	return DistanceBetweenCenterAndJoyStick() / radius;
}

cocos2d::Vec2 JoyStick::GetDir()
{
	return (joyStickSP->getPosition() - backGroundSP->getPosition()).getNormalized();
}

