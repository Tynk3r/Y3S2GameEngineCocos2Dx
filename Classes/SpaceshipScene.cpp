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

#define DEFAULT_FORCE 150.f
#define SPEED_LIMIT 100.f
#define DEFAULT_SPIN_SPEED 1.f
#define SPIN_SPEED_LIMIT 1.f
#define BULLET_SPEED 300.f
#define MAX_ASTEROIDS 5
#define MAX_ENEMIES 3
#define MAX_HEALTHPACKS 3
#define ASTEROID_SPAWN_TIME 5
#define ENEMY_SPAWN_TIME 15
#define HEALTH_PACK_SPAWN_TIME 7
#define OBJECTS_DISTANCE_FROM_PLAYER 250

#include "SpaceshipScene.h"
#include "SimpleAudioEngine.h"
#include "Input/InputManager.h"
#include "SceneManagement/SceneManager.h"
#include "Anim/CAnimation.h"
#include "Nodes.h"
#include "HUDLayer.h"
#include "JoyStick.h"
#include "UI/UI.h"
#include "AI/StateEnemyIdle.h"
#include "AI/StateEnemyAttack.h"
#include "AI/StateEnemyRetreat.h"
#include "MainMenuScene.h"

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

	//this->getPhysicsWorld()->setDebugDrawMask(0xffff);
	this->getPhysicsWorld()->setGravity(Vec2(0.f, 0.f));

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	// Post Processing
	//proPostProcess = GLProgram::createWithFilenames("Basic.vsh", "CharEffect.fsh");
	//proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	//proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	//proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	//proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	//proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
	//proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
	//proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
	//proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
	//proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);
	//proPostProcess->link();
	//proPostProcess->updateUniforms();
	//Vec2 mLoc(0.5f, 0.5f);
	//GLProgramState::getOrCreateWithGLProgram(proPostProcess)->setUniformVec2("loc", mLoc);
	//
	//rendtex = RenderTexture::create(visibleSize.width, visibleSize.height);
	//rendtex->retain();
	//
	//rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());
	//rendtexSprite->setTextureRect(Rect(0, 0, rendtex->getSprite()->getTexture()->getContentSize().width, rendtex->getSprite()->getTexture()->getContentSize().height));
	//rendtexSprite->setAnchorPoint(Point::ZERO);
	//rendtexSprite->setPosition(Point::ZERO);
	//rendtexSprite->setFlippedY(true);
	//rendtexSprite->setShaderProgram(proPostProcess);
	//this->addChild(rendtexSprite, 2);


	//Init containers

	nodeItems = Node::create();
	nodeItems->setName("nodeItems");
	spriteNode = Node::create();
	spriteNode->setName("spriteNode");

	// Creation of player HUD
	hud = HUDLayer::create();
	hud->addJoystickToLayer();
	hud->joyStick->Inactive();

	auto ShootButton = UI::createButton("Shoot.png", "ShootPressed.png", "ShootPressed.png", Vec2(visibleSize.width * 0.85, visibleSize.height * 0.15f), "", this);
	ShootButton->addTouchEventListener(CC_CALLBACK_2(SpaceshipScene::ShootButtonEvent, this));
	ShootButton->setScale(0.5);
	hud->addChild(ShootButton);

	auto HealthPackButton = UI::createButton("HealthPack.png", "HealthPackPressed.png", "HealthPackDisabled.png", Vec2(visibleSize.width * 0.85, visibleSize.height * 0.3f), "", this);
	HealthPackButton->addTouchEventListener(CC_CALLBACK_2(SpaceshipScene::UseHealthpack, this));
	HealthPackButton->setScale(0.1f);
	hud->addChild(HealthPackButton, 1, "HealthPackButton");

	sprintf(text, "X %d", playerHealthPacks);
	auto HealthPackCount = UI::createTTFLabel(text, Vec2(visibleSize.width * 0.9, visibleSize.height * 0.3f), "fonts/MarkerFelt.ttf", 24, 1, this);
	hud->addChild(HealthPackCount, 1 , "PlayerHealthPackCount");

	sprintf(text, "Points: %d", points);
	auto pointCount = UI::createTTFLabel(text, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.95f), "fonts/MarkerFelt.ttf", 24, 1, this);
	hud->addChild(pointCount, 1, "pointCount");


	// Create a layer for player when they die
	deathScreen = HUDLayer::create();
	auto DeadScreensprite = Sprite::create("DeathScreen.png");
	DeadScreensprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	DeadScreensprite->setPosition(Vec2(visibleSize.width * .5f, visibleSize.height * .5f));
	DeadScreensprite->setScale(visibleSize.width / DeadScreensprite->getContentSize().width, visibleSize.height / DeadScreensprite->getContentSize().height);
	deathScreen->addChild(DeadScreensprite);

	auto BackToMainMenuButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Blue_Front1.png", Vec2(visibleSize.width * 0.5, visibleSize.height * 0.15), "Back To MainMenu", this);
	BackToMainMenuButton->setTitleFontSize(10);
	BackToMainMenuButton->addTouchEventListener(CC_CALLBACK_2(SpaceshipScene::BackToMainMenu, this));
	deathScreen->addChild(BackToMainMenuButton);

	auto RespawnButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Blue_Front1.png", Vec2(visibleSize.width * 0.5, visibleSize.height * 0.35), "Try Again?", this);
	BackToMainMenuButton->setTitleFontSize(10);
	RespawnButton->addTouchEventListener(CC_CALLBACK_2(SpaceshipScene::RespawnPlayer, this));
	deathScreen->addChild(RespawnButton);
	deathScreen->setVisible(false);

	//Create sprites
	auto MainSpriteNode = Nodes::CreateNodeUsingTextureCache(spriteNode, "mainSprite", "Spaceship.png", Vec2(0.5, 0.5), Vec2(visibleSize.width * .5f, visibleSize.height * .5f), 1, 0.1f);
	auto physicsBody = PhysicsBody::createBox(Size(MainSpriteNode->getContentSize().width, MainSpriteNode->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
	physicsBody->setDynamic(true);
	physicsBody->setVelocityLimit(SPEED_LIMIT);
	physicsBody->setAngularVelocityLimit(SPIN_SPEED_LIMIT);
	MainSpriteNode->addComponent(physicsBody);
	player = FetchGO(MainSpriteNode, GameObject::GO_PLAYER);
	player->health = 20;
	player->maxHealth = 20;

	Vec2 randPos;
	randPos = Vec2(cocos2d::RandomHelper::random_real(0.f, visibleSize.width), cocos2d::RandomHelper::random_real(0.f, visibleSize.height));
	while ((player->node->getPosition() - randPos).length() < OBJECTS_DISTANCE_FROM_PLAYER)
		randPos = Vec2(cocos2d::RandomHelper::random_real(0.f, visibleSize.width), cocos2d::RandomHelper::random_real(0.f, visibleSize.height));
	auto EnemySprite = Nodes::CreateNodeUsingTextureCache(spriteNode, "enemy", "Enemy_Ship.png", Vec2(0.5, 0.5), randPos, 1, 0.1f);
	physicsBody = PhysicsBody::createBox(Size(EnemySprite->getContentSize().width, EnemySprite->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
	physicsBody->setDynamic(true);
	physicsBody->setVelocityLimit(SPEED_LIMIT);
	physicsBody->setAngularVelocityLimit(SPIN_SPEED_LIMIT);
	EnemySprite->addComponent(physicsBody);
	GameObject* temp = FetchGO(EnemySprite, GameObject::GO_ENEMY);
	temp->health = 10;
	temp->maxHealth = 10;

	auto thrusters = Nodes::CreateNodeUsingTextureCache(spriteNode, "thrusters", "ThrusterSprites/Thruster1.png", Vec2(0.5, 0.5), MainSpriteNode->getPosition(), 1, 0.1f);
	string thrusterSprites[5] = { "ThrusterSprites/Thruster1.png","ThrusterSprites/Thruster2.png","ThrusterSprites/Thruster3.png","ThrusterSprites/Thruster4.png","ThrusterSprites/Thruster5.png" };
	Animate* animateThrusters = CAnimation::createAnimation(thrusterSprites, 5, thrusters->getContentSize().width, thrusters->getContentSize().height, 0.5f);
	thrusters->runAction(RepeatForever::create(animateThrusters));
	player->node->addChild(thrusters);

	Texture2D* BGtexture = Director::getInstance()->getTextureCache()->addImage("SpaceTexture.png");
	Rect rect = Rect::ZERO;
	rect.size = BGtexture->getContentSize();
	auto BG = Sprite::createWithTexture(BGtexture, rect);
	BG->setAnchorPoint(Vec2(0.5f, 0.5f));
	BG->setPosition(Vec2(visibleSize.width * .5f, visibleSize.height * .5f));
	BG->setName("BackGround");
	BG->setScale(visibleSize.width / BG->getContentSize().width, visibleSize.height / BG->getContentSize().height);
	this->addChild(BG, 1);

	for (int i = 0; i < 3; i++)
	{
		randPos = Vec2(cocos2d::RandomHelper::random_real(0.f, visibleSize.width), cocos2d::RandomHelper::random_real(0.f, visibleSize.height));
		while((player->node->getPosition() - randPos).length() < OBJECTS_DISTANCE_FROM_PLAYER)
			randPos = Vec2(cocos2d::RandomHelper::random_real(0.f, visibleSize.width), cocos2d::RandomHelper::random_real(0.f, visibleSize.height));
		auto asteroid1 = Nodes::CreateNodeUsingTextureCache(nodeItems, "asteroid1", "Asteroids/asteroid_01.png", Vec2(0.5, 0.5), randPos, 1, 0.5f);
		string asteroidSprites[4] = { "Asteroids/asteroid_01.png","Asteroids/asteroid_02.png","Asteroids/asteroid_03.png","Asteroids/asteroid_04.png" };
		Animate* animateAsteroids = CAnimation::createAnimation(asteroidSprites, 4, asteroid1->getContentSize().width, asteroid1->getContentSize().width, 0.5f);
		asteroid1->runAction(RepeatForever::create(animateAsteroids));
	
		//Create static PhysicsBody
		physicsBody = PhysicsBody::createBox(Size(asteroid1->getContentSize().width, asteroid1->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
		physicsBody->setDynamic(false);
		physicsBody->setVelocityLimit(SPEED_LIMIT);
		physicsBody->setAngularVelocityLimit(SPIN_SPEED_LIMIT);
		asteroid1->addComponent(physicsBody);

		GameObject* temp = FetchGO(asteroid1, GameObject::GO_ASTEROID);
		temp->health = 5;
		temp->maxHealth = 5;
	}

	auto sprite = Sprite::create("HelloWorld.png");
	auto spritePos = Vec3(visibleSize.width / 2 + origin.x,visibleSize.height / 2 + origin.y,0);
	sprite->setCameraMask((unsigned short)CameraFlag::USER2);
	sprite->setPosition3D(spritePos);
	this->addChild(sprite);

	//// New camera(User2)
	//camera2 = Camera::createPerspective(60, (float)visibleSize.width / visibleSize.height, 1.0, 1000);
	////camera2->setCameraFlag(CameraFlag::USER2);
	//camera2->setPosition3D(spritePos + Vec3(0, 0, 600));
	//camera2->lookAt(spritePos, Vec3(0.0, 1.0, 0.0));
	//this->addChild(camera2);
	//
	//camera3 = Camera::createPerspective(60, (float)visibleSize.width / visibleSize.height, 1.0, 1000);
	////camera3->setCameraFlag(CameraFlag::USER3);
	//camera3->setPosition3D(spritePos + Vec3(0, 0, 600));
	//camera3->lookAt(spritePos, Vec3(0.0, 1.0, 0.0));
	//this->addChild(camera3);
	//
	////spriteNode->setCameraMask((unsigned short)CameraFlag::USER2);
	////nodeItems->setCameraMask((unsigned short)CameraFlag::USER3);
	//
	////this->getDefaultCamera()->setVisible(true);
	//camera2->setVisible(true);
	//camera3->setVisible(true);

	//Add containers to scene
	this->addChild(spriteNode, 1);
	this->addChild(nodeItems, 1);
	this->addChild(hud,2);
	this->addChild(deathScreen, 3);

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


	//Update
	this->schedule(schedule_selector(SpaceshipScene::Update));

	points = 0;
	asteroidSpawnTime = ASTEROID_SPAWN_TIME;
	enemySpawnTime = ENEMY_SPAWN_TIME;
	healthPackSpawnTime = HEALTH_PACK_SPAWN_TIME;
	numOfAsteroids = 3;
	numOfEnemies = 1;
	numOfHealthpacks = 0;
	currentWeapon = W_ROCKETS;
	return true;
}


void SpaceshipScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

void SpaceshipScene::ShootButtonEvent(Ref* sender, cocos2d::ui::Button::TouchEventType type)
{
	Vec2 tempDir;
	Node* bullet;
	PhysicsBody* physicsBody;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:

		switch (currentWeapon)
		{
		case W_BLASTER:
			tempDir = Vec2(sin(CC_DEGREES_TO_RADIANS(player->node->getRotation())), cos(CC_DEGREES_TO_RADIANS(player->node->getRotation())));
			tempDir.normalize();
			bullet = Nodes::CreateNodeUsingTextureCache(spriteNode, "bullet", "Bullet.png", Vec2(0.5, 0.5), player->node->getPosition() + tempDir * 85.f, 1, 0.01f);
			physicsBody = PhysicsBody::createBox(Size(bullet->getContentSize().width, bullet->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
			physicsBody->setDynamic(true);
			physicsBody->setMass(0.01);
			physicsBody->setVelocity(tempDir * BULLET_SPEED);
			bullet->addComponent(physicsBody);
			FetchGO(bullet, GameObject::GO_BULLET);
			break;

		case W_ROCKETS:
			tempDir = Vec2(sin(CC_DEGREES_TO_RADIANS(player->node->getRotation())), cos(CC_DEGREES_TO_RADIANS(player->node->getRotation())));
			tempDir.normalize();
			bullet = Nodes::CreateNodeUsingTextureCache(spriteNode, "missile", "missile.png", Vec2(0.5, 0.5), player->node->getPosition() + tempDir * 85.f, 1, 0.05f);
			physicsBody = PhysicsBody::createBox(Size(bullet->getContentSize().width, bullet->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
			physicsBody->setDynamic(true);
			physicsBody->setMass(1);
			physicsBody->setVelocity(tempDir * BULLET_SPEED);
			bullet->addComponent(physicsBody);
			FetchGO(bullet, GameObject::GO_MISSILE);
			break;
		}

		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void SpaceshipScene::Update(float interval)
{
	
	auto spaceship = this->getChildByName("spriteNode")->getChildByName("mainSprite");
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//if (InputManager::GetInstance()->GetAction("Make Brighter")->Held())
	//	darkness = clampf(darkness - .1f, 0.f, 10.f);
	//else if (InputManager::GetInstance()->GetAction("Make Darker")->Held())
	//	darkness = clampf(darkness + .1f, 0.f, 10.f);
	//GLProgramState::getOrCreateWithGLProgram(proPostProcess)->setUniformFloat("darkness", darkness);

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

		//Touch controls
		if (hud->joyStick->IsActive())
		{
			//Physics movement
			PhysicsBody* spaceshipPhysicsBody = spaceship->getPhysicsBody();
			Vec2 spaceshipDirection(cosf(CC_DEGREES_TO_RADIANS(spaceshipPhysicsBody->getRotation())), sinf(CC_DEGREES_TO_RADIANS(spaceshipPhysicsBody->getRotation())));
			spaceshipDirection.normalize();

			Vec2 temp = hud->joyStick->GetDir();
			temp.y = -temp.y;
			float dot = temp.dot(spaceshipDirection);

			if(dot > 0)
				spaceshipPhysicsBody->setAngularVelocity(-DEFAULT_SPIN_SPEED);
			else if(dot < 0)
				spaceshipPhysicsBody->setAngularVelocity(DEFAULT_SPIN_SPEED);
			else
			{
				if(hud->joyStick->GetDir() != spaceshipDirection)
					spaceshipPhysicsBody->setAngularVelocity(DEFAULT_SPIN_SPEED);
			}

			spaceshipPhysicsBody->applyForce(DEFAULT_FORCE * Vec2(0, hud->joyStick->GetPercentageDistanceBetweenCenterAndJoyStick()));
		}
		else
		{
			PhysicsBody* spaceshipPhysicsBody = spaceship->getPhysicsBody();
			spaceshipPhysicsBody->setAngularVelocity(0);
		}

		// screen wrap
		for (auto go : m_goList)
		{
			if (go->active)
			{
				if (go->type == GameObject::GO_BULLET || go->type == GameObject::GO_MISSILE)
				{
					if (go->node->getPosition().x > visibleSize.width + (go->node->getContentSize().width * go->node->getScale()))
						go->active = false;
					else if (go->node->getPosition().x < -(go->node->getContentSize().width * go->node->getScale()))
						go->active = false;

					if (go->node->getPosition().y > visibleSize.height + (go->node->getContentSize().width * go->node->getScale()))
						go->active = false;
					else if (go->node->getPosition().y < -(go->node->getContentSize().width * go->node->getScale()))
						go->active = false;
					continue;
				}
				if (go->node->getPosition().x > visibleSize.width + (go->node->getContentSize().width * go->node->getScale()))
					go->node->setPosition(Vec2(-(go->node->getContentSize().width * go->node->getScale()), go->node->getPosition().y));
				else if (go->node->getPosition().x < -(go->node->getContentSize().width * go->node->getScale()))
					go->node->setPosition(Vec2(visibleSize.width + (go->node->getContentSize().width * go->node->getScale()), go->node->getPosition().y));

				if (go->node->getPosition().y > visibleSize.height + (go->node->getContentSize().width * go->node->getScale()))
					go->node->setPosition(Vec2(go->node->getPosition().x, -(go->node->getContentSize().width * go->node->getScale())));
				else if (go->node->getPosition().y < -(go->node->getContentSize().width * go->node->getScale()))
					go->node->setPosition(Vec2(go->node->getPosition().x, visibleSize.height + (go->node->getContentSize().width * go->node->getScale())));
			}
		}


		// Update Light Location (following main sprite position in terms of screen)
		//GLProgramState::getOrCreateWithGLProgram(proPostProcess)->setUniformVec2("loc", Vec2(spaceship->getPositionX() / visibleSize.width, spaceship->getPositionY() / visibleSize.height));
	}
	
	//State Updates
	for (int i = 0; i < m_goList.size(); i++) //auto gets read access violation error when AI create 10 more empty bullet objects in FetchGo()
	{
		GameObject* go = m_goList[i];
		if (!go->active)
			continue;
		if (go->type == GameObject::GO_ENEMY)
		{
			go->sm->Update(interval);
		}
	}

	for (auto go : m_goList)
	{
		if (go->active)
		{
			if (go->lifetime != -100)
			{
				go->lifetime -= interval;
				if (go->lifetime <= 0)
				{
					go->active = false;
				}
			}
		}
	}

	//Collision Checks
	for (auto go : m_goList)
	{
		if (go->active)
		{
			for (auto go2 : m_goList)
			{
				if (!go2->active)
					continue;
				if (go == go2)
					continue;
				if (go->node->getBoundingBox().intersectsRect(go2->node->getBoundingBox()))
				{
					if (go->type == GameObject::GO_BULLET)
					{
						if (go2->type == GameObject::GO_BULLET || go2->type == GameObject::GO_MISSILE)
						{
							go->active = false;
							go2->active = false;
							continue;
						}
						if (go2->type == GameObject::GO_ASTEROID || go2->type == GameObject::GO_ENEMY || go2->type == GameObject::GO_PLAYER)
						{
							go->active = false;

							go2->health--;

							auto HealthBar = static_cast<cocos2d::ui::LoadingBar*>(go2->node->getChildByName("HealthBar"));
							HealthBar->setPercent((100.0f / go2->maxHealth) * go2->health);
							if (go2->health <= 0)
							{
								go2->active = false;
								if (go2->type == GameObject::GO_ENEMY)
								{
									points += 10;
									sprintf(text, "Points: %d", points);
									auto pointsText = static_cast<cocos2d::Label*>(hud->getChildByName("pointCount"));
									pointsText->setString(text);
									numOfEnemies--;
								}
								if (go2->type == GameObject::GO_ASTEROID)
								{
									points += 2;
									sprintf(text, "Points: %d", points);
									auto pointsText = static_cast<cocos2d::Label*>(hud->getChildByName("pointCount"));
									pointsText->setString(text);
									numOfAsteroids--;
								}
								if (go2->type == GameObject::GO_PLAYER)
								{
									points -= 25;
									sprintf(text, "Points: %d", points);
									auto pointsText = static_cast<cocos2d::Label*>(hud->getChildByName("pointCount"));
									pointsText->setString(text);
								}
							}

							continue;
						}
					}
					//player collsion
					else if (go->type == GameObject::GO_PLAYER)
					{
						if (go2->type == GameObject::GO_HEALTHPACK)
						{
							playerHealthPacks++;

							sprintf(text, "X %d", playerHealthPacks);
							auto HealthPackCount = static_cast<cocos2d::Label*>(hud->getChildByName("PlayerHealthPackCount"));
							HealthPackCount->setString(text);

							go2->active = false;
							continue;
						}
					}

					else if (go->type == GameObject::GO_MISSILE)
					{
						if (go2->type == GameObject::GO_BULLET || go2->type == GameObject::GO_MISSILE)
						{
							go->active = false;
							go2->active = false;
							continue;
						}
						if (go2->type == GameObject::GO_ASTEROID || go2->type == GameObject::GO_ENEMY)
						{
							go->active = false;
							auto explosion = Nodes::CreateNodeUsingTextureCache(spriteNode, "explosion", "explosion.png", Vec2(0.5, 0.5), go2->node->getPosition(), 1, 0.2f);
							auto physicsBody = PhysicsBody::createBox(Size(explosion->getContentSize().width, explosion->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
							physicsBody->setDynamic(true);
							physicsBody->setVelocityLimit(SPEED_LIMIT);
							physicsBody->setAngularVelocityLimit(SPIN_SPEED_LIMIT);
							explosion->addComponent(physicsBody);
							GameObject* explode = FetchGO(explosion, GameObject::GO_EXPLOSION);
							explode->lifetime = 0.1f;
						}
					}
					else if (go->type == GameObject::GO_EXPLOSION)
					{

						if (go2->type == GameObject::GO_ASTEROID || go2->type == GameObject::GO_ENEMY)
						{
							go->active = false;
							go2->health -= 10;
							auto HealthBar = static_cast<cocos2d::ui::LoadingBar*>(go2->node->getChildByName("HealthBar"));
							HealthBar->setPercent((100.0f / go2->maxHealth) * go2->health);
							if (go2->health <= 0)
							{
								go2->active = false;
								if (go2->type == GameObject::GO_ENEMY)
								{
									points += 10;
									sprintf(text, "Points: %d", points);
									auto pointsText = static_cast<cocos2d::Label*>(hud->getChildByName("pointCount"));
									pointsText->setString(text);
									numOfEnemies--;
								}
								if (go2->type == GameObject::GO_ASTEROID)
								{
									points += 2;
									sprintf(text, "Points: %d", points);
									auto pointsText = static_cast<cocos2d::Label*>(hud->getChildByName("pointCount"));
									pointsText->setString(text);
									numOfAsteroids--;
								}
								if (go2->type == GameObject::GO_PLAYER)
								{
									points -= 25;
									sprintf(text, "Points: %d", points);
									auto pointsText = static_cast<cocos2d::Label*>(hud->getChildByName("pointCount"));
									pointsText->setString(text);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			if (go->node != nullptr)
			{
				go->node->removeFromParent();
				go->node = nullptr;
				if (go->type == GameObject::GO_PLAYER)
				{
					deathScreen->setVisible(true);
				}
				continue;
			}
		}
	}

	//Spawning stuff
	if (numOfAsteroids < MAX_ASTEROIDS)
		asteroidSpawnTime -= interval;
	if (numOfEnemies < MAX_ENEMIES)
		enemySpawnTime -= interval;
	if (numOfHealthpacks < MAX_HEALTHPACKS)
		healthPackSpawnTime -= interval;
	if (asteroidSpawnTime <= 0 && player->active)
	{
		asteroidSpawnTime = ASTEROID_SPAWN_TIME;
		Vec2 randPos = Vec2(cocos2d::RandomHelper::random_real(0.f, visibleSize.width), cocos2d::RandomHelper::random_real(0.f, visibleSize.height));
		while ((player->node->getPosition() - randPos).length() < OBJECTS_DISTANCE_FROM_PLAYER)
			randPos = Vec2(cocos2d::RandomHelper::random_real(0.f, visibleSize.width), cocos2d::RandomHelper::random_real(0.f, visibleSize.height));
		auto asteroid1 = Nodes::CreateNodeUsingTextureCache(nodeItems, "asteroid1", "Asteroids/asteroid_01.png", Vec2(0.5, 0.5), randPos, 1 , 0.5f);
		string asteroidSprites[4] = { "Asteroids/asteroid_01.png","Asteroids/asteroid_02.png","Asteroids/asteroid_03.png","Asteroids/asteroid_04.png" };
		Animate* animateAsteroids = CAnimation::createAnimation(asteroidSprites, 4, 81, 101, 0.5f);
		asteroid1->runAction(RepeatForever::create(animateAsteroids));

		//Create static PhysicsBody
		PhysicsBody* physicsBody = PhysicsBody::createBox(Size(asteroid1->getContentSize().width, asteroid1->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
		physicsBody->setDynamic(false);
		physicsBody->setVelocityLimit(SPEED_LIMIT);
		physicsBody->setAngularVelocityLimit(SPIN_SPEED_LIMIT);
		physicsBody->setVelocity(Vec2(0, 0));
		asteroid1->addComponent(physicsBody);

		GameObject* temp = FetchGO(asteroid1, GameObject::GO_ASTEROID);
		temp->health = 5;
		temp->maxHealth = 5;
		numOfAsteroids++;
	}
	if (enemySpawnTime <= 0 && player->active)
	{
		enemySpawnTime = ENEMY_SPAWN_TIME;
		Vec2 randPos = Vec2(cocos2d::RandomHelper::random_real(0.f, visibleSize.width), cocos2d::RandomHelper::random_real(0.f, visibleSize.height));
		while ((player->node->getPosition() - randPos).length() < OBJECTS_DISTANCE_FROM_PLAYER)
			randPos = Vec2(cocos2d::RandomHelper::random_real(0.f, visibleSize.width), cocos2d::RandomHelper::random_real(0.f, visibleSize.height));
		auto EnemySprite = Nodes::CreateNodeUsingTextureCache(spriteNode, "enemy", "Enemy_Ship.png", Vec2(0.5, 0.5), randPos, 1, 0.1f);
		PhysicsBody* physicsBody = PhysicsBody::createBox(Size(EnemySprite->getContentSize().width, EnemySprite->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
		physicsBody->setDynamic(true);
		physicsBody->setVelocityLimit(SPEED_LIMIT);
		physicsBody->setAngularVelocityLimit(SPIN_SPEED_LIMIT);
		physicsBody->setVelocity(Vec2(0, 0));
		EnemySprite->addComponent(physicsBody);
		GameObject* temp = FetchGO(EnemySprite, GameObject::GO_ENEMY);
		temp->health = 10;
		temp->maxHealth = 10;
		numOfEnemies++;
	}
	if (healthPackSpawnTime <= 0 && player->active)
	{
		healthPackSpawnTime = HEALTH_PACK_SPAWN_TIME;
		Vec2 randPos = Vec2(cocos2d::RandomHelper::random_real(0.f, visibleSize.width), cocos2d::RandomHelper::random_real(0.f, visibleSize.height));
		while ((player->node->getPosition() - randPos).length() < OBJECTS_DISTANCE_FROM_PLAYER)
			randPos = Vec2(cocos2d::RandomHelper::random_real(0.f, visibleSize.width), cocos2d::RandomHelper::random_real(0.f, visibleSize.height));
		auto HealthPackSprite = Nodes::CreateNodeUsingTextureCache(spriteNode, "healthPack", "HealthPack.png", Vec2(0.5, 0.5), randPos, 1, 0.1f);
		PhysicsBody* physicsBody = PhysicsBody::createBox(Size(HealthPackSprite->getContentSize().width, HealthPackSprite->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
		physicsBody->setDynamic(true);
		physicsBody->setVelocityLimit(SPEED_LIMIT);
		physicsBody->setAngularVelocityLimit(SPIN_SPEED_LIMIT);
		physicsBody->setVelocity(Vec2(0, 0));
		HealthPackSprite->addComponent(physicsBody);
		GameObject* temp = FetchGO(HealthPackSprite, GameObject::GO_HEALTHPACK);
		numOfHealthpacks++;
	}

	// Post Processing
	//rendtex->beginWithClear(.0f, .0f, .0f, .0f);
	//this->visit();
	//rendtex->end();
	//rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
	//rendtexSprite->setShaderProgram(proPostProcess);

	InputManager::GetInstance()->Update();

}

GameObject* SpaceshipScene::FetchGO(cocos2d::Node* node_, GameObject::GAMEOBJECT_TYPE type)
{
	for (auto go : m_goList)
	{
		if (!go->active && go->type == type)
		{
			go->active = true;
			go->node = node_;
			if (go->type != go->GO_BULLET)
			{
				if (go->type == go->GO_PLAYER)
				{
					auto HealthBar = UI::createLoadingBar("PlayerHealthBar.png", cocos2d::ui::LoadingBar::Direction::LEFT, Vec2(go->node->getContentSize().width / 4.0f,0), this);
					HealthBar->setPercent((100.0f / go->maxHealth)*go->health);
					HealthBar->setScale(2);
					HealthBar->setScaleY(3);
					go->node->addChild(HealthBar, 1, "HealthBar");
				}
				else if(go->type == go->GO_ENEMY)
				{
					auto HealthBar = UI::createLoadingBar("EnemyHealthBar.png", cocos2d::ui::LoadingBar::Direction::LEFT, Vec2(go->node->getContentSize().width / 4.0f, 0), this);
					HealthBar->setPercent((100.0f / go->maxHealth)*go->health);
					HealthBar->setScale(2);
					HealthBar->setScaleY(3);
					go->node->addChild(HealthBar, 1, "HealthBar");
				}
				else if (go->type == go->GO_ASTEROID)
				{
					auto HealthBar = UI::createLoadingBar("EnemyHealthBar.png", cocos2d::ui::LoadingBar::Direction::LEFT, Vec2(go->node->getContentSize().width / 4.0f, 0), this);
					HealthBar->setPercent((100.0f / go->maxHealth)*go->health);
					HealthBar->setScale(0.2);
					HealthBar->setScaleY(0.6);
					go->node->addChild(HealthBar, 1, "HealthBar");
				}

			}
			return go;
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		GameObject* go = new GameObject(type);
		if (type == GameObject::GO_ENEMY)
		{
			go->sm = new StateMachine();
			go->sm->AddState(new StateEnemyIdle("idle_enemyShip", go, player));
			go->sm->AddState(new StateEnemyAttack("attack_enemyShip", go, player, this));
			go->sm->AddState(new StateEnemyRetreat("retreat_enemyShip", go, player));
		}
		m_goList.push_back(go);
	}

	return FetchGO(node_, type);
}

void SpaceshipScene::RespawnPlayer(Ref* sender, cocos2d::ui::Button::TouchEventType type)
{
	Node* MainSpriteNode;
	PhysicsBody* physicsBody;
	cocos2d::ui::LoadingBar* HealthBar;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		MainSpriteNode = Nodes::CreateNodeUsingTextureCache(spriteNode, "mainSprite", "Spaceship.png", Vec2(0.5, 0.5), Vec2(visibleSize.width * .5f, visibleSize.height * .5f), 1, 0.1f);
		physicsBody = PhysicsBody::createBox(Size(MainSpriteNode->getContentSize().width, MainSpriteNode->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
		physicsBody->setDynamic(true);
		physicsBody->setVelocityLimit(SPEED_LIMIT);
		physicsBody->setAngularVelocityLimit(SPIN_SPEED_LIMIT);
		physicsBody->setVelocity(Vec2(0, 0));
		MainSpriteNode->addComponent(physicsBody);
		player = FetchGO(MainSpriteNode, GameObject::GO_PLAYER);
		player->health = 20;
		player->maxHealth = 20;
		HealthBar = static_cast<cocos2d::ui::LoadingBar*>(player->node->getChildByName("HealthBar"));
		HealthBar->setPercent((100.0f / player->maxHealth) * player->health);
		deathScreen->setVisible(false);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void SpaceshipScene::UseHealthpack(Ref* sender, cocos2d::ui::Button::TouchEventType type)
{
	if (player->health < player->maxHealth && playerHealthPacks > 0)
	{
		playerHealthPacks--;
		//if (playerHealthPacks == 0)
		//{
		//	auto HealthPackButton = static_cast<cocos2d::ui::Button*>(hud->getChildByName("PlayerHealthPackCount"));
		//	HealthPackButton->setEnabled(false);
		//}
		player->health = player->maxHealth;

		sprintf(text, "X %d", playerHealthPacks);
		auto HealthPackCount = static_cast<cocos2d::Label*>(hud->getChildByName("PlayerHealthPackCount"));
		HealthPackCount->setString(text);

		auto HealthBar = static_cast<cocos2d::ui::LoadingBar*>(player->node->getChildByName("HealthBar"));
		HealthBar->setPercent((100.0f / player->maxHealth) * player->health);
	}
}

void SpaceshipScene::BackToMainMenu(Ref* sender, cocos2d::ui::Button::TouchEventType type)
{
	std::vector<std::string> tempResources;
	MainMenuScene* tempScene = new MainMenuScene(); // So Init isn't called immediately
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		tempResources.push_back("Blue_Back1.png");
		tempResources.push_back("Blue_Front1.png");
		tempResources.push_back("Blue_Front2.png");
		tempResources.push_back("Blue_Front3.png");
		tempResources.push_back("ZigzagGrass_Mud_Round.png");

		SceneManager::GetInstance()->ReplaceScene(tempScene, tempResources);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}