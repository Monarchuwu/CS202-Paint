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

    virtual void handleEvent(const sf::Event& event, const sf::Vector2f& drawingCenter, unsigned int zoomFactor);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
    virtual void drawToWindow(sf::RenderWindow& window);
    void clear(const sf::Color& color = sf::Color::Transparent);

    const sf::Texture& getCanvas();

    // this method will only be called after stopDrawing() called
    void drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
    // this method will only be called after stopDrawing() called
    sf::FloatRect getBoundingBox() const;

    void drawRotatingHandle(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

protected:
    // draw bounding box to mRenderTexture
    void drawBoundingBox();
    void updateBoundingBox(const sf::Vector2f& position);
    void resetBoundingBox(const sf::Vector2f& position);

private:
    bool checkHoldRotating(const sf::Vector2f& position) const ;
    float calculateAngle(sf::Vector2f position) const;
    sf::Vector2f convertPointToDefaultView(const sf::Vector2f& point, const sf::Vector2f& drawingCenter, unsigned int zoomFactor);

protected:
    // bounding box
    int mTop, mBottom, mLeft, mRight;

    sf::RenderTexture mRenderTexture;
    sf::RenderTexture mRenderTextureRotating;

private:
    DrawingStatus mDrawingStatus;

    float mAngle; // in degree
    bool isRotating;

    sf::Sprite mSprite;

    Pen& mPen;

    sf::Sprite mSpriteBlackWhite2x2;
};