#pragma once
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "StateStack.h"
#include "Pen.h"

#include <SFML/Graphics.hpp>

class Application {
public:
    Application();
    void run();

private:
    void processInput();
    void update(sf::Time deltaTime);
    void render();

    void updateStatistics(sf::Time elapsedTime);
    void registerStates();

    void loadTextures();

private:
    static const sf::Time TimePerFrame;

    sf::RenderWindow mWindow;
    TextureHolder* mTextures;
    FontHolder* mFonts;
    Pen mPen;

    StateStack mStateStack;

    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
};