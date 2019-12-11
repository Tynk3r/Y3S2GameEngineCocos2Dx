#include "Nodes.h"

USING_NS_CC;

Nodes::Nodes()
{
}


Nodes::~Nodes()
{
}

cocos2d::Node * Nodes::CreateNode(std::string Name, std::string SpriteName, std::string sprite, cocos2d::Vec2 AnchorPoint, cocos2d::Vec2 position, int NodeLayer, cocos2d::Scene* scene, int SceneLayer)
{
	// Create Node
	auto spriteNode = Node::create();
	spriteNode->setName(Name);

	auto mainSprite = Sprite::create(sprite);
	mainSprite->setAnchorPoint(AnchorPoint);
	mainSprite->setPosition(position);
	mainSprite->setName(SpriteName);

	spriteNode->addChild(mainSprite, NodeLayer);

	scene->addChild(spriteNode, SceneLayer);
	return spriteNode;
}

cocos2d::Node * Nodes::CreateNodeWithPhysics(std::string NodeName, std::string SpriteName, std::string sprite, cocos2d::Vec2 AnchorPoint, cocos2d::Vec2 position, PhysicsMaterial physicsMat, int NodeLayer, cocos2d::Scene * scene, int SceneLayer)
{
		// Create Node
	auto spriteNode = Node::create();
	spriteNode->setName(NodeName);

	auto mainSprite = Sprite::create(sprite);
	mainSprite->setAnchorPoint(AnchorPoint);
	mainSprite->setPosition(position);
	mainSprite->setName(SpriteName);

	auto physicsBody = PhysicsBody::createBox(Size(mainSprite->getContentSize().width, mainSprite->getContentSize().height), PhysicsMaterial(physicsMat));
	physicsBody->setDynamic(true);
	mainSprite->addComponent(physicsBody);

	spriteNode->addChild(mainSprite, NodeLayer);

	scene->addChild(spriteNode, SceneLayer);
	return spriteNode;

}


