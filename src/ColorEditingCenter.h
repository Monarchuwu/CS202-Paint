#pragma once
#include "ColorParameterIdentifiers.h"

#include <SFML/Graphics/Color.hpp>

class ColorEditingCenter {
public:
    virtual void updateActualColor(sf::Color color)                              = 0;
    virtual void updateDisplayColor(sf::Color color)                             = 0;
    virtual void updateActualColorParameter(ColorParameterType type, int value)  = 0;
    virtual void updateDisplayColorParameter(ColorParameterType type, int value) = 0;
};