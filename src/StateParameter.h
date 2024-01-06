#pragma once
#include "SFML/Graphics.hpp"

#include <functional>
#include <memory>

struct ColorMenuStateParameter {
    sf::Color inputColor;
    std::function<void(sf::Color)> callback;
};

struct HandleFileStateParameter {
    const sf::Texture* saveTexture;
};

class StateParameter {
public:
    ColorMenuStateParameter colorMenu;
    HandleFileStateParameter handleFile;
};