#pragma once
#include "DrawingShapeIdentifiers.h"
#include "DrawingCanvas.h"

#include <SFML/Graphics.hpp>

#include <map>
#include <functional>

class DrawingShape;

class Pen {
    enum class PenStatus {
        WAIT_TO_DRAW,
        DRAWING,
        DRAWED
    };

public:
    struct Context {
        Context(const sf::Color& color, int width);

        sf::Color color;
        int width;
    };

public:
    Pen(sf::RenderWindow& window, const Context& context);

    void setCanvas(DrawingCanvas& canvas);

    bool isDrawing() const;

    void handleEvent(const sf::Event& event);
    void draw();

    void setWidth(int width);
    int getWidth() const;

    void setColor(const sf::Color& color);
    const sf::Color& getColor() const;

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

    DrawingCanvas* mCanvas;
    Context mContext;
    DrawingShape* mDrawingShape;

    PenStatus mDrawingStatus;

    std::map<DrawingShapes::ID, std::function<DrawingShape*()>> mShapeFactories;
};

template<typename T>
void Pen::registerShape(DrawingShapes::ID shapeID) {
    mShapeFactories[shapeID] = [this]() {
        return new T(*this, mCanvas->getRenderArea());
    };
}