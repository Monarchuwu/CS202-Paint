#include "DrawingShapeLineStrip.h"

DrawingShapeLineStrip::DrawingShapeLineStrip(Pen& pen, TextureHolder* textures,
                                             const sf::FloatRect& renderArea)
    : DrawingShape(pen, textures, renderArea),
      mPen(pen),
      mRectangleShape(),
      mCircleShape() {
}

void DrawingShapeLineStrip::drawLineStrip(const std::vector<sf::Vector2f>& vertices) {
		int penWidth = mPen.getWidth();
	const sf::Color& penColor = mPen.getColor();

	mRectangleShape.setFillColor(penColor);
	mRectangleShape.setOrigin(0, penWidth / 2.f);

	mCircleShape.setFillColor(penColor);
	mCircleShape.setOrigin(penWidth / 2.f, penWidth / 2.f);
	mCircleShape.setRadius(penWidth / 2.f);

	for (int i = 1; i < vertices.size(); ++i) {
		sf::Vector2f from = vertices[i - 1];
		sf::Vector2f to = vertices[i];

		sf::Vector2f delta = to - from;
		float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
		float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;

		mRectangleShape.setSize(sf::Vector2f(length, penWidth));
		mRectangleShape.setRotation(angle);
		mRectangleShape.setPosition(from);
		mRenderTexture.draw(mRectangleShape);

		if (i > 1) {
			mCircleShape.setPosition(from);
			mRenderTexture.draw(mCircleShape);
		}
	}

	if (vertices[0] == vertices.back()) {
		mCircleShape.setPosition(vertices[0]);
		mRenderTexture.draw(mCircleShape);
	}
}