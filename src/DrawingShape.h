#pragma once
#include "Pen.h"
#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>

// This is a temporary canvas
class DrawingShape {
public:
    enum class DrawingStatus {
        WAIT_TO_DRAW,
        DRAWING,
        DRAWED
    };

protected:
    DrawingShape(Pen& pen, TextureHolder* textures,
                 const sf::FloatRect& renderArea);

public:
    virtual ~DrawingShape();

    virtual void startDrawing(const sf::Vector2f& position) = 0;
    virtual void stopDrawing()                              = 0;
    virtual void move(const sf::Vector2f& position)         = 0;
    DrawingStatus getDrawingStatus() const;

    virtual void handleEvent(const sf::Event& event);
    virtual void draw(sf::RenderTarget& target);
    virtual void drawToWindow(sf::RenderWindow& window);
    void clear(const sf::Color& color = sf::Color::Transparent);

    const sf::Texture& getCanvas() const;

    // this method will only be called after stopDrawing() called
    void drawBoundingBox(sf::RenderTarget& target);
    // this method will only be called after stopDrawing() called
    sf::FloatRect getBoundingBox() const;

protected:
    // draw bounding box to mRenderTexture
    void drawBoundingBox();
    void updateBoundingBox(const sf::Vector2f& position);
    void resetBoundingBox(const sf::Vector2f& position);

protected:
    // bounding box
    int mTop, mBottom, mLeft, mRight;

    sf::RenderTexture mRenderTexture;

private:
    DrawingStatus mDrawingStatus;

    sf::Sprite mSprite;

    Pen& mPen;

    sf::Sprite mSpriteBlackWhite2x2;
};