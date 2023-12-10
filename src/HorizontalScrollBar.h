#pragma once
#include <SFML/Graphics.hpp>

class ZoomController;

class HorizontalScrollBar : public sf::Drawable {
public:
    HorizontalScrollBar(ZoomController* zoomController,
                        sf::FloatRect objectArea,
                        float widthBar,
                        sf::Color leftColor, sf::Color rightColor,
                        unsigned int minValue, unsigned int maxValue);

    bool handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void updateValue(unsigned int value);

private:
    void updateButtonPosition(float x);

private:
    ZoomController* mZoomController;
    unsigned int mMinValue, mMaxValue, mCurrentValue;

    sf::FloatRect mObjectArea;
    sf::RectangleShape mLeftPart, mRightPart;
    sf::CircleShape mButton;

    bool mIsHold;
};
