#include "HorizontalScrollBar.h"
#include "ZoomController.h"

HorizontalScrollBar::HorizontalScrollBar(ZoomController* zoomController,
                                         sf::FloatRect objectArea,
                                         float widthBar,
                                         sf::Color leftColor, sf::Color rightColor,
                                         unsigned int minValue, unsigned int maxValue)
    : mZoomController(zoomController),
      mMinValue(minValue),
      mMaxValue(maxValue),
      mCurrentValue(),
      mObjectArea(objectArea),
      mLeftPart(), mRightPart(), mButton(),
      mIsHold(false) {
    mLeftPart.setPosition(mObjectArea.left, mObjectArea.top + mObjectArea.height / 2);
    mLeftPart.setSize(sf::Vector2f(0, widthBar));
    mLeftPart.setOrigin(0, widthBar / 2);
    mLeftPart.setFillColor(leftColor);

    mRightPart.setPosition(mObjectArea.left + mObjectArea.width, mObjectArea.top + mObjectArea.height / 2);
    mRightPart.setSize(sf::Vector2f(0, widthBar));
    mRightPart.setOrigin(0, widthBar / 2);
    mRightPart.setRotation(180);
    mRightPart.setFillColor(rightColor);

    mButton.setPosition(0, mObjectArea.top + mObjectArea.height / 2);
    mButton.setRadius(mObjectArea.height / 2);
    mButton.setOrigin(mObjectArea.height / 2, mObjectArea.height / 2);
    mButton.setFillColor(sf::Color((leftColor.r + rightColor.r) / 2,
                                   (leftColor.g + rightColor.g) / 2,
                                   (leftColor.b + rightColor.b) / 2,
                                   (leftColor.a + rightColor.a) / 2));
}

bool HorizontalScrollBar::handleEvent(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::MouseButtonPressed: {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (mObjectArea.contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (!mIsHold) {
                        mIsHold = true;
                        updateButtonPosition(event.mouseButton.x);
                        return true;
                    }
                }
            }
            break;
        }

        case sf::Event::MouseMoved: {
            if (mIsHold) {
                updateButtonPosition(event.mouseMove.x);
                return true;
            }
            break;
        }

        case sf::Event::MouseButtonReleased: {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (mIsHold) {
					mIsHold = false;
					return true;
				}
            }
        }
    }
    return false;
}

void HorizontalScrollBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mLeftPart, states);
	target.draw(mRightPart, states);
	target.draw(mButton, states);
}

void HorizontalScrollBar::updateValue(unsigned int value) {
    mCurrentValue = value;

    float pos = (mCurrentValue - mMinValue) * mObjectArea.width / (mMaxValue - mMinValue);
    mLeftPart.setSize(sf::Vector2f(pos, mLeftPart.getSize().y));
    mRightPart.setSize(sf::Vector2f(mObjectArea.width - pos, mRightPart.getSize().y));
    mButton.setPosition(mObjectArea.left + pos, mButton.getPosition().y);
}

void HorizontalScrollBar::updateButtonPosition(float x) {
    if (x > mObjectArea.left + mObjectArea.width) {
        x = mObjectArea.left + mObjectArea.width;
    }
    else if (x < mObjectArea.left) {
        x = mObjectArea.left;
    }

    unsigned int value = (x - mObjectArea.left) * (mMaxValue - mMinValue) / mObjectArea.width + mMinValue;
    mZoomController->updateZoomFactor(value);
}