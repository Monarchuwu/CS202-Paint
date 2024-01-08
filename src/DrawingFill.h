#pragma once
#include "DrawingShape.h"
#include "Pen.h"

class DrawingFill : public DrawingShape {
public:
    DrawingFill(Pen& pen, TextureHolder* textures,
                const sf::FloatRect& renderArea);

    virtual void startDrawing(const sf::Vector2f& position);
    virtual void stopDrawing();
    virtual void move(const sf::Vector2f& position);

private:
    Pen& mPen;
};