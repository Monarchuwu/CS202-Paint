// https://www.sfml-dev.org/documentation/2.6.0/classsf_1_1RenderTexture.php
#pragma once
#include <SFML/Graphics.hpp>
#include "EventHandler.h"

class DrawingCanvas : public EventHandler {
private:
    sf::FloatRect mCanvasRect;
    sf::RenderTexture mCanvasTexture;

    bool mChanged;
    bool mIsDrawing;
    sf::Vector2f mLastMousePosition;

    float mBrushSize;
    sf::Color mBrushColor;
    sf::CircleShape mCircleShape;
    sf::RectangleShape mRectangleShape;

public:
    DrawingCanvas(const sf::FloatRect& rect);

    /* handle event */
    bool eventKeyPressed(const sf::Event::KeyEvent& key) override;
    bool eventMouseButtonPressed(const sf::Event::MouseButtonEvent& mouse) override;
    bool eventMouseButtonReleased(const sf::Event::MouseButtonEvent& mouse) override;
    bool eventMouseMoved(const sf::Event::MouseMoveEvent& mouse) override;

    void setBrushSize(float size);
    void setBrushColor(const sf::Color& color);
    float getBrushSize() const;
    const sf::Color& getBrushColor() const;

    sf::Sprite getSprite();
    void clear(const sf::Color& color = sf::Color(255, 255, 255, 255));

private:
    void display();
    void drawLine(const sf::Vector2f& from, const sf::Vector2f& to);
};