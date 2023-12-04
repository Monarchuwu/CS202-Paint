#pragma once
#include "DrawingShapeLineStrip.h"
#include "Pen.h"

class DrawingShapeTriangle : public DrawingShapeLineStrip {
public:
    DrawingShapeTriangle(Pen& pen,
                         const sf::FloatRect& renderArea);

    virtual void startDrawing(const sf::Vector2f& position);
    virtual void stopDrawing();
    virtual void move(const sf::Vector2f& position);

private:
    void drawTriangle(int minX, int minY, int maxX, int maxY);

private:
    sf::Vector2f mStartPosition;
    sf::Vector2f mCurrentPosition;
};
