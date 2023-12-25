#pragma once
#include "ColorEditingCenter.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics.hpp>

class VerticalScrollBar {
public:
    VerticalScrollBar(ColorEditingCenter* center,
                      TextureHolder* textures,
                      Textures::ID textureID,
                      const sf::Vector2f& position,
                      int topValue, int bottomValue);

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target) const;

    void updateValue(int value);
    void updateColor(sf::Color color);

private:
    ColorEditingCenter* mCenter;
    int mTopValue, mBottomValue, mCurrentValue;

    sf::Sprite mBackground;
    sf::CircleShape mButton;

    bool mIsHold;
};
