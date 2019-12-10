/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "SceneManagementTestScene.h"
#include "SimpleAudioEngine.h"
#include "Input/InputManager.h"
#include "Scene Management/SceneManager.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* SceneManagementTestScene::createScene()
{
    return SceneManagementTestScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SceneManagementTestSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SceneManagementTestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

	this->getPhysicsWorld()->setDebugDrawMask(0xffff);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	//Init containers
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");
	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");

	//Create static items
	auto spriteWidth = Sprite::create("ZigzagGrass_Mud_Round.png")->getContentSize().width;

	//Create sprites
	auto mainSprite = Sprite::create("Blue_Front1.png");
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(100, playingSize.height / 2 + spriteWidth + 30);
	mainSprite->setName("mainSprite");

	//Create static PhysicsBody
	auto physicsBody = PhysicsBody::createBox(Size(mainSprite->getContentSize().width, mainSprite->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
	physicsBody->setDynamic(true);
	mainSprite->addComponent(physicsBody);

	spriteNode->addChild(mainSprite, 1);

	//Load Spritesheet
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("sprite.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("sprite.plist");

	//Creating Sprites from Spritesheet
	auto Sprite1 = Sprite::createWithSpriteFrameName("Blue_Back1.png");
	spritebatch->addChild(Sprite1);
	addChild(spritebatch);

	//Load idle animation frames
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));

	//Create animation
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animateIdle = Animate::create(animation);

	//Run animation
	mainSprite->runAction(RepeatForever::create(animateIdle));

	//Add containers to scene
	this->addChild(spriteNode, 1);
	this->addChild(nodeItems, 1);

	//Creating Inputs
	InputManager::GetInstance()->SetListeners(this);

	InputAction* moveLeft = new InputAction("Move Left");
	moveLeft->AddBinding(EventKeyboard::KeyCode::KEY_A);
	moveLeft->AddBinding(EventKeyboard::KeyCode::KEY_LEFT_ARROW);

	InputAction* moveRight = new InputAction("Move Right");
	moveRight->AddBinding(EventKeyboard::KeyCode::KEY_D);
	moveRight->AddBinding(EventKeyboard::KeyCode::KEY_RIGHT_ARROW);

	InputAction* mouseMovement = new InputAction("Mouse Movement");
	mouseMovement->AddBinding(EventMouse::MouseButton::BUTTON_LEFT);

	InputAction* toggleMovement = new InputAction("Toggle Movement");
	toggleMovement->AddBinding(EventKeyboard::KeyCode::KEY_P);

	InputAction* changeScene = new InputAction("Change Scene");
	changeScene->AddBinding(EventKeyboard::KeyCode::KEY_O);

	InputActionMap* playerMovement = new InputActionMap("Player Movement");
	playerMovement->AddAction(moveLeft);
	playerMovement->AddAction(moveRight);
	playerMovement->AddAction(mouseMovement);

	//Update
	this->schedule(schedule_selector(SceneManagementTestScene::Update));

    
    return true;
}


void SceneManagementTestScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void SceneManagementTestScene::Update(float interval)
{
	if (InputManager::GetInstance()->GetAction("Move Left")->Held())
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		//auto moveEvent = MoveBy::create(0.0f, Vec2(-1.0f, 0.f));
		//curSprite->runAction(moveEvent);
		
		//Physics movement
		PhysicsBody* curPhysics = curSprite->getPhysicsBody();
		curPhysics->setVelocity(Vec2(-100.0f, curPhysics->getVelocity().y));
	}
	else if (InputManager::GetInstance()->GetAction("Move Right")->Held())
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		//auto moveEvent = MoveBy::create(0.0f, Vec2(1.0f, 0.f));
		//curSprite->runAction(moveEvent);
		
		//Physics movement
		PhysicsBody* curPhysics = curSprite->getPhysicsBody();
		curPhysics->setVelocity(Vec2(100.0f, curPhysics->getVelocity().y));
	}
	else if (InputManager::GetInstance()->GetAction("Mouse Movement")->Pressed())
	{
		auto currSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto moveEvent = MoveTo::create(Vec2(InputManager::GetInstance()->GetMouseData()->getCursorX(), InputManager::GetInstance()->GetMouseData()->getCursorY()).getDistance(currSprite->getPosition()) / 100.0f, Vec2(InputManager::GetInstance()->GetMouseData()->getCursorX(), InputManager::GetInstance()->GetMouseData()->getCursorY()));
		currSprite->stopAllActions();
		currSprite->runAction(moveEvent);

		//Animation

		//Load movement animation
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(4);
		animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));

		Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
		Animate* animateMove = Animate::create(animation);

		currSprite->runAction(RepeatForever::create(animateMove));
	}
	else
	{
		auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
	
		//Physics movement
		PhysicsBody* curPhysics = curSprite->getPhysicsBody();
		curPhysics->setVelocity(Vec2(0.0f, curPhysics->getVelocity().y));
	}

	if (InputManager::GetInstance()->GetAction("Toggle Movement")->Pressed())
	{
		InputManager::GetInstance()->GetActionMap("Player Movement")->SetEnabled(!InputManager::GetInstance()->GetActionMap("Player Movement")->Enabled());
	}

	if (InputManager::GetInstance()->GetAction("Change Scene")->Pressed())
	{
		SceneManager::GetInstance()->ReplaceScene(HelloWorld::createScene());
	}

	InputManager::GetInstance()->Update();

}
