#pragma once
#include "SFML/Graphics.hpp"
#include "ColorEditingCenter.h"

class ColorTable {
public:
    ColorTable(ColorEditingCenter* center, const sf::FloatRect& objectArea);

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target) const;

    void updateSelectedColor(sf::Color color);

private:
    void buildColumnColorTable(int column, sf::Color color);
    void selectPosition(sf::Vector2i position);

private:
    ColorEditingCenter* mCenter;
    sf::FloatRect mObjectArea;

    sf::Image mImage;
    sf::Vector2i mCoordTable[3][256][256];

    sf::Texture mTexture;
    sf::Sprite mSprite;

    sf::CircleShape mSelectedCircle;

    bool mIsHold;
};
