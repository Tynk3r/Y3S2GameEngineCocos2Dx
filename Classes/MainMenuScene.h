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

#ifndef __EMPTYSCENE_SCENE_H__
#define __EMPTYSCENE_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "extensions/cocos-ext.h"
#include "UI/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(Ref* pSender, ui::Button::TouchEventType type);

	void SliderEventSetPercent(Ref * sender, ui::Slider::EventType type);
	void ButtonEventChangeScene(Ref * sender, ui::Button::TouchEventType type);
	void ButtonEventShopScene(Ref * sender, ui::Button::TouchEventType type);
	void Tweet(Ref* sender, ui::Button::TouchEventType type);
	void CheckBoxEventMuteSound(Ref * sender, ui::CheckBox::EventType type);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
};

#endif // __EmptyScene_SCENE_H__
