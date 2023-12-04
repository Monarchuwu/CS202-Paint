#include "DrawingShapeRightTriangle.h"

#include <cmath>

DrawingShapeRightTriangle::DrawingShapeRightTriangle(Pen& pen,
                                                     const sf::FloatRect& renderArea)
    : DrawingShapeLineStrip(pen, renderArea),
      mStartPosition(),
      mCurrentPosition() {
}

void DrawingShapeRightTriangle::startDrawing(const sf::Vector2f& position) {
    resetBoundingBox(position);
    mStartPosition = position;
    clear();
}

void DrawingShapeRightTriangle::stopDrawing() {
    updateBoundingBox(mCurrentPosition);
}

void DrawingShapeRightTriangle::move(const sf::Vector2f& position) {
    // clear the render texture to draw a new shape
    clear();

    int minX = std::min(mStartPosition.x, position.x);
    int minY = std::min(mStartPosition.y, position.y);
    int maxX = std::max(mStartPosition.x, position.x);
    int maxY = std::max(mStartPosition.y, position.y);
    drawRightTriangle(minX, minY, maxX, maxY);

    mCurrentPosition = position;
}

void DrawingShapeRightTriangle::drawRightTriangle(int minX, int minY, int maxX, int maxY) {
    std::vector<sf::Vector2f> points(4);

    points[0] = sf::Vector2f(minX, minY);
    points[1] = sf::Vector2f(minX, maxY);
    points[2] = sf::Vector2f(maxX, maxY);
    points[3] = points[0];

    drawLineStrip(points);
}