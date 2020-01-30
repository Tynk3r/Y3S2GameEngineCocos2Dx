#include "JoyStick.h"



JoyStick::JoyStick()
{
}

JoyStick::~JoyStick()
{
}

JoyStick::JoyStick(std::string backGround, std::string joyStick)
{
	JSNode = new Node();

	Texture2D *backGroundtexture = Director::getInstance()->getTextureCache()->addImage(backGround);
	Rect backGroundtexturerect = Rect::ZERO;
	backGroundtexturerect.size = backGroundtexture->getContentSize();
	Sprite *backGroundSprite = Sprite::createWithTexture(backGroundtexture, backGroundtexturerect);

	Texture2D *joySticktexture = Director::getInstance()->getTextureCache()->addImage(backGround);
	Rect joySticktexturerect = Rect::ZERO;
	joySticktexturerect.size = joySticktexture->getContentSize();
	Sprite *joyStickSprite = Sprite::createWithTexture(joySticktexture, joySticktexturerect);


	Sprite* BGSprite = backGroundSprite;
	BGSprite->setPosition(Vec2(0, 0));
	BGSprite->setName("JoyStickBackGround");
	JSNode->addChild(BGSprite);

	Sprite* JSSprite = joyStickSprite;
	JSSprite->setPosition(backGroundSprite->getPosition());
	JSSprite->setName("JoyStick");
	JSNode->addChild(JSSprite);
}
