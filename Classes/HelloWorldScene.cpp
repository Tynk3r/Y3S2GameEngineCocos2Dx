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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Input/InputManager.h"
#include "Scene Management/SceneManager.h"
#include "SceneManagementTestScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

	// Post Processing
	proPostProcess = GLProgram::createWithFilenames("Basic.vsh", "CharEffect.fsh");
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);
	proPostProcess->link();
	proPostProcess->updateUniforms();
	Vec2 mLoc(0.5f, 0.5f);
	GLProgramState::getOrCreateWithGLProgram(proPostProcess)->setUniformVec2("loc", mLoc);
	
	rendtex = RenderTexture::create(visibleSize.width, visibleSize.height);
	rendtex->retain();

	rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setTextureRect(Rect(0, 0, rendtex->getSprite()->getTexture()->getContentSize().width, rendtex->getSprite()->getTexture()->getContentSize().height));
	rendtexSprite->setAnchorPoint(Point::ZERO);
	rendtexSprite->setPosition(Point::ZERO);
	rendtexSprite->setFlippedY(true);
	rendtexSprite->setShaderProgram(proPostProcess);
	this->addChild(rendtexSprite, 2);

	//Init containers
	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");
	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");

	//Create static items
	auto spriteWidth = Sprite::create("ZigzagGrass_Mud_Round.png")->getContentSize().width;
	int numOfBlocks = ceil(playingSize.width / spriteWidth);
	for (int i = 0; i < numOfBlocks; i++)
	{
		auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(0 + i * spriteWidth, playingSize.height / 2);
		//sprite->setPosition(0, 0);

		//Create static PhysicsBody
		auto physicsBody = PhysicsBody::createBox(Size(sprite->getContentSize().width, sprite->getContentSize().height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody->setDynamic(false);
		sprite->addComponent(physicsBody);

		nodeItems->addChild(sprite, 0);
	}

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

	InputAction* makeBrighter = new InputAction("Make Brighter");
	makeBrighter->AddBinding(EventKeyboard::KeyCode::KEY_EQUAL);

	InputAction* makeDarker = new InputAction("Make Darker");
	makeDarker->AddBinding(EventKeyboard::KeyCode::KEY_MINUS);

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

	////Keyboard Event
	//auto listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	//listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	////Mouse Event
	//auto listenerMouse = EventListenerMouse::create();
	//listenerMouse->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseDown, this);
	//listenerMouse->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);

	//Update
	this->schedule(schedule_selector(HelloWorld::Update));
    
    return true;
}

void HelloWorld::graySprite(Sprite* sprite)
{
	if (sprite)
	{
		GLProgram* p = new GLProgram();
		p->initWithFilenames("Basic.vsh", "gray.fsh");
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
		p->link();
		p->updateUniforms();
		sprite->setShaderProgram(p);
	}
}

void HelloWorld::charEffectSprite(Sprite* sprite)
{
	if (sprite)
	{
		GLProgram* p = new GLProgram();
		p->initWithFilenames("Basic.vsh", "CharEffect.fsh");
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
		p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
		p->link();
		p->updateUniforms();
		GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(p);
		Vec2 mLoc(0.5f, 0.5f);
		state->setUniformVec2("loc", mLoc);
		sprite->setShaderProgram(p);
	}
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::Update(float interval)
{
	InputManager::GetInstance()->Update();

	if (InputManager::GetInstance()->GetAction("Make Brighter")->Held())
		darkness = clampf(darkness - .1f, 0.f, 10.f);
	else if(InputManager::GetInstance()->GetAction("Make Darker")->Held())
		darkness = clampf(darkness + .1f, 0.f, 10.f);
	GLProgramState::getOrCreateWithGLProgram(proPostProcess)->setUniformFloat("darkness", darkness);

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
		std::vector<std::string> tempResources;
		tempResources.push_back("big.png");
		tempResources.push_back("big - Copy.png");
		tempResources.push_back("big - Copy (2).png");
		tempResources.push_back("big - Copy (3).png");
		tempResources.push_back("big - Copy (4).png");
		tempResources.push_back("big - Copy (5).png");
		tempResources.push_back("big - Copy (6).png");
		tempResources.push_back("big - Copy (7).png");
		tempResources.push_back("big - Copy (8).png");

		SceneManager::GetInstance()->ReplaceScene(SceneManagementTestScene::createScene(), tempResources);
	}
	auto curSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	GLProgramState::getOrCreateWithGLProgram(proPostProcess)->setUniformVec2("loc", Vec2(curSprite->getPositionX() / visibleSize.width, curSprite->getPositionY() / visibleSize.height));

	// Post Processing
	rendtex->beginWithClear(.0f, .0f, .0f, .0f);
	this->visit();
	rendtex->end();
	rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setShaderProgram(proPostProcess);
}
