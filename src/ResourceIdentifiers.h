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

        ButtonShapeLinesStripNormal,
        ButtonShapeLinesStripSelected,
        ButtonShapeLinesStripPressed = ButtonShapeLinesStripSelected,
        ButtonShapeLineNormal,
        ButtonShapeLineSelected,
        ButtonShapeLinePressed = ButtonShapeLineSelected,
        ButtonShapeRectangleNormal,
        ButtonShapeRectangleSelected,
        ButtonShapeRectanglePressed = ButtonShapeRectangleSelected,
        ButtonShapeOvalNormal,
        ButtonShapeOvalSelected,
        ButtonShapeOvalPressed = ButtonShapeOvalSelected,
        ButtonShapeTriangleNormal,
        ButtonShapeTriangleSelected,
        ButtonShapeTrianglePressed = ButtonShapeTriangleSelected,
        ButtonShapeRightTriangleNormal,
        ButtonShapeRightTriangleSelected,
        ButtonShapeRightTrianglePressed = ButtonShapeRightTriangleSelected,
        ButtonShapeDiamondNormal,
        ButtonShapeDiamondSelected,
        ButtonShapeDiamondPressed = ButtonShapeDiamondSelected,
        ButtonShapeFillNormal,
        ButtonShapeFillSelected,
		ButtonShapeFillPressed = ButtonShapeFillSelected,

        ButtonShapeTextWritingNormal,
        ButtonShapeTextWritingSelected,
        ButtonShapeTextWritingPressed = ButtonShapeTextWritingSelected,

        ButtonHistoryPanelNormal,
        ButtonHistoryPanelSelected,
        ButtonHistoryPanelPressed = ButtonHistoryPanelSelected,

        ButtonZoomOption,
        ButtonZoomNormal,
        ButtonZoomSelected,
        ButtonZoomPressed = ButtonZoomSelected,

        ButtonColorEditNormal,
        ButtonColorEditSelected = ButtonColorEditNormal,
        ButtonColorEditPressed  = ButtonColorEditNormal,

        InputBoxNormal,
        InputBoxSelected,
        InputBoxPressed  = InputBoxSelected,

        ScrollBarColors,

        BlackWhite2x2,
        Transparent70x40,
        DarkGray100x40,
        CircleWhite20x20,
        CircleWhite30x30,
        CircleWhite30x30_outline4,
        ButtonOK290x40,
        ButtonCancel290x40,

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