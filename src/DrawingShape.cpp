#include "DrawingShape.h"

DrawingShape::DrawingShape(sf::RenderWindow& window, Pen& pen,
                           const sf::FloatRect& renderArea)
    : mWindow(window),
      mRenderTexture(),
      mSprite(),
      mPen(pen) {
    mRenderTexture.create(renderArea.width, renderArea.height);
    clear();

    mSprite.setTexture(mRenderTexture.getTexture());
    mSprite.setPosition(renderArea.getPosition());
}

DrawingShape::~DrawingShape() {}

void DrawingShape::draw() {
	mRenderTexture.display();
	mWindow.draw(mSprite);
}

void DrawingShape::clear(const sf::Color& color) {
	mRenderTexture.clear(color);
}

const sf::Texture& DrawingShape::getCanvas() const {
	return mRenderTexture.getTexture();
}