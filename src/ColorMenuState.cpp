#include "ColorMenuState.h"

#include <cassert>

ColorMenuState::ColorMenuState(StateStack& stack, Context context)
    : State(stack, context),
      mScale(100),
      mActualColor(sf::Color::Red),
      mDisplayColor(sf::Color::Red),
      mBackground(sf::Vector2f(450, 340)),
      mColorTable(this, sf::FloatRect(400, 200, 320, 320)),
      mDisplayColorRectangle(sf::Vector2f(55, 320)),
      mScaleScrollBar(this, context.textures, Textures::ScrollBarColors, sf::Vector2f(815, 200), 100, 0) {
	mBackground.setFillColor(sf::Color(38, 38, 38));
	mBackground.setPosition(390, 190);

	mDisplayColorRectangle.setPosition(745, 200);

    updateDisplay();
}

void ColorMenuState::draw() {
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackground);
    mColorTable.draw(window);
	window.draw(mDisplayColorRectangle);
	mScaleScrollBar.draw(window);
}

bool ColorMenuState::update(sf::Time deltaTime) {
	return false;
}

bool ColorMenuState::handleEvent(const sf::Event& event) {
	mColorTable.handleEvent(event);
	mScaleScrollBar.handleEvent(event);

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Escape) {
			requestStackPop();
		    quit();
			return false;		
		}
	}
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
}