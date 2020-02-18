#pragma once
#include "State.h"
#include "../GameObject.h"
#include "cocos2d.h"
#include "SpaceshipScene.h"

#define THRUSTER_FORCE 150.f
#define DEFAULT_SPIN_SPEED .8f
#define DISTANCE_FROM_PLAYER 200
#define ANGLE_TO_SHOOT 20
#define BULLET_SPEED 300.f
#define ATTACK_SPEED 0.5
#define HEALTH_BEFORE_RETREAT 3

class StateEnemyAttack : public State
{
	GameObject* m_go;
	GameObject* player;
	cocos2d::Vec2 dir;
	SpaceshipScene* scene;
	float timeBeforeShoot;
public:
	StateEnemyAttack(const std::string& stateID, GameObject* go, GameObject* player_, SpaceshipScene* scene_);
	virtual ~StateEnemyAttack();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();

};

