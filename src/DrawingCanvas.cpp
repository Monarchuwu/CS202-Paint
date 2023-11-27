#include "DrawingCanvas.h"
#include <iostream>
#include <cmath>

DrawingCanvas::DrawingCanvas(const sf::FloatRect& rect)
    : mCanvasRect(rect),
	  mCanvasTexture(),
	  mChanged(false),
	  mIsDrawing(false),
	  mLastMousePosition(0, 0),
      mBrushSize() {
    mCanvasTexture.create(mCanvasRect.width, mCanvasRect.height);
    setBrushSize(4.f);
	setBrushColor(sf::Color::Black);
    display();
}

bool DrawingCanvas::eventKeyPressed(const sf::Event::KeyEvent& key) {
    if (key.code == sf::Keyboard::Space) {
        clear();
        return true;
    }
    return false;
}
bool DrawingCanvas::eventMouseButtonPressed(const sf::Event::MouseButtonEvent& mouse) {
	if (!mIsDrawing) {
        if (mouse.button == sf::Mouse::Left) {
            mIsDrawing         = true;
            mLastMousePosition = sf::Vector2f(mouse.x, mouse.y);
            mLastMousePosition -= mCanvasRect.getPosition();
            return true;
        }
	}
	return false;
}
bool DrawingCanvas::eventMouseButtonReleased(const sf::Event::MouseButtonEvent& mouse) {
	if (mIsDrawing) {
        if (mouse.button == sf::Mouse::Left) {
            mIsDrawing = false;
            return true;
        }
	}
	return false;
}
bool DrawingCanvas::eventMouseMoved(const sf::Event::MouseMoveEvent& mouse) {
	if (mIsDrawing) {
        sf::Vector2f mousePosition(mouse.x, mouse.y);
        mousePosition -= mCanvasRect.getPosition();

        drawLine(mLastMousePosition, mousePosition);

        mLastMousePosition = mousePosition;
        return true;
	}
	return false;
}

void DrawingCanvas::setBrushSize(float size) {
	mBrushSize = size;
	mRectangleShape.setOrigin(0, mBrushSize / 2.f);
	mCircleShape.setRadius(mBrushSize / 2.f);
	mCircleShape.setOrigin(mBrushSize / 2.f, mBrushSize / 2.f);
}
void DrawingCanvas::setBrushColor(const sf::Color& color) {
	mBrushColor = color;
	mRectangleShape.setFillColor(sf::Color::Black);
	mCircleShape.setFillColor(sf::Color::Black);
}
float DrawingCanvas::getBrushSize() const {
	return mBrushSize;
}
const sf::Color& DrawingCanvas::getBrushColor() const {
	return mBrushColor;
}

sf::Sprite DrawingCanvas::getSprite() {
    if (mChanged) display();
	sf::Sprite sprite;
	sprite.setTexture(mCanvasTexture.getTexture());
	sprite.setPosition(mCanvasRect.getPosition());
	return sprite;
}

void DrawingCanvas::clear(const sf::Color& color) {
	mCanvasTexture.clear(color);
}

void DrawingCanvas::display() {
	mCanvasTexture.display();
}

void DrawingCanvas::drawLine(const sf::Vector2f& from, const sf::Vector2f& to) {
	sf::Vector2f delta = to - from;
	float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
	float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;

	mRectangleShape.setSize(sf::Vector2f(length, mBrushSize));
	mRectangleShape.setRotation(angle);
	mRectangleShape.setPosition(from);
	mCanvasTexture.draw(mRectangleShape);

	mCircleShape.setPosition(from);
	mCanvasTexture.draw(mCircleShape);

	mCircleShape.setPosition(to);
	mCanvasTexture.draw(mCircleShape);

	mChanged = true;
}