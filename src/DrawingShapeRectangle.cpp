#include "DrawingShapeRectangle.h"

#include <cmath>

DrawingShapeRectangle::DrawingShapeRectangle(Pen& pen, TextureHolder* textures,
                                             const sf::FloatRect& renderArea)
    : DrawingShapeConvex(pen, textures, renderArea, 4),
      mStartPosition(),
      mCurrentPosition() {
}

void DrawingShapeRectangle::startDrawing(const sf::Vector2f& position) {
    resetBoundingBox(position);
    mStartPosition = mCurrentPosition = position;
    clear();
}

void DrawingShapeRectangle::stopDrawing() {
    updateBoundingBox(mCurrentPosition);
}

void DrawingShapeRectangle::move(const sf::Vector2f& position) {
    // clear the render texture to draw a new shape
    clear();

    int minX = std::min(mStartPosition.x, position.x);
    int minY = std::min(mStartPosition.y, position.y);
    int maxX = std::max(mStartPosition.x, position.x);
    int maxY = std::max(mStartPosition.y, position.y);
    drawRectangle(minX, minY, maxX, maxY);

    mCurrentPosition = position;
}

void DrawingShapeRectangle::drawRectangle(int minX, int minY, int maxX, int maxY) {
    std::vector<sf::Vector2f> points(4);

    points[0] = sf::Vector2f(minX, minY);
    points[1] = sf::Vector2f(maxX, minY);
    points[2] = sf::Vector2f(maxX, maxY);
    points[3] = sf::Vector2f(minX, maxY);

    drawConvex(points);
}
