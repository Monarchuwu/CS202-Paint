#include "DrawingShapeRightTriangle.h"

#include <cmath>

DrawingShapeRightTriangle::DrawingShapeRightTriangle(Pen& pen,
                                                     const sf::FloatRect& renderArea)
    : DrawingShape(pen, renderArea),
      mPen(pen) {
}

void DrawingShapeRightTriangle::startDrawing(const sf::Vector2f& position) {
    mStartPosition = position;
    clear();
}

void DrawingShapeRightTriangle::stopDrawing() {
    // nothing to do
}

void DrawingShapeRightTriangle::move(const sf::Vector2f& position) {
    // clear the render texture to draw a new shape
    clear();

    int minX = std::min(mStartPosition.x, position.x);
    int minY = std::min(mStartPosition.y, position.y);
    int maxX = std::max(mStartPosition.x, position.x);
    int maxY = std::max(mStartPosition.y, position.y);
    drawTriangle(minX, minY, maxX, maxY);
}

void DrawingShapeRightTriangle::drawTriangle(int minX, int minY, int maxX, int maxY) {
    int penWidth              = mPen.getWidth();
    const sf::Color& penColor = mPen.getColor();

    /// draw left and bottom sides of the triangle
    mRectangleShape.setFillColor(penColor);
    // bottom
    mRectangleShape.setSize(sf::Vector2f(maxX - minX, penWidth));
    mRectangleShape.setOrigin(0, penWidth / 2.f);
    mRectangleShape.setPosition(minX, maxY);
    mRenderTexture.draw(mRectangleShape);
    // left
    mRectangleShape.setSize(sf::Vector2f(penWidth, maxY - minY));
    mRectangleShape.setOrigin(penWidth / 2.f, 0);
    mRectangleShape.setPosition(minX, minY);
    mRenderTexture.draw(mRectangleShape);
    /// draw (top, left) to (bottom, right) side of the triangle
    drawLine(sf::Vector2f(minX, minY), sf::Vector2f(maxX, maxY));

    /// draw the three corners of the triangle
    mCircleShape.setFillColor(penColor);
    mCircleShape.setOrigin(penWidth / 2.f, penWidth / 2.f);
    mCircleShape.setRadius(penWidth / 2.f);
    // top left
    mCircleShape.setPosition(minX, minY);
    mRenderTexture.draw(mCircleShape);
    // bottom left
    mCircleShape.setPosition(minX, maxY);
    mRenderTexture.draw(mCircleShape);
    // bottom right
    mCircleShape.setPosition(maxX, maxY);
    mRenderTexture.draw(mCircleShape);
}

void DrawingShapeRightTriangle::drawLine(const sf::Vector2f& from, const sf::Vector2f& to) {
    sf::Vector2f delta = to - from;
    float length       = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float angle        = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;

    int penWidth              = mPen.getWidth();
    const sf::Color& penColor = mPen.getColor();

    mRectangleShapeLine.setFillColor(penColor);
    mRectangleShapeLine.setOrigin(0, penWidth / 2.f);

    mRectangleShapeLine.setSize(sf::Vector2f(length, penWidth));
    mRectangleShapeLine.setRotation(angle);
    mRectangleShapeLine.setPosition(from);
    mRenderTexture.draw(mRectangleShapeLine);
}