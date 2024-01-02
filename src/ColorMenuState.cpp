#include "ColorMenuState.h"
#include "Utility.h"

#include <cassert>
#include <string>

ColorMenuState::ColorMenuState(StateStack& stack, Context context, sf::Color inputColor, std::function<void(sf::Color)> callback)
    : State(stack, context),
      mOKCallback(callback),
      mScale(100),
      mActualColor(),
      mDisplayColor(),
      mBackground(sf::Vector2f(610, 390)),
      mColorTable(this, sf::FloatRect(400, 200, 320, 320)),
      mDisplayColorRectangle(sf::Vector2f(55, 320)),
      mScaleScrollBar(this, context.textures, Textures::ScrollBarColors, sf::Vector2f(815, 200), 100, 0),
      mInputBoxR(),
	  mInputBoxG(),
      mInputBoxB(),
      mInputBoxHexaDecimal(),
      mLabels(new GUI::Container(sf::Vector2f())),
      mButtons(new GUI::Container(sf::Vector2f(610, 60))) {
	mBackground.setFillColor(sf::Color(32, 32, 32));
	mBackground.setPosition(390, 190);

	mDisplayColorRectangle.setPosition(745, 200);

	setUp4InputBoxes(context, sf::Vector2f(840, 200));
	setUp2Buttons(context, sf::Vector2f(400, 530));

	updateDisplayColor(inputColor);
	updateDisplay();
}

void ColorMenuState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(mBackground);
    mColorTable.draw(window);
    window.draw(mDisplayColorRectangle);
    mScaleScrollBar.draw(window);
    window.draw(*mInputBoxHexaDecimal);
    window.draw(*mInputBoxR);
    window.draw(*mInputBoxG);
    window.draw(*mInputBoxB);
    window.draw(*mLabels);
	window.draw(*mButtons);
}

bool ColorMenuState::update(sf::Time deltaTime) {
	return false;
}

bool ColorMenuState::handleEvent(const sf::Event& event) {
	mColorTable.handleEvent(event);
	mScaleScrollBar.handleEvent(event);

	if (mInputBoxHexaDecimal->handleEvent(event)) return false;
	if (mInputBoxR->handleEvent(event)) return false;
	if (mInputBoxG->handleEvent(event)) return false;
	if (mInputBoxB->handleEvent(event)) return false;

	if (mButtons->handleEvent(event)) return false;

	return false;
}

void ColorMenuState::updateActualColor(sf::Color color) {
	mActualColor = color;
	mDisplayColor.r = mActualColor.r * mScale / 100;
	mDisplayColor.g = mActualColor.g * mScale / 100;
	mDisplayColor.b = mActualColor.b * mScale / 100;
	updateDisplay();
}

void ColorMenuState::updateDisplayColor(sf::Color color) {
	mDisplayColor = color;
	int mx        = std::max({ mDisplayColor.r, mDisplayColor.g, mDisplayColor.b });

	if (mx == 0) {
		mScale = 0;
		mActualColor.r = 255;
		mActualColor.g = 255;
		mActualColor.b = 255;
	}
	else {
		mScale         = mx / 2.55 + 0.00001f;
		mActualColor.r = mDisplayColor.r * 100 / mScale;
		mActualColor.g = mDisplayColor.g * 100 / mScale;
		mActualColor.b = mDisplayColor.b * 100 / mScale;
	}

	updateDisplay();
}

void ColorMenuState::updateActualColorParameter(ColorParameterType type, int value) {
	switch (type) {
		case ColorParameterType::Red:
			mActualColor.r = value;
			break;
		case ColorParameterType::Green:
			mActualColor.g = value;
			break;
		case ColorParameterType::Blue:
			mActualColor.b = value;
			break;
		case ColorParameterType::Scale:
			mScale = value;
			break;
		default:
			assert(false);
	}
	updateActualColor(mActualColor);
}

void ColorMenuState::updateDisplayColorParameter(ColorParameterType type, int value) {
	switch (type) {
		case ColorParameterType::Red:
			mDisplayColor.r = value;
			break;
		case ColorParameterType::Green:
			mDisplayColor.g = value;
			break;
		case ColorParameterType::Blue:
			mDisplayColor.b = value;
			break;
		default:
			assert(false);
	}
	updateDisplayColor(mDisplayColor);
}

void ColorMenuState::updateDisplay() {
	mColorTable.updateSelectedColor(mActualColor);
	mDisplayColorRectangle.setFillColor(mDisplayColor);
	mScaleScrollBar.updateValue(mScale);
	mScaleScrollBar.updateColor(mActualColor);
	mInputBoxHexaDecimal->setString(toStringHexaDecimal(mDisplayColor.toInteger() / 256));
	mInputBoxR->setString(toString(int(mDisplayColor.r)));
	mInputBoxG->setString(toString(int(mDisplayColor.g)));
	mInputBoxB->setString(toString(int(mDisplayColor.b)));
}

void ColorMenuState::setUp4InputBoxes(Context& context, sf::Vector2f position) {
	mInputBoxR = std::make_shared<GUI::DecimalInputBox>(context.fonts, context.textures,
	                                                    Textures::InputBoxNormal,
	                                                    Textures::InputBoxSelected,
	                                                    Textures::InputBoxPressed);
	mInputBoxR->setMinValue(0);
	mInputBoxR->setMaxValue(255);
	mInputBoxR->setMaxCharacters(3);
	mInputBoxR->setTextChangedCallback([this](std::string str) {
	    int value = str.empty() ? 0 : std::stoi(str);
	    updateDisplayColorParameter(ColorParameterType::Red, value);
	});

	mInputBoxG = std::make_shared<GUI::DecimalInputBox>(context.fonts, context.textures,
	                                                    Textures::InputBoxNormal,
	                                                    Textures::InputBoxSelected,
	                                                    Textures::InputBoxPressed);
	mInputBoxG->setMinValue(0);
	mInputBoxG->setMaxValue(255);
	mInputBoxG->setMaxCharacters(3);
	mInputBoxG->setTextChangedCallback([this](std::string str) {
	    int value = str.empty() ? 0 : std::stoi(str);
	    updateDisplayColorParameter(ColorParameterType::Green, value);
	});

	mInputBoxB = std::make_shared<GUI::DecimalInputBox>(context.fonts, context.textures,
	                                                    Textures::InputBoxNormal,
	                                                    Textures::InputBoxSelected,
	                                                    Textures::InputBoxPressed);
	mInputBoxB->setMinValue(0);
	mInputBoxB->setMaxValue(255);
	mInputBoxB->setMaxCharacters(3);
	mInputBoxB->setTextChangedCallback([this](std::string str) {
	    int value = str.empty() ? 0 : std::stoi(str);
	    updateDisplayColorParameter(ColorParameterType::Blue, value);
	});

	mInputBoxHexaDecimal = std::make_shared<GUI::InputBox>(context.fonts, context.textures,
	                                                       Textures::InputBoxNormal,
	                                                       Textures::InputBoxSelected,
	                                                       Textures::InputBoxPressed,
	                                                       [](sf::Uint32 c) -> bool {
	                                                           return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
	                                                       });
	mInputBoxHexaDecimal->setMaxCharacters(6);
	mInputBoxHexaDecimal->setDefaultCharacter('0');
	mInputBoxHexaDecimal->setTextChangedCallback([this](std::string str) {
	    int value = str.empty() ? 0 : std::stoi(str, nullptr, 16);
	    int r     = value / 0x10000;
	    int g     = (value / 0x100) % 0x100;
	    int b     = value % 0x100;
	    updateDisplayColor(sf::Color(r, g, b));
	});

	mInputBoxHexaDecimal->setPosition(position + sf::Vector2f(0, 25));
	mInputBoxR->setPosition(position + sf::Vector2f(0, 105));
	mInputBoxG->setPosition(position + sf::Vector2f(0, 185));
	mInputBoxB->setPosition(position + sf::Vector2f(0, 265));

	mLabels->setPosition(position);
	GUI::Label::Ptr mLabelR(new GUI::Label("Red", context.fonts));
	GUI::Label::Ptr mLabelG(new GUI::Label("Green", context.fonts));
	GUI::Label::Ptr mLabelB(new GUI::Label("Blue", context.fonts));
	GUI::Label::Ptr mLabelHexaDecimal(new GUI::Label("Code", context.fonts));

	mLabelHexaDecimal->setPosition(75, 15);
	mLabelR->setPosition(75, 95);
	mLabelG->setPosition(75, 175);
	mLabelB->setPosition(75, 255);

	mLabels->pack(mLabelHexaDecimal);
	mLabels->pack(mLabelR);
	mLabels->pack(mLabelG);
	mLabels->pack(mLabelB);
}

void ColorMenuState::setUp2Buttons(Context& context, sf::Vector2f position) {
	mButtons->setPosition(position);
	mButtons->setBackgroundColor(sf::Color::Transparent);

	GUI::Button::Ptr mButtonOK(new GUI::Button(context.fonts, context.textures,
	                                           Textures::ButtonOK290x40,
	                                           Textures::ButtonOK290x40,
	                                           Textures::ButtonOK290x40));
	GUI::Button::Ptr mButtonCancel(new GUI::Button(context.fonts, context.textures,
	                                               Textures::ButtonCancel290x40,
	                                               Textures::ButtonCancel290x40,
	                                               Textures::ButtonCancel290x40));

	mButtonOK->setPosition(0, 0);
	mButtonCancel->setPosition(300, 0);

	mButtonOK->setCallback([this]() {
	    if (mOKCallback) mOKCallback(mDisplayColor);
	    requestStackPop();
	    quit();
	});
	mButtonCancel->setCallback([this]() {
	    requestStackPop();
	    quit();
	});

	mButtons->pack(mButtonOK);
	mButtons->pack(mButtonCancel);
}