#include "Navigation.h"

Navigation::Navigation(const sf::FloatRect& rect)
	: mNavigationRect(rect),
	  mBackground(rect.getSize()) {
	mBackground.setPosition(rect.getPosition());
    mBackground.setFillColor(sf::Color(255, 255, 255, 10));
}

void Navigation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mBackground, states);
}