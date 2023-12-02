#include "DrawingShapeRectangle.h"

#include <cmath>

DrawingShapeRectangle::DrawingShapeRectangle(Pen& pen,
                                             const sf::FloatRect& renderArea)
    : DrawingShape(pen, renderArea),
      mPen(pen) {
}

void DrawingShapeRectangle::startDrawing(const sf::Vector2f& position) {
    mStartPosition = position;
    clear();
}

void DrawingShapeRectangle::stopDrawing() {
    // nothing to do
}

void DrawingShapeRectangle::move(const sf::Vector2f& position) {
    // clear the render texture to draw a new shape
    clear();

    int minX = std::min(mStartPosition.x, position.x);
    int minY = std::min(mStartPosition.y, position.y);
    int maxX = std::max(mStartPosition.x, position.x);
    int maxY = std::max(mStartPosition.y, position.y);
    drawRectangle(minX, minY, maxX, maxY);
}

void DrawingShapeRectangle::drawRectangle(int minX, int minY, int maxX, int maxY) {
    int penWidth              = mPen.getWidth();
    const sf::Color& penColor = mPen.getColor();

    /// draw the four sides of the rectangle
    mRectangleShape.setFillColor(penColor);
    // top and bottom
    mRectangleShape.setSize(sf::Vector2f(maxX - minX, penWidth));
    mRectangleShape.setOrigin(0, penWidth / 2.f);
    // top
    mRectangleShape.setPosition(minX, minY);
    mRenderTexture.draw(mRectangleShape);
    // bottom
    mRectangleShape.setPosition(minX, maxY);
    mRenderTexture.draw(mRectangleShape);
    // left and right
    mRectangleShape.setSize(sf::Vector2f(penWidth, maxY - minY));
    mRectangleShape.setOrigin(penWidth / 2.f, 0);
    // left
    mRectangleShape.setPosition(minX, minY);
    mRenderTexture.draw(mRectangleShape);
    // right
    mRectangleShape.setPosition(maxX, minY);
    mRenderTexture.draw(mRectangleShape);

    /// draw the four corners of the rectangle
    mCircleShape.setFillColor(penColor);
    mCircleShape.setOrigin(penWidth / 2.f, penWidth / 2.f);
    mCircleShape.setRadius(penWidth / 2.f);
    // top left
    mCircleShape.setPosition(minX, minY);
    mRenderTexture.draw(mCircleShape);
    // top right
    mCircleShape.setPosition(maxX, minY);
    mRenderTexture.draw(mCircleShape);
    // bottom left
    mCircleShape.setPosition(minX, maxY);
    mRenderTexture.draw(mCircleShape);
    // bottom right
    mCircleShape.setPosition(maxX, maxY);
    mRenderTexture.draw(mCircleShape);
}
