#include "DrawingShapeLine.h"

#include <cmath>

DrawingShapeLine::DrawingShapeLine(Pen& pen,
                                   const sf::FloatRect& renderArea)
    : DrawingShapeLineStrip(pen, renderArea),
      mStartPosition(),
      mCurrentPosition() {
}

void DrawingShapeLine::startDrawing(const sf::Vector2f& position) {
    resetBoundingBox(position);
    mStartPosition = mCurrentPosition = position;
    clear();
}

void DrawingShapeLine::stopDrawing() {
    updateBoundingBox(mCurrentPosition);
}

void DrawingShapeLine::move(const sf::Vector2f& position) {
    // clear the render texture to draw a new shape
    clear();

    drawLineStrip(std::vector<sf::Vector2f>{mStartPosition, position});

    mCurrentPosition = position;
}