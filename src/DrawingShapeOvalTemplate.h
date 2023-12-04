#pragma once
#include "DrawingShape.h"
#include "Pen.h"

template<std::size_t N>
class DrawingShapeOvalTemplate : public DrawingShape {
public:
    DrawingShapeOvalTemplate(Pen& pen,
                     const sf::FloatRect& renderArea);

    virtual void startDrawing(const sf::Vector2f& position);
    virtual void stopDrawing();
    virtual void move(const sf::Vector2f& position);

private:
    void drawOval(int minX, int minY, int maxX, int maxY);

private:
    Pen& mPen;
    sf::Vector2f mStartPosition;
    sf::Vector2f mCurrentPosition;

    sf::RectangleShape mRectangleShape;
    sf::CircleShape mCircleShape;
};

#include "DrawingShapeOvalTemplate.inl"