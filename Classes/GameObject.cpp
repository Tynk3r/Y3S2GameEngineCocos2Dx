#include "GameObject.h"

GameObject::GameObject(cocos2d::Node* node_, GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	active(false)
{
	node = node_;
}

GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	active(false)
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