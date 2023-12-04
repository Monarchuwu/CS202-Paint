#pragma once
#include "DrawingShape.h"
#include "Pen.h"

class DrawingShapeLine : public DrawingShape {
public:
    DrawingShapeLine(Pen& pen,
                          const sf::FloatRect& renderArea);

    virtual void startDrawing(const sf::Vector2f& position);
    virtual void stopDrawing();
    virtual void move(const sf::Vector2f& position);

private:
    void drawLine(const sf::Vector2f& from, const sf::Vector2f& to);

private:
    Pen& mPen;
    sf::Vector2f mStartPosition;
    sf::Vector2f mCurrentPosition;

    sf::RectangleShape mRectangleShape;
    sf::CircleShape mCircleShape;
};
