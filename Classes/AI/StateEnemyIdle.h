#pragma once
#include "State.h"
#include "../GameObject.h"
#include "cocos2d.h"

#define DIR_CHANGE_TIME 5
#define THRUSTER_FORCE 150.f
#define DEFAULT_SPIN_SPEED 1.f
#define DISTANCE_TO_ATTACK 350
#define HEALTH_BEFORE_RETREAT 3

class StateEnemyIdle : public State
{
	GameObject* m_go;
	GameObject* player;
	float timeBeforeChangeDir;
	cocos2d::Vec2 dir;

public:
	StateEnemyIdle(const std::string& stateID, GameObject* go, GameObject* player_);
	virtual ~StateEnemyIdle();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();

};

