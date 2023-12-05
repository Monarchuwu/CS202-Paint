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
      mPen(mWindow, mTextures, mFonts, Pen::Context(sf::Color::Black, 3)),
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

    mTextures->load(Textures::ButtonShapeLinesStripNormal, "data/Textures/button-shape-lines_strip-normal.png");
    mTextures->load(Textures::ButtonShapeLinesStripSelected, "data/Textures/button-shape-lines_strip-selected.png");
    mTextures->load(Textures::ButtonShapeLineNormal, "data/Textures/button-shape-line-normal.png");
    mTextures->load(Textures::ButtonShapeLineSelected, "data/Textures/button-shape-line-selected.png");
    mTextures->load(Textures::ButtonShapeRectangleNormal, "data/Textures/button-shape-rectangle-normal.png");
    mTextures->load(Textures::ButtonShapeRectangleSelected, "data/Textures/button-shape-rectangle-selected.png");
    mTextures->load(Textures::ButtonShapeOvalNormal, "data/Textures/button-shape-oval-normal.png");
    mTextures->load(Textures::ButtonShapeOvalSelected, "data/Textures/button-shape-oval-selected.png");
    mTextures->load(Textures::ButtonShapeTriangleNormal, "data/Textures/button-shape-triangle-normal.png");
    mTextures->load(Textures::ButtonShapeTriangleSelected, "data/Textures/button-shape-triangle-selected.png");
    mTextures->load(Textures::ButtonShapeRightTriangleNormal, "data/Textures/button-shape-right_triangle-normal.png");
    mTextures->load(Textures::ButtonShapeRightTriangleSelected, "data/Textures/button-shape-right_triangle-selected.png");
    mTextures->load(Textures::ButtonShapeDiamondNormal, "data/Textures/button-shape-diamond-normal.png");
    mTextures->load(Textures::ButtonShapeDiamondSelected, "data/Textures/button-shape-diamond-selected.png");

    mTextures->load(Textures::ButtonShapeTextWritingNormal, "data/Textures/button-shape-text_writing-normal.png");
    mTextures->load(Textures::ButtonShapeTextWritingSelected, "data/Textures/button-shape-text_writing-selected.png");

    mTextures->load(Textures::ButtonHistoryPanelNormal, "data/Textures/button-history_panel-normal.png");
    mTextures->load(Textures::ButtonHistoryPanelSelected, "data/Textures/button-history_panel-selected.png");

    mTextures->load(Textures::BlackWhite2x2, "data/Textures/black-white-2x2.png");
    mTextures->get(Textures::BlackWhite2x2).setRepeated(true);
}
