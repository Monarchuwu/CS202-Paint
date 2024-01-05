#pragma once
#include "DrawingShape.h"
#include "Pen.h"

#include <vector>

// this class is not used in the current version of the program
// constructor scope is changed from protected to private
class DrawingShapeLineStrip : public DrawingShape {
private:
    DrawingShapeLineStrip(Pen& pen, TextureHolder* textures,
                          const sf::FloatRect& renderArea);

protected:
    void drawLineStrip(const std::vector<sf::Vector2f>& vertices);

private:
    Pen& mPen;
    sf::RectangleShape mRectangleShape;
    sf::CircleShape mCircleShape;
};