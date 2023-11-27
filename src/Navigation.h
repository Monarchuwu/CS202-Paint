#pragma once
#include <SFML/Graphics.hpp>
#include "EventHandler.h"

class Navigation : public sf::Drawable, public EventHandler {
private:
	sf::FloatRect mNavigationRect;
	sf::RectangleShape mBackground;

public:
	Navigation(const sf::FloatRect& rect);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
