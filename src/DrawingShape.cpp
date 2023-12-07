#include "DrawingShape.h"
#include "ResourceIdentifiers.h"

#include <array>

DrawingShape::DrawingShape(Pen& pen, TextureHolder* textures,
                           const sf::FloatRect& drawingArea)
    : mTop(0), mBottom(0), mLeft(0), mRight(0),
      mRenderTexture(), mRenderTextureRotating(),
      mDrawingStatus(DrawingStatus::WAIT_TO_DRAW),
      mAngle(0),
      isRotating(false),
      mSprite(),
      mPen(pen),
      mSpriteBlackWhite2x2(textures->get(Textures::BlackWhite2x2)) {
    mRenderTexture.create(drawingArea.width, drawingArea.height);
    mRenderTextureRotating.create(drawingArea.width, drawingArea.height);
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
                    sf::FloatRect drawingArea = mSprite.getGlobalBounds();
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
                move(sf::Vector2f(event.mouseMove.x, event.mouseMove.y) - mSprite.getPosition());
            }
            break;
        }

        case DrawingStatus::DRAWED: {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                    sf::FloatRect drawingArea = mSprite.getGlobalBounds();

                    if (checkHoldRotating(mousePosition - mSprite.getPosition())) {
                        isRotating = true;
                        break;
                    }

                    if (drawingArea.contains(mousePosition)) {
                        sf::FloatRect boundingBox = getBoundingBox();
                        if (boundingBox.contains(mousePosition)) {}
                        else {
                            mPen.addTexture(getCanvas());
                            mDrawingStatus = DrawingStatus::WAIT_TO_DRAW;
                            mAngle         = 0;
                            break;
                        }
                    }
                }
            }
            else if (event.type == sf::Event::MouseMoved) {
                if (isRotating) {
					mAngle = calculateAngle(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
				}
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					isRotating = false;
				}
			}
            break;
        }
    }
}

void DrawingShape::draw(sf::RenderTarget& target, sf::RenderStates states) {
	mRenderTexture.display();
    target.draw(mSprite, states);
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
            sf::RenderStates states;
            sf::FloatRect boundingBox = getBoundingBox();
            sf::Vector2f center(boundingBox.left + boundingBox.width / 2,
								boundingBox.top + boundingBox.height / 2);
            states.transform.rotate(mAngle, center);

            draw(window, states);
            drawBoundingBox(window, states);
            drawRotatingHandle(window, states);
            break;
        }
    }
}

void DrawingShape::clear(const sf::Color& color) {
	mRenderTexture.clear(color);
}

const sf::Texture& DrawingShape::getCanvas() {
	sf::FloatRect boundingBox = getBoundingBox();
	sf::Vector2f center(boundingBox.left + boundingBox.width / 2,
	                    boundingBox.top + boundingBox.height / 2);
    center -= mSprite.getPosition();

    sf::RenderStates states;
    states.transform.rotate(mAngle, center);
    mRenderTextureRotating.clear(sf::Color::Transparent);
    mRenderTextureRotating.draw(sf::Sprite(mRenderTexture.getTexture()), states);
    mRenderTextureRotating.display();
	return mRenderTextureRotating.getTexture();
}

void DrawingShape::drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states) {
    mSpriteBlackWhite2x2.setOrigin(.5f, .5f);

    /// draw 4 sides of the bounding box
    // top and bottom
    mSpriteBlackWhite2x2.setTextureRect(sf::IntRect(0, 0, mRight - mLeft + 1, 1));
    // top
    mSpriteBlackWhite2x2.setPosition(mLeft, mTop);
    mSpriteBlackWhite2x2.move(mSprite.getPosition());
    target.draw(mSpriteBlackWhite2x2, states);
    // bottom
    mSpriteBlackWhite2x2.setPosition(mLeft, mBottom);
    mSpriteBlackWhite2x2.move(mSprite.getPosition());
    target.draw(mSpriteBlackWhite2x2, states);
    // left and right
    mSpriteBlackWhite2x2.setTextureRect(sf::IntRect(0, 0, 1, mBottom - mTop + 1));
    // left
    mSpriteBlackWhite2x2.setPosition(mLeft, mTop);
    mSpriteBlackWhite2x2.move(mSprite.getPosition());
    target.draw(mSpriteBlackWhite2x2, states);
    // right
    mSpriteBlackWhite2x2.setPosition(mRight, mTop);
    mSpriteBlackWhite2x2.move(mSprite.getPosition());
    target.draw(mSpriteBlackWhite2x2, states);
}

sf::FloatRect DrawingShape::getBoundingBox() const {
    const sf::Vector2f& position = mSprite.getPosition();
    return sf::FloatRect(mLeft + position.x, mTop + position.y, mRight - mLeft, mBottom - mTop);
}

void DrawingShape::drawRotatingHandle(sf::RenderTarget& target, sf::RenderStates states) {
    float radius = 5;
	sf::CircleShape handle(radius);
    handle.setOrigin(radius, radius);
	handle.setPosition(sf::Vector2f((mLeft + mRight) / 2, mTop - 20));
    handle.move(mSprite.getPosition());
	handle.setFillColor(sf::Color::Red);
	target.draw(handle, states);
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

bool DrawingShape::checkHoldRotating(const sf::Vector2f& mousePosition) const {
    sf::FloatRect boundingBox = getBoundingBox();
    sf::Vector2f center(boundingBox.left + boundingBox.width / 2,
						boundingBox.top + boundingBox.height / 2);
    center -= mSprite.getPosition();

	sf::Vector2f handlePosition((mLeft + mRight) / 2, mTop - 20);
    handlePosition -= center;

    sf::Transformable transformable;
    transformable.rotate(mAngle);
    handlePosition = transformable.getTransform().transformPoint(handlePosition);
    handlePosition += center;

	// Euclidean distance
	float distance = std::sqrt(
	    std::pow(mousePosition.x - handlePosition.x, 2)
	    + std::pow(mousePosition.y - handlePosition.y, 2));
	return distance < 5;
}

float DrawingShape::calculateAngle(sf::Vector2f mousePosition) const {
    sf::FloatRect boundingBox = getBoundingBox();
	mousePosition -= sf::Vector2f(boundingBox.left + boundingBox.width / 2,
	                              boundingBox.top + boundingBox.height / 2);
    return std::atan2f(mousePosition.x, -mousePosition.y) * 180 / acos(-1);
}