#include "DrawingShapeTriangle.h"

#include <cmath>

DrawingShapeTriangle::DrawingShapeTriangle(Pen& pen,
                                                     const sf::FloatRect& renderArea)
    : DrawingShape(pen, renderArea),
      mPen(pen),
      mStartPosition(),
      mCurrentPosition(),
      mRectangleShape(),
      mCircleShape() {
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
    sf::Vector2f point[3];
    point[0] = sf::Vector2f(minX, maxY);
    point[1] = sf::Vector2f(maxX, maxY);
    point[2] = sf::Vector2f((minX + maxX) / 2, minY);

    drawLine(point[0], point[1]);
    drawLine(point[1], point[2]);
    drawLine(point[2], point[0]);
}

void DrawingShapeTriangle::drawLine(const sf::Vector2f& from, const sf::Vector2f& to) {
    sf::Vector2f delta = to - from;
    float length       = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float angle        = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;

    int penWidth              = mPen.getWidth();
    const sf::Color& penColor = mPen.getColor();

    mRectangleShape.setFillColor(penColor);
    mRectangleShape.setOrigin(0, penWidth / 2.f);

    mCircleShape.setFillColor(penColor);
    mCircleShape.setOrigin(penWidth / 2.f, penWidth / 2.f);
    mCircleShape.setRadius(penWidth / 2.f);

    mRectangleShape.setSize(sf::Vector2f(length, penWidth));
    mRectangleShape.setRotation(angle);
    mRectangleShape.setPosition(from);
    mRenderTexture.draw(mRectangleShape);

    mCircleShape.setPosition(from);
    mRenderTexture.draw(mCircleShape);

    mCircleShape.setPosition(to);
    mRenderTexture.draw(mCircleShape);
}