#pragma once

#include "cocos2d.h"

class Nodes
{
public:
	Nodes();
	~Nodes();

	static cocos2d::Node* CreateNode(std::string NodeName, std::string SpriteName, std::string sprite, cocos2d::Vec2 AnchorPoint, cocos2d::Vec2 position, int NodeLayer, cocos2d::Scene* scene, int SceneLayer);
	static cocos2d::Node* CreateNodeWithPhysics(std::string NodeName, std::string SpriteName, std::string sprite, cocos2d::Vec2 AnchorPoint, cocos2d::Vec2 position, cocos2d::PhysicsMaterial physicsMat, int NodeLayer, cocos2d::Scene* scene, int SceneLayer);

};

