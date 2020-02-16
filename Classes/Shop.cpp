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
#pragma once
#include "Shop.h"
#include "MainMenuScene.h"
#include "SceneManagement/SceneManager.h"
#include "SimpleAudioEngine.h"
#include "UI/UI.h"
#include "Nodes.h"
#include "HelloWorldScene.h"

Scene* Shop::createScene()
{
	return Shop::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in EmptySceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Shop::init()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//audio->playBackgroundMusic("BackgroundMusic.wav", true);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	// Start // Load the level
	auto BackButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Button_Disable.png", Vec2(visibleSize.width / 2, visibleSize.height * 0.20f), "Back", this);
	BackButton->addTouchEventListener(CC_CALLBACK_2(Shop::ButtonEventChangeScene, this));

	// Settings // Open settings menu
	//// Settings has 2 sliders, 2 checkbox // BGM, SFX // 2 text for BGM and SFX
	auto BGMLabel = UI::createTTFLabel("SHOP", Vec2(visibleSize.width / 2, visibleSize.height * 0.90f), "fonts/Marker Felt.ttf", 48, 1, this);
	
	auto adNode = Node::create();
	adNode->setName("adNode");
	auto MainSpriteNode = Nodes::CreateNodeUsingTextureCache(adNode, "advertisment", "advertisement.png", Vec2(0.5, 0.5), Vec2(visibleSize.width * .5f, visibleSize.height * .5f), 1, 0.1f);

	return true;
}


void Shop::ButtonEventChangeScene(Ref * sender, ui::Button::TouchEventType type)
{
	std::vector<std::string> tempResources;
	MainMenuScene* tempScene = new MainMenuScene(); // So Init isn't called immediately
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		tempResources.push_back("Blue_Back1.png");
		tempResources.push_back("Blue_Front1.png");
		tempResources.push_back("Blue_Front2.png");
		tempResources.push_back("Blue_Front3.png");
		tempResources.push_back("ZigzagGrass_Mud_Round.png");

		SceneManager::GetInstance()->ReplaceScene(tempScene, tempResources);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}



