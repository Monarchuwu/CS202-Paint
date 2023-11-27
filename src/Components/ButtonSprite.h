#pragma once
#include <SFML/Graphics.hpp>
#include "ContainMethod.h"
#include "PressMethod.h"
#include "HideMethod.h"

class ButtonSprite : public sf::Sprite, public ContainMethod, public PressMethod, public HideMethod {
public:
    // default constructor
    ButtonSprite();

    // constructor with texture
    ButtonSprite(const sf::Texture* texture);

    // set texture of button
    void setTexture(const sf::Texture* texture);

    // get texture of button
    const sf::Texture* getTexture() const;

    // check if point in Button
    bool isContain(sf::Vector2f point) const override;
    bool isContain(float x, float y) const override;

private:
    // set texture of button (internal)
    void setTexture();

private:
    // texture of button
    const sf::Texture* mTexture;
};
