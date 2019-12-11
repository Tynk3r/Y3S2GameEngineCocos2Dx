#include "UI.h"

USING_NS_CC;

UI::UI()
{
}


UI::~UI()
{
}

Label* UI::createTTFLabel(std::string text, cocos2d::Vec2 position, std::string fontfilepath, int fontSize, int outlineSize, cocos2d::Scene* scene)
{
	TTFConfig labelConfig;
	labelConfig.fontFilePath = fontfilepath;
	labelConfig.fontSize = fontSize;
	labelConfig.glyphs = GlyphCollection::DYNAMIC;
	labelConfig.outlineSize = outlineSize;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;

	Label* myLabel = Label::createWithTTF(labelConfig, text);
	myLabel->setPosition(position);
	scene->addChild(myLabel);
	return myLabel;
}

Label * UI::createSystemFontLabel(std::string text, std::string systemFont, int fontSize, cocos2d::Vec2 position, cocos2d::Scene* scene)
{
	Label* myLabel = Label::createWithSystemFont(text, systemFont, fontSize);
	myLabel->setPosition(position);
	scene->addChild(myLabel);
	return myLabel;
}

//Add this to the ui component after creating it
//UI->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
//switch (type) {
//case ui::Widget::TouchEventType::BEGAN:
//		break;
//case ui::Widget::TouchEventType::ENDED:
//		//std::cout << "slider moved" << std::endl;
//		break;
//	default: break;
//}});


// Button
cocos2d::ui::Button * UI::createButton(const::std::string & normalImage, const::std::string & selectedImage, const::std::string & disabledImage, cocos2d::Vec2 position, std::string buttonText, cocos2d::Scene* scene)
{
	auto button = ui::Button::create(normalImage, selectedImage, disabledImage);
	button->setTitleText(buttonText);
	button->setTitleFontSize(20);
	button->setTitleColor(Color3B(0, 0, 0));
	button->setPosition(position);
	scene->addChild(button);
	return button;
}

// CheckBox
cocos2d::ui::CheckBox * UI::createCheckBox(const::std::string & checkBoxNormal, const::std::string & checkBoxNormalSelected, const::std::string & checkBoxNormalDisabled, const::std::string & checkBoxActive, const::std::string & checkBoxActiveDisabled, cocos2d::Vec2 position, cocos2d::Scene* scene)
{
	auto checkbox = ui::CheckBox::create(checkBoxNormal,
		checkBoxNormalSelected, checkBoxActive,
		checkBoxNormalDisabled, checkBoxActiveDisabled);
	checkbox->setPosition(position);
	scene->addChild(checkbox);
	return checkbox;
}

// slider 
cocos2d::ui::Slider * UI::createSlider(const::std::string sliderTexture, const::std::string sliderHandleTexture, const::std::string sliderHandlePressedTexture, const::std::string sliderHandleDisabledTexture, const::std::string sliderProgressBarTexture, int MaxPercentage, int Percentage, cocos2d::Vec2 position, cocos2d::Scene * scene)
{
	auto slider = ui::Slider::create();
	slider->loadBarTexture(sliderTexture);
	slider->loadSlidBallTextures(sliderHandleTexture, sliderHandlePressedTexture,
		sliderHandleDisabledTexture);
	slider->loadProgressBarTexture(sliderProgressBarTexture);
	slider->setPosition(position);
	slider->setMaxPercent(MaxPercentage);
	slider->setPercent(Percentage);
	scene->addChild(slider);
	return slider;
}

// Loading bar 
cocos2d::ui::LoadingBar * UI::createLoadingBar(const::std::string LoadingBarTexture, cocos2d::ui::LoadingBar::Direction LoadingBarDirection, cocos2d::Vec2 position, cocos2d::Scene* scene)
{
	auto loadingBar = ui::LoadingBar::create(LoadingBarTexture);
	loadingBar->setDirection(LoadingBarDirection);
	loadingBar->setPosition(position);
	scene->addChild(loadingBar);
	return loadingBar;
}

// Text Input for the player
cocos2d::ui::TextField * UI::createTextField(const::std::string PlaceHolderText, const::std::string FontName, int FontSize, bool PasswordEnabled, int TextFieldLength, cocos2d::Vec2 position, cocos2d::Scene* scene)
{
	auto textField = ui::TextField::create(PlaceHolderText, FontName, FontSize);
	textField->setPasswordEnabled(PasswordEnabled);
	textField->setMaxLength(TextFieldLength);
	textField->setPosition(position);
	scene->addChild(textField);
	return textField;
}



