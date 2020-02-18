#include "StateEnemyRetreat.h"
#include "../Nodes.h"

using namespace cocos2d;

StateEnemyRetreat::StateEnemyRetreat(const std::string& stateID, GameObject* go, GameObject* player_)
	:State(stateID),
	m_go(go),
	player(player_)
{
}

StateEnemyRetreat::~StateEnemyRetreat()
{
}

void StateEnemyRetreat::Enter()
{
	dir = m_go->node->getPosition() - player->node->getPosition();
	dir.normalize();
}

void StateEnemyRetreat::Update(double dt)
{
	if (!player->active)
	{
		m_go->sm->SetNextState("idle_enemyShip");
		return;
	}

	dir = m_go->node->getPosition() - player->node->getPosition();
	dir.normalize();

	//Physics movement
	PhysicsBody* spaceshipPhysicsBody = m_go->node->getPhysicsBody();
	Vec2 spaceshipDirection = Vec2(cosf(CC_DEGREES_TO_RADIANS(spaceshipPhysicsBody->getRotation())), sinf(CC_DEGREES_TO_RADIANS(spaceshipPhysicsBody->getRotation())));
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

void StateEnemyRetreat::Exit()
{
}
