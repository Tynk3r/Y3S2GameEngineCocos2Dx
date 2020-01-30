#include "HUDLayer.h"
#include "Nodes.h"

HUDLayer::HUDLayer()
{
}


HUDLayer::~HUDLayer()
{
}

bool HUDLayer::init() {

	if (!CCLayer::init()) 
	{
		CCLOG("you should not see this");
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TestLabel = Label::createWithTTF("TEST", "fonts/arial.ttf", visibleSize.height * 0.1);
	TestLabel->setColor(Color3B::WHITE);
	TestLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(TestLabel);

	auto spriteNode = Node::create();
	auto TestNode = Nodes::CreateNodeUsingTextureCache(spriteNode, "mainSprite", "Blue_Front1.png", Vec2(0, 0), Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y), 1);
	addChild(TestNode);

	joyStick = new JoyStick("Asteroids/asteroid_01.png", "Asteroids/asteroid_01.png");
	addChild(joyStick->JSNode);

	return true;
}
