#pragma once
#include "DrawingShapeLineStrip.h"
#include "Pen.h"

template<std::size_t N>
class DrawingShapeOvalTemplate : public DrawingShapeLineStrip {
public:
    DrawingShapeOvalTemplate(Pen& pen,
                     const sf::FloatRect& renderArea);

    virtual void startDrawing(const sf::Vector2f& position);
    virtual void stopDrawing();
    virtual void move(const sf::Vector2f& position);

private:
    void drawOval(int minX, int minY, int maxX, int maxY);

private:
    sf::Vector2f mStartPosition;
    sf::Vector2f mCurrentPosition;
};

#include "DrawingShapeOvalTemplate.inl"