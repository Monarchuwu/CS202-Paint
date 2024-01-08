#pragma once
#include "DrawingShapeIdentifiers.h"
#include "DrawingCanvas.h"
#include "ResourceHolder.h"

#include <SFML/Graphics.hpp>

#include <map>
#include <functional>

class DrawingShape;

class Pen {
public:
    struct Context {
        Context(const sf::Color& color, int width);

        sf::Color color;
        int width;
    };

public:
    Pen(sf::RenderWindow& window,
        TextureHolder* textures,
        FontHolder* fonts,
        const Context& context);

    void setCanvas(DrawingCanvas& canvas);
    const DrawingCanvas& getCanvas() const;
    const sf::FloatRect& getDrawingArea() const;
    const sf::FloatRect& getDisplayArea() const;
    // this method should not be here
    // it should be in CommandQueue
    void addTexture(const sf::Texture& texture);

    bool handleEvent(const sf::Event& event, const sf::Vector2f& drawingCenter, unsigned int zoomFactor);
    void draw();

    void setWidth(int width);
    int getWidth() const;

    void setColor(const sf::Color& color);
    const sf::Color& getColor() const;

    void setGradientColor(const sf::Color& firstColor, const sf::Color& secondColor);
    const sf::Texture& getGradientTexture() const;

    template<typename T>
    void registerShape(DrawingShapes::ID shapeID);
    void setShape(DrawingShapes::ID shapeID);

private:
    DrawingShape* createShape(DrawingShapes::ID shapeID);

    void startDrawing(const sf::Vector2f& position);
    void stopDrawing();
    void move(const sf::Vector2f& position);

private:
    sf::RenderWindow& mWindow;
    TextureHolder* mTextures;
    FontHolder* mFonts;

    DrawingCanvas* mCanvas;
    Context mContext;
    sf::Texture mGradientTexture;
    DrawingShape* mDrawingShape;

    std::map<DrawingShapes::ID, std::function<DrawingShape*()>> mShapeFactories;
};

template<typename T>
void Pen::registerShape(DrawingShapes::ID shapeID) {
    mShapeFactories[shapeID] = [this]() {
        return new T(*this, mTextures, mCanvas->getRenderArea());
    };
}

class DrawingShapeTextWriting;

template<>
void Pen::registerShape<DrawingShapeTextWriting>(DrawingShapes::ID shapeID);
