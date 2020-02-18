#pragma once
#include "State.h"
#include "../GameObject.h"
#include "cocos2d.h"
#include "SpaceshipScene.h"

#define THRUSTER_FORCE 150.f
#define DEFAULT_SPIN_SPEED .8f

class StateEnemyRetreat : public State
{
	GameObject* m_go;
	GameObject* player;
	cocos2d::Vec2 dir;

public:
	StateEnemyRetreat(const std::string& stateID, GameObject* go, GameObject* player_);
	virtual ~StateEnemyRetreat();

	virtual void Enter();
	virtual void Update(double dt);
	virtual void Exit();

};

