#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Textures {
    enum ID {
        ButtonSizeNormal,
        ButtonSizeSelected = ButtonSizeNormal,
        ButtonSizePressed  = ButtonSizeNormal,
        ButtonSize1pxNormal,
        ButtonSize1pxSelected,
        ButtonSize1pxPressed = ButtonSize1pxSelected,
        ButtonSize3pxNormal,
        ButtonSize3pxSelected,
        ButtonSize3pxPressed = ButtonSize3pxSelected,
        ButtonSize5pxNormal,
        ButtonSize5pxSelected,
        ButtonSize5pxPressed = ButtonSize5pxSelected,
        ButtonSize8pxNormal,
        ButtonSize8pxSelected,
        ButtonSize8pxPressed = ButtonSize8pxSelected,
        TextureCount
    };
}

namespace Fonts {
    enum ID {
        Sansation,
        FontCount
    };
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;