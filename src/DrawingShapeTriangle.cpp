#include "DrawingShapeTriangle.h"

#include <cmath>

DrawingShapeTriangle::DrawingShapeTriangle(Pen& pen, TextureHolder* textures,
                                           const sf::FloatRect& renderArea)
    : DrawingShapeLineStrip(pen, textures, renderArea),
      mStartPosition(),
      mCurrentPosition() {
}

void DrawingShapeTriangle::startDrawing(const sf::Vector2f& position) {
    resetBoundingBox(position);
    mStartPosition = position;
    clear();
}

void DrawingShapeTriangle::stopDrawing() {
    updateBoundingBox(mCurrentPosition);
}

void DrawingShapeTriangle::move(const sf::Vector2f& position) {
    // clear the render texture to draw a new shape
    clear();

    int minX = std::min(mStartPosition.x, position.x);
    int minY = std::min(mStartPosition.y, position.y);
    int maxX = std::max(mStartPosition.x, position.x);
    int maxY = std::max(mStartPosition.y, position.y);
    drawTriangle(minX, minY, maxX, maxY);

    mCurrentPosition = position;
}

void DrawingShapeTriangle::drawTriangle(int minX, int minY, int maxX, int maxY) {
    std::vector<sf::Vector2f> points(4);

    points[0] = sf::Vector2f(minX, maxY);
    points[1] = sf::Vector2f(maxX, maxY);
    points[2] = sf::Vector2f((minX + maxX) / 2, minY);
    points[3] = points[0];

    drawLineStrip(points);
}