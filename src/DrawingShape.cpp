#include "DrawingShape.h"
#include "ResourceIdentifiers.h"

#include <array>

DrawingShape::DrawingShape(Pen& pen, TextureHolder* textures,
                           const sf::FloatRect& drawingArea)
    : mTop(0), mBottom(0), mLeft(0), mRight(0),
      mRenderTexture(),
      mDrawingStatus(DrawingStatus::WAIT_TO_DRAW),
      mSprite(),
      mPen(pen),
      mSpriteBlackWhite2x2(textures->get(Textures::BlackWhite2x2)) {
    mRenderTexture.create(drawingArea.width, drawingArea.height);
    clear();

    mSprite.setTexture(mRenderTexture.getTexture());
    mSprite.setPosition(drawingArea.getPosition());
}

DrawingShape::~DrawingShape() {}

DrawingShape::DrawingStatus DrawingShape::getDrawingStatus() const {
    return mDrawingStatus;
}

void DrawingShape::handleEvent(const sf::Event& event) {
    switch (mDrawingStatus) {
        case DrawingStatus::WAIT_TO_DRAW: {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                    sf::FloatRect drawingArea = mPen.getDrawingArea();
                    if (drawingArea.contains(mousePosition)) {
                        startDrawing(mousePosition - drawingArea.getPosition());
                        mDrawingStatus = DrawingStatus::DRAWING;
                    }
                }
            }
            break;
        }

        case DrawingStatus::DRAWING: {
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    stopDrawing();
                    mDrawingStatus = DrawingStatus::DRAWED;
                }
            }
            else if (event.type == sf::Event::MouseMoved) {
                move(sf::Vector2f(event.mouseMove.x, event.mouseMove.y) - mPen.getDrawingArea().getPosition());
            }
            break;
        }

        case DrawingStatus::DRAWED: {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                    sf::FloatRect drawingArea = mPen.getDrawingArea();
                    if (drawingArea.contains(mousePosition)) {
                        sf::FloatRect boundingBox = getBoundingBox();
                        if (!boundingBox.contains(mousePosition)) {
                            mPen.addTexture(getCanvas());
                            mDrawingStatus = DrawingStatus::WAIT_TO_DRAW;
                            break;
                        }
                    }
                }
            }
            break;
        }
    }
}

void DrawingShape::draw(sf::RenderTarget& target) {
	mRenderTexture.display();
    target.draw(mSprite);
}

void DrawingShape::drawToWindow(sf::RenderWindow& window) {
    switch (mDrawingStatus) {
        case DrawingStatus::WAIT_TO_DRAW: {
            break;
        }

        case DrawingStatus::DRAWING: {
            draw(window);
            break;
        }

        case DrawingStatus::DRAWED: {
            draw(window);
            drawBoundingBox(window);
            break;
        }
    }
}

void DrawingShape::clear(const sf::Color& color) {
	mRenderTexture.clear(color);
}

const sf::Texture& DrawingShape::getCanvas() const {
	return mRenderTexture.getTexture();
}

void DrawingShape::drawBoundingBox(sf::RenderTarget& target) {
    mSpriteBlackWhite2x2.setOrigin(.5f, .5f);

    /// draw 4 sides of the bounding box
    // top and bottom
    mSpriteBlackWhite2x2.setTextureRect(sf::IntRect(0, 0, mRight - mLeft + 1, 1));
    // top
    mSpriteBlackWhite2x2.setPosition(mLeft, mTop);
    mSpriteBlackWhite2x2.move(mSprite.getPosition());
    target.draw(mSpriteBlackWhite2x2);
    // bottom
    mSpriteBlackWhite2x2.setPosition(mLeft, mBottom);
    mSpriteBlackWhite2x2.move(mSprite.getPosition());
    target.draw(mSpriteBlackWhite2x2);
    // left and right
    mSpriteBlackWhite2x2.setTextureRect(sf::IntRect(0, 0, 1, mBottom - mTop + 1));
    // left
    mSpriteBlackWhite2x2.setPosition(mLeft, mTop);
    mSpriteBlackWhite2x2.move(mSprite.getPosition());
    target.draw(mSpriteBlackWhite2x2);
    // right
    mSpriteBlackWhite2x2.setPosition(mRight, mTop);
    mSpriteBlackWhite2x2.move(mSprite.getPosition());
    target.draw(mSpriteBlackWhite2x2);
}

sf::FloatRect DrawingShape::getBoundingBox() const {
    const sf::Vector2f& position = mSprite.getPosition();
    return sf::FloatRect(mLeft + position.x, mTop + position.y, mRight - mLeft, mBottom - mTop);
}

void DrawingShape::drawBoundingBox() {
    const sf::Vector2f& position = mSprite.getPosition();
    mLeft -= position.x;
    mRight -= position.x;
    mTop -= position.y;
    mBottom -= position.y;
	drawBoundingBox(mRenderTexture);
    mLeft += position.x;
	mRight += position.x;
	mTop += position.y;
	mBottom += position.y;
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