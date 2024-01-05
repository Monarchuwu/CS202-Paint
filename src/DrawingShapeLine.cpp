#include "DrawingShapeLine.h"

#include <cmath>

DrawingShapeLine::DrawingShapeLine(Pen& pen, TextureHolder* textures,
                                   const sf::FloatRect& renderArea)
    : DrawingShapeConvex(pen, textures, renderArea, 2),
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

    drawConvex(std::vector<sf::Vector2f>{mStartPosition, position});

    mCurrentPosition = position;
}