#include "Pen.h"
#include "DrawingCanvas.h"

Pen::Context::Context(const sf::Color& color, int width)
	: color(color),
	  width(width) {
}

Pen::Pen(DrawingCanvas& canvas,
	     const Context& context)
	: mCanvas(&canvas),
	  mContext(context),
	  mDrawingShape(nullptr),
	  mIsDrawing(false) {
}

void Pen::startDrawing(const sf::Vector2f& position) {
	mIsDrawing = true;
	mLastPosition = position;
}

void Pen::stopDrawing() {
	mIsDrawing = false;
}

void Pen::move(const sf::Vector2f& position) {
	if (mIsDrawing) {
		drawLine(mLastPosition, position);
		mLastPosition = position;
	}
}

void Pen::drawLine(const sf::Vector2f& from, const sf::Vector2f& to) {
	sf::Vector2f delta = to - from;
	float length       = std::sqrt(delta.x * delta.x + delta.y * delta.y);
	float angle        = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;

	mRectangleShape.setFillColor(mContext.color);
	mCircleShape.setFillColor(mContext.color);

	mRectangleShape.setOrigin(0, mContext.width / 2.f);
	mRectangleShape.setSize(sf::Vector2f(length, mContext.width));
	mRectangleShape.setRotation(angle);
	mRectangleShape.setPosition(from);
	(mCanvas->mRenderTexture).draw(mRectangleShape);

	mCircleShape.setOrigin(mContext.width / 2.f, mContext.width / 2.f);
	mCircleShape.setRadius(mContext.width / 2.f);
	mCircleShape.setPosition(from);
	(mCanvas->mRenderTexture).draw(mCircleShape);

	mCircleShape.setPosition(to);
	(mCanvas->mRenderTexture).draw(mCircleShape);
}