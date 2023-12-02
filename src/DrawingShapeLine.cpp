#include "DrawingShapeLine.h"

#include <cmath>

DrawingShapeLine::DrawingShapeLine(Pen& pen,
                                   const sf::FloatRect& renderArea)
    : DrawingShape(pen, renderArea),
      mPen(pen) {
}

void DrawingShapeLine::startDrawing(const sf::Vector2f& position) {
    mStartPosition = position;
    clear();
}

void DrawingShapeLine::stopDrawing() {
    // nothing to do
}

void DrawingShapeLine::move(const sf::Vector2f& position) {
    // clear the render texture to draw a new shape
    clear();

    drawLine(mStartPosition, position);
}

void DrawingShapeLine::drawLine(const sf::Vector2f& from, const sf::Vector2f& to) {
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