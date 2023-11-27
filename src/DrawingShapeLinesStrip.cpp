#include "DrawingShapeLinesStrip.h"

#include <cmath>

DrawingShapeLinesStrip::DrawingShapeLinesStrip(
    const sf::Vector2f& size,
    const sf::Vector2f& startingPosition,
    const Pen::Context& context)
    : DrawingShape(size),
      mCurrentPosition(startingPosition),
      mContext(context) {
}

void DrawingShapeLinesStrip::draw() {
    //states.transform *= getTransform();
    //target.draw(mVertexArray, states);
}

void DrawingShapeLinesStrip::mouseMove(const sf::Vector2f& move) {
    sf::Vector2f newPosition = mCurrentPosition + move;

    // draw a line from the current position to the new position WITHOUT clear
    drawLine(mCurrentPosition, newPosition);

    mCurrentPosition = newPosition;
}

void DrawingShapeLinesStrip::drawLine(const sf::Vector2f& from, const sf::Vector2f& to) {
    sf::Vector2f delta = to - from;
    float length       = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float angle        = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;

    mRectangleShape.setFillColor(mContext.color);
    mCircleShape.setFillColor(mContext.color);

    mRectangleShape.setSize(sf::Vector2f(length, mContext.width));
    mRectangleShape.setRotation(angle);
    mRectangleShape.setPosition(from);
    getRenderTexture()->draw(mRectangleShape);

    mCircleShape.setPosition(from);
    getRenderTexture()->draw(mCircleShape);

    mCircleShape.setPosition(to);
    getRenderTexture()->draw(mCircleShape);
}