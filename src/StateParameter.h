#pragma once
#include "SFML/Graphics.hpp"

#include <functional>

struct ColorMenuStateParameter {
    sf::Color inputColor;
    std::function<void(sf::Color)> callback;
};

class StateParameter {
public:
    ColorMenuStateParameter colorMenu;
};