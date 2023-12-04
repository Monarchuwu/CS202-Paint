#include "DrawingShapeTextWriting.h"

DrawingShapeTextWriting::DrawingShapeTextWriting(Pen& pen, FontHolder* fonts,
                                                 const sf::FloatRect& renderArea)
    : DrawingShape(pen, renderArea),
      mPen(pen),
      mStartPosition(),
      mCurrentPosition(),
      mString(""),
	  mText(),
      mDrawingPosition(renderArea.getPosition()) {
    mText.setFont(fonts->get(Fonts::Sansation));
}

void DrawingShapeTextWriting::startDrawing(const sf::Vector2f& position) {
    resetBoundingBox(position);
    mStartPosition = mCurrentPosition = position;
    mString.clear();
    clear();
}

void DrawingShapeTextWriting::stopDrawing() {
    updateBoundingBox(mCurrentPosition);
}

void DrawingShapeTextWriting::move(const sf::Vector2f& position) {
    // nothing to draw before stopDrawing
    // so we don't need to clear the render texture
    mCurrentPosition = position;
}

void DrawingShapeTextWriting::handleEvent(const sf::Event& event) {
if (event.type == sf::Event::TextEntered) {
		if (event.text.unicode == '\b') {
			if (!mString.empty()) {
				mString.pop_back();
			}
		} else {
			mString += char(event.text.unicode);
		}
		mText.setString(mString);

        drawText(getBoundingBox());
	}
}

void DrawingShapeTextWriting::drawText(sf::FloatRect textBox) {
	clear();

    mText.setPosition(textBox.left, textBox.top);
	mText.move(-mDrawingPosition);
    mText.setCharacterSize(mPen.getWidth() * 5);
	mText.setFillColor(mPen.getColor());
    mRenderTexture.draw(mText);
}