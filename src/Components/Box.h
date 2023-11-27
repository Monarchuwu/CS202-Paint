#pragma once
#include <SFML/Graphics.hpp>
#include "ContainMethod.h"
#include "HideMethod.h"

// Inherit 'sf::RectangleShape'
// Draw 'sf::Text' (with 'std::string') at Center / Left
class Box : public sf::RectangleShape, public ContainMethod, public HideMethod {
public:
    // Default constructor
    Box(const sf::Vector2f& size = sf::Vector2f(0, 0));

    // set Font
    virtual void setFont(const sf::Font& font);

    // set Text
    void setText(const std::string& text);

    // get Text
    const std::string& getText() const;

    // add a char at the end of Text
    void addChar(const sf::Uint32& c);

    // remove a char at the end of Text
    void removeChar();

    // set Style
    virtual void setStyle(sf::Uint32 style);

    // set Character Size
    virtual void setCharacterSize(unsigned int size);

    // set Text Color
    virtual void setTextColor(const sf::Color& color);

    // align Text at center if true
    // align Text at left if false
    void setAlignCenter(bool alignCenter);

    // get align Text
    bool getAlignCenter() const;

    // draw
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /// Contain Method
    // check if point in Box
    bool isContain(sf::Vector2f point) const override;
    bool isContain(float x, float y) const override;

protected:
    // Set Display Text
    void displayText();
    // Set Text Position
    virtual void setTextPosition();

private:
    std::string mString;
    const sf::Font* mFont;
    sf::Text mText;
    bool mIsAlignCenter;
};