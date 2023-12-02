#include "DrawingCanvas.h"

DrawingCanvas::DrawingCanvas(sf::RenderWindow& window, Pen& pen,
                             const sf::FloatRect& objectArea,
                             const sf::Vector2f& renderArea)
    : mWindow(window),
      mObjectArea(objectArea),
      mRenderTexture(),
      mSprite(),
      mPen(pen) {
    mRenderTexture.create(renderArea.x, renderArea.y);
    clear();

    mSprite.setTexture(mRenderTexture.getTexture());
    mSprite.setPosition(mObjectArea.left + mObjectArea.width / 2.f,
                        mObjectArea.top + mObjectArea.height / 2.f);
    adaptRenderArea(renderArea);
}

void DrawingCanvas::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            mPen.startDrawing(sf::Vector2f(event.mouseButton.x, event.mouseButton.y) - getPositionCanvas());
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            mPen.stopDrawing();
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        mPen.move(sf::Vector2f(event.mouseMove.x, event.mouseMove.y) - getPositionCanvas());
    }
	else if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			clear();
		}
	}
}

void DrawingCanvas::update() {
    //mRenderTexture.display();
}

void DrawingCanvas::draw() {
	mRenderTexture.display();
	mWindow.draw(mSprite);
    if (mPen.isDrawing()) {
		mPen.draw();
	}
}

void DrawingCanvas::clear(const sf::Color& color) {
	mRenderTexture.clear(color);
}

Pen& DrawingCanvas::getPen() {
	return mPen;
}

sf::Vector2f DrawingCanvas::getPositionCanvas() const {
    return mSprite.getPosition() - (sf::Vector2f)mRenderTexture.getSize() / 2.f;
}

void DrawingCanvas::adaptRenderArea(const sf::Vector2f& renderArea) {
    mSprite.setOrigin(renderArea / 2.f);
}

const sf::FloatRect& DrawingCanvas::getRenderArea() const {
    sf::Vector2f size = (sf::Vector2f)mRenderTexture.getSize();
    return sf::FloatRect(mSprite.getPosition() - mSprite.getOrigin(), size);
}