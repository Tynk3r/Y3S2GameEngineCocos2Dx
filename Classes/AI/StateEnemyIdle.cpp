#include "StateEnemyIdle.h"

using namespace cocos2d;

StateEnemyIdle::StateEnemyIdle(const std::string& stateID, GameObject* go, GameObject* player_)
	:State(stateID),
	m_go(go),
	player(player_)
{
}

StateEnemyIdle::~StateEnemyIdle()
{
}

void StateEnemyIdle::Enter()
{
	dir = Vec2(RandomHelper::random_real(-1.f, 1.f), cocos2d::RandomHelper::random_real(-1.f, 1.f));
	dir.normalize();
	timeBeforeChangeDir = DIR_CHANGE_TIME;
}

void StateEnemyIdle::Update(double dt)
{
	if (player->active)
	{
		if (m_go->health <= HEALTH_BEFORE_RETREAT)
		{
			m_go->sm->SetNextState("retreat_enemyShip");
		}
		else if ((player->node->getPosition() - m_go->node->getPosition()).length() < DISTANCE_TO_ATTACK)
		{
			m_go->sm->SetNextState("attack_enemyShip");
		}
	}

	timeBeforeChangeDir -= dt;
	if (timeBeforeChangeDir <= 0)
	{
		timeBeforeChangeDir = DIR_CHANGE_TIME;
		dir = Vec2(RandomHelper::random_real(-1.f, 1.f), cocos2d::RandomHelper::random_real(-1.f, 1.f));
	}

	//Physics movement
	PhysicsBody* spaceshipPhysicsBody = m_go->node->getPhysicsBody();
	Vec2 spaceshipDirection(cosf(CC_DEGREES_TO_RADIANS(spaceshipPhysicsBody->getRotation())), sinf(CC_DEGREES_TO_RADIANS(spaceshipPhysicsBody->getRotation())));
	spaceshipDirection.normalize();

	Vec2 temp = dir;
	temp.y = -temp.y;
	float dot = temp.dot(spaceshipDirection);

	if (dot > 0)
		spaceshipPhysicsBody->setAngularVelocity(-DEFAULT_SPIN_SPEED);
	else if (dot < 0)
		spaceshipPhysicsBody->setAngularVelocity(DEFAULT_SPIN_SPEED);
	else
	{
		if (dir != spaceshipDirection)
			spaceshipPhysicsBody->setAngularVelocity(DEFAULT_SPIN_SPEED);
	}

	spaceshipPhysicsBody->applyForce(Vec2(0, THRUSTER_FORCE));
}

void StateEnemyIdle::Exit()
{
}
