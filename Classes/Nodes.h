#pragma once

#include "cocos2d.h"

class Nodes
{
public:
	Nodes();
	~Nodes();

 	static cocos2d::Node* CreateNodeUsingTextureCache(cocos2d::Node* Node, std::string SpriteName, std::string filename, cocos2d::Vec2 AnchorPoint, cocos2d::Vec2 position, int NodeLayer, float scale = 1.f);

};

