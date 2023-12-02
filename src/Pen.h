#pragma once
#include <SFML/Graphics.hpp>

class DrawingCanvas;
class DrawingShape;

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

    bool isDrawing() const;
    void draw();
    void startDrawing(const sf::Vector2f& position);
    void stopDrawing();
    void move(const sf::Vector2f& position);

    void setWidth(int width);
    int getWidth() const;

    void setColor(const sf::Color& color);
    const sf::Color& getColor() const;

    void setShape();

private:
    DrawingCanvas* mCanvas;
    Context mContext;
    DrawingShape* mDrawingShape;

    bool mIsDrawing;
    sf::Vector2f mLastPosition;
    sf::RectangleShape mRectangleShape;
    sf::CircleShape mCircleShape;
};