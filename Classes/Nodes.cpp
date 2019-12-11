#include "Nodes.h"

USING_NS_CC;

Nodes::Nodes()
{
}


Nodes::~Nodes()
{
}

cocos2d::Node * Nodes::CreateNodeUsingTextureCache(cocos2d::Node * Node, std::string SpriteName, std::string filename, cocos2d::Vec2 AnchorPoint, cocos2d::Vec2 position, int NodeLayer, float scale)
{
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
	Rect rect = Rect::ZERO;
	rect.size = texture->getContentSize();
	Sprite *frame = Sprite::createWithTexture(texture, rect);

	auto mainSprite = frame;
	mainSprite->setAnchorPoint(AnchorPoint);
	mainSprite->setPosition(position);
	mainSprite->setName(SpriteName);
	mainSprite->setScale(scale);

	Node->addChild(mainSprite, NodeLayer);

	return mainSprite;
}