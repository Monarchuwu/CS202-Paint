#pragma once
#include <SFML/Graphics.hpp>

class ContainMethod {
public:
	// constructor
	ContainMethod();

	// destructor
	virtual ~ContainMethod();

    // check if point in something
	virtual bool isContain(sf::Vector2f point) const = 0;
	virtual bool isContain(float x, float y) const   = 0;
};