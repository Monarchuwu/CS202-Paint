#include "Application.h"
#include "Utility.h"
#include "State.h"
#include "StateIdentifiers.h"
#include "MainState.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
    : mWindow(sf::VideoMode(1600, 900), "My Paint", sf::Style::Close),
      mTextures(TextureHolder::getInstance()),
      mFonts(FontHolder::getInstance()),
      mStateStack(State::Context(mWindow, *mTextures, *mFonts)),
      mStatisticsText(),
      mStatisticsUpdateTime(),
      mStatisticsNumFrames(0) {
    mWindow.setKeyRepeatEnabled(false);
    mWindow.setPosition(sf::Vector2i(10, 10));

    mFonts->load(Fonts::Sansation, "data/Fonts/Sansation.ttf");
    //mTextures->load(Textures::ButtonNormal, "Media/Textures/ButtonNormal.png");

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
}