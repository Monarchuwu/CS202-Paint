#include "Application.h"
#include "Utility.h"
#include "State.h"
#include "StateIdentifiers.h"
#include "MainState.h"
#include "SizeMenuState.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
    : mWindow(sf::VideoMode(1600, 900), "My Paint", sf::Style::Close),
      mTextures(TextureHolder::getInstance()),
      mFonts(FontHolder::getInstance()),
      mPen(Pen::Context(sf::Color::Black, 3)),
      mStateStack(State::Context(mWindow, *mTextures, *mFonts, mPen)),
      mStatisticsText(),
      mStatisticsUpdateTime(),
      mStatisticsNumFrames(0) {
    mWindow.setKeyRepeatEnabled(false);
    mWindow.setPosition(sf::Vector2i(10, 10));

    mFonts->load(Fonts::Sansation, "data/Fonts/Sansation.ttf");
    loadTextures();

    mStatisticsText.setFont(mFonts->get(Fonts::Sansation));
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10u);

    registerStates();
    mStateStack.pushState(States::Main);
}

void Application::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            // Check inside this loop, because stack might be empty after update() call
            if (mStateStack.isEmpty())
                mWindow.close();
        }

        updateStatistics(elapsedTime);
        render();
    }
}

void Application::processInput() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time deltaTime) {
    mStateStack.update(deltaTime);
}

void Application::render() {
    mWindow.clear();

    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);

    mWindow.display();
}

void Application::updateStatistics(sf::Time elapsedTime) {
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f)) {
        mStatisticsText.setString(
            "Frames / Second = " + toString(mStatisticsNumFrames) + "\n" + "Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Application::registerStates() {
    mStateStack.registerState<MainState>(States::Main);
    mStateStack.registerState<SizeMenuState>(States::SizeMenu);
}

void Application::loadTextures() {
    mTextures->load(Textures::ButtonSizeNormal, "data/Textures/button-size-40x60.png");
    mTextures->load(Textures::ButtonSize1pxNormal, "data/Textures/button-size-1px-normal.png");
    mTextures->load(Textures::ButtonSize1pxSelected, "data/Textures/button-size-1px-selected.png");
    mTextures->load(Textures::ButtonSize3pxNormal, "data/Textures/button-size-3px-normal.png");
    mTextures->load(Textures::ButtonSize3pxSelected, "data/Textures/button-size-3px-selected.png");
    mTextures->load(Textures::ButtonSize5pxNormal, "data/Textures/button-size-5px-normal.png");
    mTextures->load(Textures::ButtonSize5pxSelected, "data/Textures/button-size-5px-selected.png");
    mTextures->load(Textures::ButtonSize8pxNormal, "data/Textures/button-size-8px-normal.png");
    mTextures->load(Textures::ButtonSize8pxSelected, "data/Textures/button-size-8px-selected.png");
}