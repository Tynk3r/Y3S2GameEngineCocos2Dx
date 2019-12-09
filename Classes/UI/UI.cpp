#include "UI.h"

USING_NS_CC;

UI::UI()
{
}


UI::~UI()
{
}

Label* UI::createTTFLabel(std::string text, cocos2d::Vec2 position, std::string fontfilepath, int fontSize, int outlineSize)
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
	return myLabel;
}

Label * UI::createSystemFontLabel(std::string text, std::string systemFont, int fontSize)
{
	Label* myLabel = Label::createWithSystemFont(text, systemFont, fontSize);
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
cocos2d::ui::Button * UI::createButton(const::std::string & normalImage, const::std::string & selectedImage, const::std::string & disabledImage, cocos2d::Vec2 position, std::string buttonText)
{
	auto button = ui::Button::create(normalImage, selectedImage, disabledImage);
	button->setTitleText(buttonText);
	button->setPosition(position);
	return button;
}

// CheckBox
cocos2d::ui::CheckBox * UI::createCheckBox(const::std::string & checkBoxNormal, const::std::string & checkBoxNormalSelected, const::std::string & checkBoxNormalDisabled, const::std::string & checkBoxActive, const::std::string & checkBoxActiveDisabled, cocos2d::Vec2 position, std::string buttonText)
{
	auto checkbox = ui::CheckBox::create(checkBoxNormal,
		checkBoxNormalSelected, checkBoxActive,
		checkBoxNormalDisabled, checkBoxActiveDisabled);
	return checkbox;
}

// slider 
cocos2d::ui::Slider * UI::createSlider(const::std::string sliderTexture, const::std::string sliderHandleTexture, const::std::string sliderHandlePressedTexture, const::std::string sliderHandleDisabledTexture, const::std::string sliderProgressBarTexture)
{
	auto slider = ui::Slider::create();
	slider->loadBarTexture(sliderTexture);
	slider->loadSlidBallTextures(sliderHandleTexture, sliderHandlePressedTexture,
		sliderHandleDisabledTexture);
	slider->loadProgressBarTexture(sliderProgressBarTexture);
	return slider;
}

// Loading bar 
cocos2d::ui::LoadingBar * UI::createLoadingBar(const::std::string LoadingBarTexture, cocos2d::ui::LoadingBar::Direction LoadingBarDirection)
{
	auto loadingBar = ui::LoadingBar::create(LoadingBarTexture);
	loadingBar->setDirection(LoadingBarDirection);
	return loadingBar;
}

// Text Input for the player
cocos2d::ui::TextField * UI::createTextField(const::std::string PlaceHolderText, const::std::string FontName, int FontSize, bool PasswordEnabled, int TextFieldLength)
{
	auto textField = ui::TextField::create(PlaceHolderText, FontName, FontSize);
	textField->setPasswordEnabled(PasswordEnabled);
	textField->setMaxLength(TextFieldLength);
	return textField;
}

