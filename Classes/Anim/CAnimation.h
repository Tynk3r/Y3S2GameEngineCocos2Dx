#pragma once
#include <iostream>
#include <vector>
#include "cocos2d.h"
#include <string>

using namespace std;

class CAnimation 
{
public:
	static cocos2d::Animate* createAnimation(string spriteNames[], int numOfFrames, int xSize, int ySize, float delay);

};