#include "DrawingShape.h"

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