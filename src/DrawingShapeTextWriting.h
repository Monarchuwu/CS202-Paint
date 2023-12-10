#pragma once
#include "DrawingShape.h"
#include "Pen.h"
#include "ResourceHolder.h"

#include <vector>

class DrawingShapeTextWriting : public DrawingShape {
public:
    DrawingShapeTextWriting(Pen& pen,
                            TextureHolder* textures,
                            FontHolder* fonts,
                            const sf::FloatRect& renderArea);

    virtual void startDrawing(const sf::Vector2f& position);
    virtual void stopDrawing();
    virtual void move(const sf::Vector2f& position);

    // I suppose that this function is called in DRAWED phase
    virtual void handleEvent(const sf::Event& event, const sf::Vector2f& drawingCenter, unsigned int zoomFactor);

private:
    void drawText(sf::FloatRect textBox);

private:
    Pen& mPen;
    sf::Vector2f mStartPosition;
    sf::Vector2f mCurrentPosition;

    std::string mString;
    sf::Text mText;
    sf::Vector2f mDrawingPosition;
};