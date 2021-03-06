#include "GameObject.h"

GameObject::GameObject(cocos2d::Node* node_, GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	active(false),
	health(1),
	maxHealth(1),
	lifetime(-100)
{
	node = node_;
}

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	active(false),
	node(nullptr),
	health(1),
	maxHealth(1),
	lifetime(-100)
{
}

GameObject::~GameObject()
{
	if (sm != NULL)
	{
		delete sm;
		sm = NULL;
	}
}