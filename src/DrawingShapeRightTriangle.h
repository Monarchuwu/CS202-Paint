#pragma once
#include "DrawingShape.h"
#include "Pen.h"

class DrawingShapeRightTriangle : public DrawingShape {
public:
    DrawingShapeRightTriangle(Pen& pen,
                              const sf::FloatRect& renderArea);

    virtual void startDrawing(const sf::Vector2f& position);
    virtual void stopDrawing();
    virtual void move(const sf::Vector2f& position);

private:
    void drawTriangle(int minX, int minY, int maxX, int maxY);
    void drawLine(const sf::Vector2f& from, const sf::Vector2f& to);

private:
    Pen& mPen;
    sf::Vector2f mStartPosition;

    sf::RectangleShape mRectangleShape;
    sf::RectangleShape mRectangleShapeLine;
    sf::CircleShape mCircleShape;
};
