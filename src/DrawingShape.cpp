#include "DrawingShape.h"

#include <array>

DrawingShape::DrawingShape(Pen& pen,
                           const sf::FloatRect& renderArea)
    : mRenderTexture(),
      mSprite(),
      mPen(pen) {
    mRenderTexture.create(renderArea.width, renderArea.height);
    clear();

    mSprite.setTexture(mRenderTexture.getTexture());
    mSprite.setPosition(renderArea.getPosition());
}

DrawingShape::~DrawingShape() {}

void DrawingShape::handleEvent(const sf::Event& event) {
    // do nothing
}

void DrawingShape::draw(sf::RenderTarget& target) {
	mRenderTexture.display();
    target.draw(mSprite);
}

void DrawingShape::clear(const sf::Color& color) {
	mRenderTexture.clear(color);
}

const sf::Texture& DrawingShape::getCanvas() const {
	return mRenderTexture.getTexture();
}

void DrawingShape::drawBoundingBox(sf::RenderTarget& target) {
    std::array<sf::RectangleShape, 2> pixel;
    pixel[0].setSize(sf::Vector2f(1, 1));
    pixel[1].setSize(sf::Vector2f(1, 1));
    pixel[0].setFillColor(sf::Color::White);
    pixel[1].setFillColor(sf::Color::Black);

    /// draw 4 sides of the bounding box
    // top
    pixel[0].setPosition(mSprite.getPosition() + sf::Vector2f(mLeft, mTop));
    pixel[1].setPosition(mSprite.getPosition() + sf::Vector2f(mLeft, mTop));
    for (int i = mLeft; i <= mRight; ++i) {
        pixel[0].move(1, 0);
        pixel[1].move(1, 0);
        target.draw(pixel[(i + mTop) & 1]);
	}
    // bottom
    pixel[0].setPosition(mSprite.getPosition() + sf::Vector2f(mLeft, mBottom));
    pixel[1].setPosition(mSprite.getPosition() + sf::Vector2f(mLeft, mBottom));
    for (int i = mLeft; i <= mRight; ++i) {
		pixel[0].move(1, 0);
		pixel[1].move(1, 0);
		target.draw(pixel[(i + mBottom) & 1]);
    }
    // left
    pixel[0].setPosition(mSprite.getPosition() + sf::Vector2f(mLeft, mTop));
    pixel[1].setPosition(mSprite.getPosition() + sf::Vector2f(mLeft, mTop));
    for (int i = mTop + 1; i < mBottom; ++i) {
        pixel[0].move(0, 1);
        pixel[1].move(0, 1);
        target.draw(pixel[(i + mLeft) & 1]);
    }
    // right
    pixel[0].setPosition(mSprite.getPosition() + sf::Vector2f(mRight, mTop));
    pixel[1].setPosition(mSprite.getPosition() + sf::Vector2f(mRight, mTop));
    for (int i = mTop + 1; i < mBottom; ++i) {
		pixel[0].move(0, 1);
		pixel[1].move(0, 1);
		target.draw(pixel[(i + mRight) & 1]);
	}
}

sf::FloatRect DrawingShape::getBoundingBox() const {
    const sf::Vector2f& position = mSprite.getPosition();
    return sf::FloatRect(mLeft + position.x, mTop + position.y, mRight - mLeft, mBottom - mTop);
}

void DrawingShape::updateBoundingBox(const sf::Vector2f& position) {
    if (mLeft > position.x) {
        mLeft = position.x;
    }
    if (mRight < position.x) {
        mRight = position.x;
    }
    if (mTop > position.y) {
        mTop = position.y;
    }
    if (mBottom < position.y) {
        mBottom = position.y;
    }
}

void DrawingShape::resetBoundingBox(const sf::Vector2f& position) {
	mLeft = mRight = position.x;
	mTop = mBottom = position.y;
}