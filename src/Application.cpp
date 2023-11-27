#include "Application.h"
#include <iostream>

const sf::Time TimePerFrame = sf::seconds(1.f / 15.f);

Application::Application()
    : mWindow(),
      mDrawingCanvas(sf::FloatRect(480, 290, 640, 480)),
      mNavigation(sf::FloatRect(0, 50, 1600, 160)) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16; // Default is 0
    mWindow.create(sf::VideoMode(1600, 900), "Paint Project", sf::Style::Close, settings);
    mWindow.setPosition(sf::Vector2i(10, 10));
    mWindow.setFramerateLimit(120);
    mDrawingCanvas.clear();

    mEventHandlers.push_back(&mNavigation);
    mEventHandlers.push_back(&mDrawingCanvas);
}

Application::~Application() {}

void Application::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Application::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        bool handled = false;
        for (auto& object : mEventHandlers) {
            if (object->handleEvent(event)) {
                handled = true;
                break;
            }
		}
        if (handled) continue;

        switch (event.type) {
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Application::update() {}

void Application::render() {
    mWindow.clear(sf::Color(26, 32, 49));

    mWindow.draw(mDrawingCanvas.getSprite());
    mWindow.draw(mNavigation);

    mWindow.display();
}