#include "LineEdit.h"

LineEdit::LineEdit(const sf::Vector2f& size)
    : Button(size) {
    mSearchText.setString("Search");
}

void LineEdit::setFont(const sf::Font& font) {
    Button::setFont(font);
    mFont = &font;
    mSearchText.setFont(*mFont);
}

void LineEdit::setStyle(sf::Uint32 style) {
	Button::setStyle(style);
	mSearchText.setStyle(style);
}

void LineEdit::setCharacterSize(unsigned int size) {
	Button::setCharacterSize(size);
	mSearchText.setCharacterSize(size);
}

void LineEdit::setTextColor(const sf::Color& color) {
	Button::setTextColor(color);
	mSearchText.setFillColor(color);
}

void LineEdit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (getText().empty() && !getPressed()) {
	    target.draw(static_cast<sf::RectangleShape>(*this), states);
        states.transform *= getTransform();
        target.draw(mSearchText, states);
    }
    else Button::draw(target, states);
}

void LineEdit::setTextPosition() {
    Button::setTextPosition();

    sf::FloatRect textRect = mSearchText.getLocalBounds();
    if (getAlignCenter()) {
        mSearchText.setPosition(getSize().x / 2 - textRect.width / 2 - textRect.left,
                                getSize().y / 2 - textRect.height / 2 - textRect.top);
    }
    else {
        mSearchText.setPosition(10, getSize().y / 2 - textRect.height / 2 - textRect.top);
    }
}