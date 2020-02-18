#include "StateEnemyAttack.h"
#include "../Nodes.h"

using namespace cocos2d;

StateEnemyAttack::StateEnemyAttack(const std::string& stateID, GameObject* go, GameObject* player_, SpaceshipScene* scene_)
	:State(stateID),
	m_go(go),
	player(player_),
	scene(scene_)
{
}

StateEnemyAttack::~StateEnemyAttack()
{
}

void StateEnemyAttack::Enter()
{
	dir = player->node->getPosition() - m_go->node->getPosition();
	dir.normalize();
}

void StateEnemyAttack::Update(double dt)
{
	if (!player->active)
	{
		m_go->sm->SetNextState("idle_enemyShip");
		return;
	}
	else if (m_go->health <= HEALTH_BEFORE_RETREAT)
	{
		m_go->sm->SetNextState("retreat_enemyShip");
	}
	dir = player->node->getPosition() - m_go->node->getPosition();
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

	if ((player->node->getPosition() - m_go->node->getPosition()).length() > DISTANCE_FROM_PLAYER)
		spaceshipPhysicsBody->applyForce(Vec2(0, THRUSTER_FORCE));
	else
		spaceshipPhysicsBody->applyForce(Vec2(0, -THRUSTER_FORCE));

	timeBeforeShoot -= dt;

	spaceshipDirection = Vec2(sin(CC_DEGREES_TO_RADIANS(spaceshipPhysicsBody->getRotation())), cos(CC_DEGREES_TO_RADIANS(spaceshipPhysicsBody->getRotation())));
	spaceshipDirection.normalize();
	//Shoot if angle between current dir and target dir < some angle
	if (CC_RADIANS_TO_DEGREES(acosf(dir.dot(spaceshipDirection))) < ANGLE_TO_SHOOT && timeBeforeShoot <= 0)
	{
		Node* bullet = Nodes::CreateNodeUsingTextureCache(scene->spriteNode, "bullet", "Bullet.png", Vec2(0.5, 0.5), m_go->node->getPosition() + spaceshipDirection * 85.f, 1, 0.01f);
		PhysicsBody* physicsBody = PhysicsBody::createBox(Size(bullet->getContentSize().width, bullet->getContentSize().height), PhysicsMaterial(0.001f, 0.1f, 5.0f));
		physicsBody->setDynamic(true);
		physicsBody->setMass(0.01);
		physicsBody->setVelocity(spaceshipDirection * BULLET_SPEED);
		bullet->addComponent(physicsBody);
		scene->FetchGO(bullet, GameObject::GO_BULLET);
		timeBeforeShoot = ATTACK_SPEED;
	}
}

void StateEnemyAttack::Exit()
{
}
