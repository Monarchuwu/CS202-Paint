#pragma once
#include "DrawingShape.h"

#include <SFML/Graphics.hpp>

class DrawingCanvas;

class Pen {
public:
    struct Context {
        Context(const sf::Color& color, int width);

        sf::Color color;
		int width;
    };

public:
    Pen(const Context& context);

    void setCanvas(DrawingCanvas& canvas);

    void startDrawing(const sf::Vector2f& position);
    void stopDrawing();
    void move(const sf::Vector2f& position);

    void setWidth(int width);
    int getWidth() const;

private:
    void drawLine(const sf::Vector2f& from, const sf::Vector2f& to);

private:
    DrawingCanvas* mCanvas;
    Context mContext;
    DrawingShape* mDrawingShape;

    bool mIsDrawing;
    sf::Vector2f mLastPosition;
    sf::RectangleShape mRectangleShape;
    sf::CircleShape mCircleShape;
};