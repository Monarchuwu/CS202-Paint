#include "MainState.h"

MainState::MainState(StateStack& stack, Context context)
    : State(stack, context),
      mWindow(*(context.window)),
      mTextures((context.textures)->getInstance()),
      mFonts((context.fonts)->getInstance()),
      mBackground(sf::Vector2f(1600, 900)) {
    mBackground.setFillColor(sf::Color(26, 32, 49));

    mDrawingCanvas = new DrawingCanvas(mWindow,
                                       sf::FloatRect(0, 210, 1600, 640),
                                       sf::Vector2f(640, 480));
}

void MainState::draw() {
    mWindow.draw(mBackground);

    mDrawingCanvas->draw();
}

bool MainState::update(sf::Time dt) {
    //mWorld.update(dt);

    //CommandQueue& commands = mWorld.getCommandQueue();
    //mPlayer.handleRealtimeInput(commands);

    return true;
}

bool MainState::handleEvent(const sf::Event& event) {
    mDrawingCanvas->handleEvent(event);

    // Game input handling
    //CommandQueue& commands = mWorld.getCommandQueue();
    //mPlayer.handleEvent(event, commands);

    // Escape pressed, trigger the pause screen
    //if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    //    requestStackPush(States::Pause);

    return true;
}