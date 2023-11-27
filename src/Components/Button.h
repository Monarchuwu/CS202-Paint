#pragma once
#include "Box.h"
#include "PressMethod.h"

class Button : public Box, public PressMethod {
public:
    // Default constructor
    Button(const sf::Vector2f& size = sf::Vector2f(0, 0));
};