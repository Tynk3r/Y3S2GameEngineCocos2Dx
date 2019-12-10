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

#include "MainMenuScene.h"
#include "Scene Management/SceneManager.h"
#include "SimpleAudioEngine.h"
#include "UI/UI.h"
#include "HelloWorldScene.h"

USING_NS_CC;

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
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//audio->playBackgroundMusic("BackgroundMusic.wav", true);
	//audio->getInstance()->setBackgroundMusicVolume(0.0f);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
	// Create a menu
	auto settingsMenu = Menu::create();

	// Start // Load the level
	auto StartButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Button_Disable.png", Vec2(visibleSize.width / 2, visibleSize.height * 0.75f), "Start", this);
	StartButton->addTouchEventListener([&](Ref* sender,
		ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			SceneManager::GetInstance()->ReplaceScene(HelloWorld::createScene());
			break;
		default: break;
		} });
	auto SettingsButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Button_Disable.png", Vec2(visibleSize.width / 2, visibleSize.height * 0.5f), "Settings", this);

	auto ExitButton = UI::createButton("Button_Normal.png", "Button_Press.png", "Button_Disable.png", Vec2(visibleSize.width / 2, visibleSize.height * 0.25f), "Exit", this);
	//MainMenu->addChild(StartButton, 1);
	//MainMenu->addChild(SettingsButton);
	//MainMenu->addChild(ExitButton);
	auto MainMenu = Menu::create();


	// Settings // Open settings menu
	//// Settings has 2 sliders, 2 checkbox // BGM, SFX // 2 text for BGM and SFX
	auto BGMLabel = UI::createTTFLabel("BGM", Vec2(visibleSize.width * 0.68, visibleSize.height * 0.58f), "fonts/Marker Felt.ttf", 24, 1, this);
	auto BGMSlider = UI::createSlider("Slider_Back.png", "SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png", "Slider_PressBar.png", Vec2(visibleSize.width * 0.75, visibleSize.height * 0.55f), this);
	BGMSlider->setMaxPercent(100);
	BGMSlider->setPercent(10);
	BGMSlider->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED:
			log(BGMSlider->getPercent());
			break;
		default: break;
		} });
	auto BGMCheckBox = UI::createCheckBox("CheckBox_Normal.png", "CheckBox_Press.png", "CheckBoxNode_Disable.png", "CheckBox_Disable.png", "CheckBoxNode_Normal.png", Vec2(visibleSize.width * 0.9, visibleSize.height * 0.55f), "Mute", this);
	auto SFXLabel = UI::createTTFLabel("SFX", Vec2(visibleSize.width * 0.68, visibleSize.height * 0.48f), "fonts/Marker Felt.ttf", 24, 1, this);
	auto SFXSlider = UI::createSlider("Slider_Back.png", "SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png", "Slider_PressBar.png", Vec2(visibleSize.width * 0.75, visibleSize.height * 0.45f), this);
	
	auto SFXCheckBox = UI::createCheckBox("CheckBox_Normal.png", "CheckBox_Press.png", "CheckBoxNode_Disable.png", "CheckBox_Disable.png", "CheckBoxNode_Normal.png", Vec2(visibleSize.width * 0.9, visibleSize.height * 0.45f), "Mute", this);
	
	BGMCheckBox->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		default: break;
		} });
	// Exit
	log(BGMSlider->getPercent());
    return true;
}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
