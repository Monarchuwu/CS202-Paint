#include "DrawingCanvas.h"
#include "Pen.h"

DrawingCanvas::DrawingCanvas(State::Context context,
                             const sf::FloatRect& objectArea,
                             const sf::Vector2f& renderArea)
    : mWindow(*(context.window)),
      mObjectArea(objectArea),
      mRenderTexturePermanently(),
      mRenderTexture(),
      mSprite(),
      mHistoryPanel(this, context, sf::FloatRect(1400, objectArea.top, 190, objectArea.height)),
      mPen(*(context.pen)) {
    mRenderTexturePermanently.create(renderArea.x, renderArea.y);
    mRenderTexturePermanently.clear(sf::Color::Transparent);

    mRenderTexture.create(renderArea.x, renderArea.y);
    clear();
    addTexture(mRenderTexture.getTexture());

    mSprite.setTexture(mRenderTexture.getTexture());
    mSprite.setPosition(mObjectArea.left + mObjectArea.width / 2.f,
                        mObjectArea.top + mObjectArea.height / 2.f);
    adaptRenderArea(renderArea);
}

void DrawingCanvas::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
            sf::FloatRect renderArea = getRenderArea();
			if (renderArea.contains(mousePosition)) {
				mPen.startDrawing(mousePosition - renderArea.getPosition());
			}
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

    mHistoryPanel.handleEvent(event);
}

void DrawingCanvas::update() {
    //mRenderTexture.display();
}

void DrawingCanvas::draw() {
	mRenderTexture.clear(sf::Color::Transparent);
    mRenderTexture.draw(sf::Sprite(mRenderTexturePermanently.getTexture()));

    mHistoryPanel.drawTextures(mRenderTexture);
	mRenderTexture.display();

    mWindow.draw(mSprite);
    if (mPen.isDrawing()) {
		mPen.draw();
	}

    mHistoryPanel.draw();
}

void DrawingCanvas::clear(const sf::Color& color) {
	mRenderTexture.clear(color);
}

void DrawingCanvas::addTexture(const sf::Texture& texture) {
    mHistoryPanel.addTexture(texture);
}

Pen& DrawingCanvas::getPen() {
	return mPen;
}

sf::Vector2f DrawingCanvas::getPositionCanvas() const {
    return mSprite.getPosition() - mSprite.getOrigin();
}

void DrawingCanvas::adaptRenderArea(const sf::Vector2f& renderArea) {
    mSprite.setOrigin(renderArea / 2.f);
}

const sf::FloatRect& DrawingCanvas::getRenderArea() const {
    sf::Vector2f size = (sf::Vector2f)mRenderTexture.getSize();
    return sf::FloatRect(getPositionCanvas(), size);
}