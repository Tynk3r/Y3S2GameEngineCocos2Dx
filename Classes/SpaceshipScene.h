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

#ifndef __SPACESHIP_SCENE_H__
#define __SPACESHIP_SCENE_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "HUDLayer.h"
#include "UI/CocosGUI.h"
#include <vector>
#include <iostream>

using namespace cocos2d;

class SpaceshipScene : public cocos2d::Scene
{
private:
	GLProgram* proPostProcess;
	RenderTexture* rendtex;
	Sprite* rendtexSprite;
    std::vector<GameObject*> m_goList;
	float darkness = 1.0f;
    HUDLayer* hud;
	HUDLayer* deathScreen;
    GameObject* player;
    int points;
    float asteroidSpawnTime;
    float enemySpawnTime;
    float healthPackSpawnTime;
    int numOfAsteroids;
    int numOfEnemies;
	int playerHealthPacks = 1;
	char text[256];
	int numOfHealthpacks;

public:
    Node* spriteNode;

    static Scene* createScene();

    virtual bool init();
    
	//Keyboard Event
	//std::vector<cocos2d::EventKeyboard::KeyCode> keysHeld;
	void Update(float interval);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void ShootButtonEvent(Ref* sender, ui::Button::TouchEventType type);

    GameObject* FetchGO(cocos2d::Node* node_, GameObject::GAMEOBJECT_TYPE type);

	void RespawnPlayer(Ref * sender, cocos2d::ui::Button::TouchEventType type);

	void UseHealthpack(Ref * sender, cocos2d::ui::Button::TouchEventType type);

	void BackToMainMenu(Ref * sender, cocos2d::ui::Button::TouchEventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(SpaceshipScene);
};

#endif // __HELLOWORLD_SCENE_H__
