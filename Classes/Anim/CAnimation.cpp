#include "CAnimation.h"

USING_NS_CC;

cocos2d::Animate * CAnimation::createAnimation(string spriteNames[], int numOfFrames, int xSize, int ySize, float delay)
{
	Vector<SpriteFrame*> animFrames;
	Animate* AnimName;

	animFrames.reserve(numOfFrames);
	for (int i = 0; i < numOfFrames; i++)
	{
		animFrames.pushBack(SpriteFrame::create(spriteNames[i], Rect(0, 0, xSize, ySize)));
	}
	Animation* animation = Animation::createWithSpriteFrames(animFrames, delay);
	AnimName = Animate::create(animation);
	return AnimName;
}
