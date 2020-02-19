#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "cocos2d.h"
#include "AI/StateMachine.h"
#include "ui/CocosGUI.h"

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_ASTEROID,
		GO_PLAYER,
		GO_BULLET,
		GO_MISSILE,
		GO_EXPLOSION,
		GO_ENEMY,
		GO_HEALTHPACK,
		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	cocos2d::Node* node;
	bool active;
	cocos2d::Vec2 target;
	float moveSpeed;
	StateMachine* sm;
	int health;
	int maxHealth;
	float lifetime;
	cocos2d::ui::LoadingBar* healthBarNode;

	GameObject(cocos2d::Node* node_, GAMEOBJECT_TYPE typeValue = GO_ASTEROID);
	GameObject(GAMEOBJECT_TYPE typeValue = GO_ASTEROID);
	~GameObject();
};

#endif