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

#define DEFAULT_FORCE 100.f
#define SPEED_LIMIT 100.f
#define DEFAULT_SPIN_SPEED .01f
#define SPIN_SPEED_LIMIT 5.f

#include "SpaceshipScene.h"
#include "SimpleAudioEngine.h"
#include "Input/InputManager.h"
#include "Scene Management/SceneManager.h"
#include "SceneManagementTestScene.h"
#include "Anim/CAnimation.h"

USING_NS_CC;

Scene* SpaceshipScene::createScene()
{
	return SpaceshipScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SpaceshipScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	this->getPhysicsWorld()->setDebugDrawMask(0xffff);
	this->getPhysicsWorld()->setGravity(Vec2(0.f, 0.f));

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

	//Create sprites
	auto mainSprite = Sprite::create("Spaceship.png");
	mainSprite->setAnchorPoint(Vec2(0.5, 0.5));
	mainSprite->setPosition(visibleSize.width * .5f, visibleSize.height * .5f);
	mainSprite->setScale(.1f);
	mainSprite->setName("mainSprite");
	//Create static PhysicsBody
	auto physicsBody = PhysicsBody::createBox(Size(mainSprite->getContentSize().width, mainSprite->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
	physicsBody->setDynamic(true);
	physicsBody->setVelocityLimit(SPEED_LIMIT);
	physicsBody->setAngularVelocityLimit(SPIN_SPEED_LIMIT);
	mainSprite->addComponent(physicsBody);

	auto asteroid1 = Sprite::create("Asteroids/asteroid_01.png");
	asteroid1->setAnchorPoint(Vec2(0.5, 0.5));
	asteroid1->setPosition(visibleSize.width * .25f, visibleSize.height * .25f);
	asteroid1->setScale(1.f);
	asteroid1->setName("asteroid1");

	string asteroidSprites[4] = { "Asteroids/asteroid_01.png","Asteroids/asteroid_02.png","Asteroids/asteroid_03.png","Asteroids/asteroid_04.png" };
	Animate* animateAsteroids = CAnimation::createAnimation(asteroidSprites, 4, 81, 101, 0.5f);

	asteroid1->runAction(RepeatForever::create(animateAsteroids));


	//Create static PhysicsBody
	physicsBody = PhysicsBody::createBox(Size(asteroid1->getContentSize().width, asteroid1->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
	physicsBody->setDynamic(true);
	physicsBody->setVelocityLimit(SPEED_LIMIT);
	physicsBody->setAngularVelocityLimit(SPIN_SPEED_LIMIT);
	asteroid1->addComponent(physicsBody);

	spriteNode->addChild(mainSprite, 1);
	spriteNode->addChild(asteroid1, 1);

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
	//mainSprite->runAction(RepeatForever::create(animateIdle));

	//Add containers to scene
	this->addChild(spriteNode, 1);
	this->addChild(nodeItems, 1);

	//Creating Inputs
	InputManager::GetInstance()->SetListeners(this);

	// move in front direction
	InputAction* backThrusters = new InputAction("BackThrusters");
	backThrusters->AddBinding(EventKeyboard::KeyCode::KEY_W);
	backThrusters->AddBinding(EventKeyboard::KeyCode::KEY_UP_ARROW);
	// move in back direction
	InputAction* frontThrusters = new InputAction("FrontThrusters");
	frontThrusters->AddBinding(EventKeyboard::KeyCode::KEY_S);
	frontThrusters->AddBinding(EventKeyboard::KeyCode::KEY_DOWN_ARROW);
	// spin clockwise
	InputAction* clockwiseSpinThrusters = new InputAction("ClockwiseSpinThrusters");
	clockwiseSpinThrusters->AddBinding(EventKeyboard::KeyCode::KEY_D);
	clockwiseSpinThrusters->AddBinding(EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
	// spin counter clockwise
	InputAction* cClockwiseSpinThrusters = new InputAction("CClockwiseSpinThrusters");
	cClockwiseSpinThrusters->AddBinding(EventKeyboard::KeyCode::KEY_A);
	cClockwiseSpinThrusters->AddBinding(EventKeyboard::KeyCode::KEY_LEFT_ARROW);

	InputActionMap* playerMovement = new InputActionMap("Player Movement");
	playerMovement->AddAction(backThrusters);
	playerMovement->AddAction(frontThrusters);

	InputAction* makeBrighter = new InputAction("Make Brighter");
	makeBrighter->AddBinding(EventKeyboard::KeyCode::KEY_EQUAL);

	InputAction* makeDarker = new InputAction("Make Darker");
	makeDarker->AddBinding(EventKeyboard::KeyCode::KEY_MINUS);

	//Sounds
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("BackgroundMusic.wav", true);

	//Update
	this->schedule(schedule_selector(SpaceshipScene::Update));

	return true;
}


void SpaceshipScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

void SpaceshipScene::Update(float interval)
{
	auto spaceship = this->getChildByName("spriteNode")->getChildByName("mainSprite");
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (InputManager::GetInstance()->GetAction("Make Brighter")->Held())
		darkness = clampf(darkness - .1f, 0.f, 10.f);
	else if (InputManager::GetInstance()->GetAction("Make Darker")->Held())
		darkness = clampf(darkness + .1f, 0.f, 10.f);
	GLProgramState::getOrCreateWithGLProgram(proPostProcess)->setUniformFloat("darkness", darkness);

	if (spaceship != nullptr && spaceship->getPhysicsBody() != nullptr)
	{
		//Physics movement
		PhysicsBody* spaceshipPhysicsBody = spaceship->getPhysicsBody();

		// Spin Thrusterz
		if (InputManager::GetInstance()->GetAction("ClockwiseSpinThrusters")->Held())
		{
			spaceshipPhysicsBody->setAngularVelocity(spaceshipPhysicsBody->getAngularVelocity() - DEFAULT_SPIN_SPEED);
		}
		else if (InputManager::GetInstance()->GetAction("CClockwiseSpinThrusters")->Held())
		{
			spaceshipPhysicsBody->setAngularVelocity(spaceshipPhysicsBody->getAngularVelocity() + DEFAULT_SPIN_SPEED);
		}

		// Update Direction
		Vec2 spaceshipDirection(cosf(CC_DEGREES_TO_RADIANS(spaceshipPhysicsBody->getRotation())), sinf(CC_DEGREES_TO_RADIANS(spaceshipPhysicsBody->getRotation())));
		spaceshipDirection.normalize();

		// Thrusterz
		if (InputManager::GetInstance()->GetAction("BackThrusters")->Held())
		{
			spaceshipPhysicsBody->applyForce(DEFAULT_FORCE * Vec2(0, 1));
		}
		else if (InputManager::GetInstance()->GetAction("FrontThrusters")->Held())
		{
			spaceshipPhysicsBody->applyForce(DEFAULT_FORCE * -Vec2(0, 1));
		}

		// screen wrap
		if (spaceship->getPosition().x > visibleSize.width + (spaceship->getContentSize().width * spaceship->getScale()))
			spaceship->setPosition(Vec2(-(spaceship->getContentSize().width * spaceship->getScale()), spaceship->getPosition().y));
		else if (spaceship->getPosition().x < -(spaceship->getContentSize().width * spaceship->getScale()))
			spaceship->setPosition(Vec2(visibleSize.width + (spaceship->getContentSize().width * spaceship->getScale()), spaceship->getPosition().y));

		if (spaceship->getPosition().y > visibleSize.height + (spaceship->getContentSize().width * spaceship->getScale()))
			spaceship->setPosition(Vec2(spaceship->getPosition().x, -(spaceship->getContentSize().width * spaceship->getScale())));
		else if (spaceship->getPosition().y < -(spaceship->getContentSize().width * spaceship->getScale()))
			spaceship->setPosition(Vec2(spaceship->getPosition().x, visibleSize.height + (spaceship->getContentSize().width * spaceship->getScale())));

		// Update Light Location (following main sprite position in terms of screen)
		GLProgramState::getOrCreateWithGLProgram(proPostProcess)->setUniformVec2("loc", Vec2(spaceship->getPositionX() / visibleSize.width, spaceship->getPositionY() / visibleSize.height));
	}

	// Post Processing
	rendtex->beginWithClear(.0f, .0f, .0f, .0f);
	this->visit();
	rendtex->end();
	rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setShaderProgram(proPostProcess);

	InputManager::GetInstance()->Update();

}
