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
#include "HelloWorldScene.h"
#include "SpaceshipScene.h"
#include <CkHttp.h>
#include <CkGlobal.h>
#include <CkHttpRequest.h>
#include <CkHttpResponse.h>

Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in EmptySceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	CkGlobal glob;
	bool success = glob.UnlockBundle("Anything for 30-day trial");
	if (success != true) {
		std::cout << glob.lastErrorText() << "\r\n";
	}
	else
	{
		int status = glob.get_UnlockStatus();
		if (status == 2) {
			std::cout << "Unlocked using purchased unlock code." << "\r\n";
		}
		else {
			std::cout << "Unlocked in trial mode." << "\r\n";
		}
	}
	// The LastErrorText can be examined in the success case to see if it was unlocked in
	// trial more, or with a purchased unlock code.
	std::cout << glob.lastErrorText() << "\r\n";

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
	
	/***********************/
		 	 int i;
			 i = 0 ;
			i +=+ 1 ;
		   i  -=-  1 ;
	/***********************/

	// Create a menu
	auto settingsMenu = Menu::create();

	// Start // Load the level
	auto StartButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Button_Disable.png", Vec2(visibleSize.width / 2, visibleSize.height * 0.75f), "Start", this);
	StartButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::ButtonEventChangeScene, this));

	auto ShopButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Button_Disable.png", Vec2(visibleSize.width / 2, visibleSize.height * 0.62f), "Shop", this);
	ShopButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::ButtonEventShopScene, this));

	auto SettingsButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Button_Disable.png", Vec2(visibleSize.width / 2, visibleSize.height * 0.5f), "Settings", this);

	auto ExitButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Button_Disable.png", Vec2(visibleSize.width / 2, visibleSize.height * 0.25f), "Exit", this);
	ExitButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::menuCloseCallback, this));

	auto TweetButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Button_Disable.png", Vec2(visibleSize.width * 0.25f, visibleSize.height * 0.5f), "Tweet", this);
	TweetButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::Tweet, this));

	auto MainMenu = Menu::create();


	// Settings // Open settings menu
	//// Settings has 2 sliders, 2 checkbox // BGM, SFX // 2 text for BGM and SFX
	auto BGMLabel = UI::createTTFLabel("BGM", Vec2(visibleSize.width * 0.68, visibleSize.height * 0.58f), "fonts/MarkerFelt.ttf", 24, 1, this);
	auto BGMSlider = UI::createSlider("Slider_Back.png", "SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png", "Slider_PressBar.png", 100, 100, Vec2(visibleSize.width * 0.75, visibleSize.height * 0.55f), this);
	BGMSlider->addEventListener(CC_CALLBACK_2(MainMenuScene::SliderEventSetPercent, this));
	auto BGMCheckBox = UI::createCheckBox("CheckBox_Normal.png", "CheckBox_Press.png", "CheckBoxNode_Disable.png", "CheckBox_Disable.png", "CheckBoxNode_Normal.png", Vec2(visibleSize.width * 0.9, visibleSize.height * 0.55f), this);
	BGMCheckBox->addEventListener(CC_CALLBACK_2(MainMenuScene::CheckBoxEventMuteSound, this));
	auto SFXLabel = UI::createTTFLabel("SFX", Vec2(visibleSize.width * 0.68, visibleSize.height * 0.48f), "fonts/MarkerFelt.ttf", 24, 1, this);
	auto SFXSlider = UI::createSlider("Slider_Back.png", "SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png", "Slider_PressBar.png", 100, 100, Vec2(visibleSize.width * 0.75, visibleSize.height * 0.45f), this);
	SFXSlider->addEventListener(CC_CALLBACK_2(MainMenuScene::SliderEventSetPercent, this));

	auto SFXCheckBox = UI::createCheckBox("CheckBox_Normal.png", "CheckBox_Press.png", "CheckBoxNode_Disable.png", "CheckBox_Disable.png", "CheckBoxNode_Normal.png", Vec2(visibleSize.width * 0.9, visibleSize.height * 0.45f), this);
	// Exit
	log(BGMSlider->getPercent());
	return true;
}

void MainMenuScene::menuCloseCallback(Ref* pSender, ui::Button::TouchEventType type)
{
	//Close the cocos2d-x game scene and quit the application
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->end();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MainMenuScene::SliderEventSetPercent(Ref* sender, ui::Slider::EventType type)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		ui::Slider* slider = dynamic_cast<ui::Slider*>(sender);
		int percent = slider->getPercent();
		audio->setBackgroundMusicVolume(percent);
		log("%i", percent);
	}
}

void MainMenuScene::ButtonEventChangeScene(Ref* sender, ui::Button::TouchEventType type)
{
	std::vector<std::string> tempResources;
	SpaceshipScene* tempScene = new SpaceshipScene(); // So Init isn't called immediately
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

void MainMenuScene::ButtonEventShopScene(Ref* sender, ui::Button::TouchEventType type)
{
	std::vector<std::string> tempResources;
	Shop* tempScene = new Shop(); // So Init isn't called immediately
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		tempResources.push_back("Blue_Back1.png");

		SceneManager::GetInstance()->ReplaceScene(tempScene, tempResources);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}

void MainMenuScene::Tweet(Ref* sender, ui::Button::TouchEventType type)
{
	CkHttp http;
	CkHttpRequest req;
	CkHttpResponse* resp = 0;
	std::vector<std::string> tempResources;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		http.put_OAuth1(true);
		http.put_OAuthVerifier("");
		http.put_OAuthConsumerKey("jo3HPmdtDPtfWShc3ddgIC51V");
		http.put_OAuthConsumerSecret("qKHuou6c1mPT5XYKJiL6uI123sVp06xh9PFltaFbOak9FG8FR5");
		http.put_OAuthToken("549162013-9Vx1C9LV5cXqN7VFkruXUpfFdVVD2rgJASnhEQrl");
		http.put_OAuthTokenSecret("sSArrGmMz7YK9aqCbWjruFL97DJ3oMOJy5qrCYfugVdqE");

		req.AddParam("status", "Hey guys! I'm playing PENG SPACESHIP and I'm loving it!");

		resp = http.PostUrlEncoded("https://api.twitter.com/1.1/statuses/update.json", req);

		if (http.get_LastMethodSuccess() != true) {
			std::cout << http.lastErrorText() << "\r\n";
			return;
		}

		if (resp->get_StatusCode() == 200) {
			// Display the JSON response.
			std::cout << resp->bodyStr() << "\r\n";
		}
		else {
			std::cout << http.lastErrorText() << "\r\n";
		}

		delete resp;
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}

void MainMenuScene::CheckBoxEventMuteSound(Ref* sender, ui::CheckBox::EventType type)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		audio->pauseBackgroundMusic();
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		audio->resumeBackgroundMusic();
		break;
	default:
		break;
	}
}


