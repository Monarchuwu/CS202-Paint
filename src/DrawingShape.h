#pragma once
#include "Pen.h"

#include <SFML/Graphics.hpp>

// This is a temporary canvas
class DrawingShape {
protected:
    DrawingShape(Pen& pen,
                 const sf::FloatRect& renderArea);

public:
    virtual ~DrawingShape();

    virtual void startDrawing(const sf::Vector2f& position) = 0;
    virtual void stopDrawing()                              = 0;
    virtual void move(const sf::Vector2f& position)         = 0;


    virtual void draw(sf::RenderTarget& target);
    void clear(const sf::Color& color = sf::Color::Transparent);

    const sf::Texture& getCanvas() const;

protected:
    sf::RenderTexture mRenderTexture;

private:
    sf::Sprite mSprite;

    Pen& mPen;
};