#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class UI
{
public:
	UI();
	~UI();

	static cocos2d::Label* createTTFLabel(std::string text, cocos2d::Vec2 position, std::string fontfilepath, int fontSize, int outlineSize, cocos2d::Scene* scene);
	static cocos2d::Label* createSystemFontLabel(std::string text, std::string systemFont, int fontSize, cocos2d::Vec2 position, cocos2d::Scene* scene);
	static cocos2d::ui::Button* createButton(const::std::string &normalImage, 
		const::std::string &selectedImage, 
		const::std::string &disabledImage, 
		cocos2d::Vec2 position, 
		std::string buttonText, cocos2d::Scene* scene);
	static cocos2d::ui::CheckBox * UI::createCheckBox(const::std::string & checkBoxNormal, 
		const::std::string & checkBoxNormalSelected, 
		const::std::string & checkBoxNormalDisabled, 
		const::std::string & checkBoxActive, 
		const::std::string & checkBoxActiveDisabled, 
		cocos2d::Vec2 position, 
		cocos2d::Scene* scene);
	static cocos2d::ui::Slider * createSlider(const::std::string sliderTexture, 
		const::std::string sliderHandleTexture, 
		const::std::string sliderHandlePressedTexture, 
		const::std::string sliderHandleDisabledTexture, 
		const::std::string sliderProgressBarTexture, 
		int MaxPercentage,
		int Percentage,
		cocos2d::Vec2 position, cocos2d::Scene* scene);
	static cocos2d::ui::LoadingBar * createLoadingBar(const::std::string LoadingBarTexture, cocos2d::ui::LoadingBar::Direction LoadingBarDirection, cocos2d::Vec2 position, cocos2d::Scene* scene);
	static cocos2d::ui::TextField * createTextField(const::std::string PlaceHolderText, const::std::string FontName, int FontSize, bool PasswordEnabled, int TextFieldLength, cocos2d::Vec2 position, cocos2d::Scene* scene);

};

