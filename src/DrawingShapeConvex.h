#pragma once
#include "DrawingShape.h"
#include "Pen.h"

#include <vector>

class DrawingShapeConvex : public DrawingShape {
protected:
    DrawingShapeConvex(Pen& pen, TextureHolder* textures,
                       const sf::FloatRect& renderArea,
                       std::size_t pointCount);

protected:
    void drawConvex(const std::vector<sf::Vector2f>& vertices);

private:
    void drawConvex();
    void drawOutline(const std::vector<sf::Vector2f>& vertices);

private:
    Pen& mPen;
    sf::ConvexShape mShape;
    sf::RectangleShape mRectangleShape;
    sf::CircleShape mCircleShape;
};