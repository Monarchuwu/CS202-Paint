#pragma once
#include <SFML/Graphics.hpp>

// This is a temporary canvas
class DrawingShape {
protected:
    DrawingShape(const sf::Vector2f& size);

public:
    virtual ~DrawingShape();

    virtual void draw()                              = 0;
    virtual void mouseMove(const sf::Vector2f& move) = 0;

    void clear(const sf::Color& color = sf::Color::Transparent);

protected:
    sf::RenderTexture* getRenderTexture();

private:
    sf::RenderTexture mRenderTexture;
    sf::Sprite mSprite;
};