#pragma once
#include "DrawingShape.h"
#include "Pen.h"

class DrawingShapeRectangle : public DrawingShape {
public:
    DrawingShapeRectangle(Pen& pen,
                           const sf::FloatRect& renderArea);

    virtual void startDrawing(const sf::Vector2f& position);
    virtual void stopDrawing();
    virtual void move(const sf::Vector2f& position);

private:
    void drawRectangle(int minX, int minY, int maxX, int maxY);

private:
    Pen& mPen;
    sf::Vector2f mStartPosition;
    sf::Vector2f mCurrentPosition;

    sf::RectangleShape mRectangleShape;
    sf::CircleShape mCircleShape;
};
