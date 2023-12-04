#pragma once
#include "DrawingShape.h"
#include "Pen.h"

#include <vector>

class DrawingShapeLineStrip : public DrawingShape {
protected:
    DrawingShapeLineStrip(Pen& pen,
                          const sf::FloatRect& renderArea);

protected:
    void drawLineStrip(const std::vector<sf::Vector2f>& vertices);

private:
    Pen& mPen;
    sf::RectangleShape mRectangleShape;
    sf::CircleShape mCircleShape;
};