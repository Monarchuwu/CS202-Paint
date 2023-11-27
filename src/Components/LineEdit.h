#pragma once
#include "Button.h"

class LineEdit : public Button {
public:
    // Default constructor
    LineEdit(const sf::Vector2f& size = sf::Vector2f(0, 0));

    // set Font
    virtual void setFont(const sf::Font& font) override;

    // set Style
    virtual void setStyle(sf::Uint32 style) override;

    // set Character Size
    virtual void setCharacterSize(unsigned int size) override;

    // set Text Color
    virtual void setTextColor(const sf::Color& color) override;

    // draw
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    // Set Text Position
    virtual void setTextPosition() override;

private:
    const sf::Font* mFont;
    sf::Text mSearchText;
};
