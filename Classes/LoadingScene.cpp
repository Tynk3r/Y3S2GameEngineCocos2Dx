/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "LoadingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
    return LoadingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in LoadingSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
	auto visibleSize = Director::getInstance()->getVisibleSize();

	label = Label::createWithTTF("Loading Next Scene", "fonts/Marker Felt.ttf", 24);
	if (label != nullptr)
	{
		label->setPosition(Vec2((int)visibleSize.width >> 1, (int)visibleSize.height >> 1));
		this->addChild(label, 1);
	}

	label = Label::createWithTTF("0%", "fonts/Marker Felt.ttf", 24);
	if (label != nullptr)
	{
		label->setPosition(Vec2((int)visibleSize.width >> 1, ((int)visibleSize.height >> 1) - 30));
		this->addChild(label, 1);
	}

	numOfResources = 10;
	curResource = 0;
	Resources[0] = "big.png";
	Resources[1] = "big - Copy.png";
	Resources[2] = "big - Copy (1).png";
	Resources[3] = "big - Copy (2).png";
	Resources[4] = "big - Copy (3).png";
	Resources[5] = "big - Copy (4).png";
	Resources[6] = "big - Copy (5).png";
	Resources[7] = "big - Copy (6).png";
	Resources[8] = "big - Copy (7).png";
	Resources[9] = "big - Copy (8).png";

	auto director = Director::getInstance();
	TextureCache* textureCache = director->getTextureCache();
	textureCache->addImageAsync(Resources[0], CC_CALLBACK_1(LoadingScene::loadingTextureFinished, this));
    return true;
}

void LoadingScene::update(float dt)
{
	auto scene = LoadingScene::createScene();
	auto director = Director::getInstance();
	return director->replaceScene(scene);
}


void LoadingScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void LoadingScene::loadingTextureFinished(Texture2D * texture)
{
	auto director = Director::getInstance();
	curResource++;

	int percentage = curResource * 100 / numOfResources;
	label->setString(CCString::createWithFormat("%d%%", percentage)->getCString());
	if (curResource < numOfResources)
	{
		TextureCache* textureCache = director->getTextureCache();
		textureCache->addImageAsync(Resources[curResource], CC_CALLBACK_1(LoadingScene::loadingTextureFinished, this));
	}
	else
	{
		auto scene = HelloWorld::createScene();
		return director->replaceScene(scene);
	}

}
