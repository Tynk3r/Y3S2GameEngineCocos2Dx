#include "Nodes.h"

USING_NS_CC;

Nodes::Nodes()
{
}


Nodes::~Nodes()
{
}

cocos2d::Node * Nodes::CreateNode(std::string Name, std::string sprite, cocos2d::Vec2 AnchorPoint, cocos2d::Vec2 position, int NodeLayer, cocos2d::Scene* scene, int SceneLayer)
{
	// Create Node
	auto spriteNode = Node::create();
	spriteNode->setName(Name);

	auto mainSprite = Sprite::create(sprite);
	mainSprite->setAnchorPoint(AnchorPoint);
	mainSprite->setPosition(position);

	spriteNode->addChild(mainSprite, NodeLayer);

	scene->addChild(spriteNode, SceneLayer);
	return spriteNode;
}

