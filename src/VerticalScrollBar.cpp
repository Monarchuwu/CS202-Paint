#include "VerticalScrollBar.h"

VerticalScrollBar::VerticalScrollBar(ColorEditingCenter* center,
                                     TextureHolder* textures,
                                     Textures::ID textureID,
                                     const sf::Vector2f& position,
                                     int topValue, int bottomValue)
    : mCenter(center),
      mTopValue(topValue),
      mBottomValue(bottomValue),
      mCurrentValue(topValue),
      mBackground(textures->get(textureID)),
      mButton(),
      mIsHold(false) {
    mBackground.setPosition(position);

    mButton.setRadius(mBackground.getLocalBounds().width / 2);
    mButton.setFillColor(sf::Color::White);
    mButton.setOrigin(mButton.getRadius(), mButton.getRadius());
    mButton.setPosition(position.x + mBackground.getGlobalBounds().width / 2.f,
                        position.y + mBackground.getGlobalBounds().height / 2.f);
    mButton.setOutlineColor(sf::Color::Black);
    mButton.setOutlineThickness(2);
}

void VerticalScrollBar::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
			mIsHold = false;
		}
	}

    if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			if (mBackground.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			    mIsHold = true;

			    int y = event.mouseButton.y - mBackground.getPosition().y;
			    if (y > mBackground.getLocalBounds().height) {
			        y = mBackground.getLocalBounds().height;
			    }
			    else if (y < 0) y = 0;

                int scale = mTopValue + (mBottomValue - mTopValue) * y / mBackground.getLocalBounds().height;
                mCenter->updateActualColorParameter(ColorParameterType::Scale, scale);
			}
		}
	}

    if (event.type == sf::Event::MouseMoved) {
        if (mIsHold) {
            int y = event.mouseMove.y - mBackground.getPosition().y;
            if (y > mBackground.getLocalBounds().height) {
				y = mBackground.getLocalBounds().height;
			}
			else if (y < 0) y = 0;

			int scale = mTopValue + (mBottomValue - mTopValue) * y / mBackground.getLocalBounds().height;
			mCenter->updateActualColorParameter(ColorParameterType::Scale, scale);
		}
	}
}

void VerticalScrollBar::draw(sf::RenderTarget& target) const {
	target.draw(mBackground);
	target.draw(mButton);
}

void VerticalScrollBar::updateValue(int value) {
	mCurrentValue = value;
	float y = mBackground.getPosition().y + mBackground.getLocalBounds().height * (value - mTopValue) / (mBottomValue - mTopValue);
    mButton.setPosition(mButton.getPosition().x, y);
}

void VerticalScrollBar::updateColor(sf::Color color) {
    mBackground.setColor(color);
}