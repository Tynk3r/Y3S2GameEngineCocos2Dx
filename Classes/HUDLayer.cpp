#include "HUDLayer.h"
#include "Nodes.h"

USING_NS_CC;

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


	joyStick = new JoyStick("JoyStickBackGround.png", "JoyStickHandle.png", 0.3);
	this->addChild(joyStick->joyStickSP, 1);
	this->addChild(joyStick->backGroundSP,0);
	joyStick->Inactive();

	//auto _spriteToMove = joyStick->joyStickSP;
	//_spriteToMove->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//this->addChild(_spriteToMove);

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HUDLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HUDLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HUDLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


bool HUDLayer::onTouchBegan(CCTouch * pTouch, CCEvent * pEvent)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Point touchLoc = pTouch->getLocationInView();
	touchLoc = cocos2d::CCDirector::sharedDirector()->convertToGL(touchLoc);

	if (touchLoc.x < visibleSize.width * 0.5)
	{
		joyStick->Active();
		
		joyStick->backGroundSP->setPosition(touchLoc);
		joyStick->joyStickSP->setPosition(joyStick->backGroundSP->getPosition());
		joyStick->centerPoint = joyStick->backGroundSP->getPosition();
		joyStick->currentPoint = touchLoc;

		if (joyStick->joyStickSP->getBoundingBox().containsPoint(touchLoc))
		{
			return true;
		}
	}


	return false;
}

void HUDLayer::onTouchMoved(CCTouch * pTouch, CCEvent * pEvent)
{
	Point touchLoc = pTouch->getLocationInView();
	touchLoc = cocos2d::CCDirector::sharedDirector()->convertToGL(touchLoc);

	if (ccpDistance(touchLoc, joyStick->centerPoint) > joyStick->radius)
	{
		joyStick->currentPoint = ccpAdd(joyStick->centerPoint, ccpMult(ccpNormalize(ccpSub(touchLoc, joyStick->centerPoint)), joyStick->radius));
		joyStick->joyStickSP->setPosition(joyStick->currentPoint);
	}
	else
	{
		joyStick->currentPoint = touchLoc;
		joyStick->joyStickSP->setPosition(joyStick->currentPoint);
	}
}

void HUDLayer::onTouchEnded(CCTouch * pTouch, CCEvent * pEvent)
{
	joyStick->Inactive();
}
