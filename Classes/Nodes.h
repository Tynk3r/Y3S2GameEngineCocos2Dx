#pragma once

#include "cocos2d.h"

class Nodes
{
public:
	Nodes();
	~Nodes();

	static cocos2d::Node* CreateNode(std::string Name, std::string sprite, cocos2d::Vec2 AnchorPoint, cocos2d::Vec2 position, int NodeLayer, cocos2d::Scene* scene, int SceneLayer);

};

