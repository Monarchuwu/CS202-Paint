#include "DrawingShape.h"

DrawingShape::DrawingShape(const sf::Vector2f& size)
	: mRenderTexture() {
    mRenderTexture.create(size.x, size.y);

	mSprite.setTexture(mRenderTexture.getTexture());
}

DrawingShape::~DrawingShape() {}

void DrawingShape::clear(const sf::Color& color) {
	mRenderTexture.clear(color);
}

sf::RenderTexture* DrawingShape::getRenderTexture() {
	return &mRenderTexture;
}