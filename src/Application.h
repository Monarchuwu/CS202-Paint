#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "DrawingCanvas.h"
#include "Navigation.h"
#include "EventHandler.h"

class Application {
public:
    Application();
    ~Application();
    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    sf::RenderWindow mWindow;
    DrawingCanvas mDrawingCanvas;
    Navigation mNavigation;
    std::vector<EventHandler*> mEventHandlers;
};