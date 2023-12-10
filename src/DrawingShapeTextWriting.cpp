#include "DrawingShapeTextWriting.h"

DrawingShapeTextWriting::DrawingShapeTextWriting(Pen& pen,
                                                 TextureHolder* textures,
                                                 FontHolder* fonts,
                                                 const sf::FloatRect& renderArea)
    : DrawingShape(pen, textures, renderArea),
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
    clear();
    resetBoundingBox(mStartPosition);
    updateBoundingBox(mCurrentPosition);
}

void DrawingShapeTextWriting::move(const sf::Vector2f& position) {
    // clear and draw the bounding box (text writing behavior)
    clear();
    resetBoundingBox(mStartPosition);
    updateBoundingBox(position);
    drawBoundingBox();

    mCurrentPosition = position;
}

void DrawingShapeTextWriting::handleEvent(const sf::Event& event, const sf::Vector2f& drawingCenter, unsigned int zoomFactor) {
    DrawingShape::handleEvent(event, drawingCenter, zoomFactor);

    if (getDrawingStatus() != DrawingStatus::DRAWED) return;
    if (event.type == sf::Event::TextEntered) {
		if (event.text.unicode == '\b') {
			if (!mString.empty()) {
				mString.pop_back();
			    mText.setString(mString);
			}
		} else {
			mString += char(event.text.unicode);
     	    mText.setString(mString);
		}

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