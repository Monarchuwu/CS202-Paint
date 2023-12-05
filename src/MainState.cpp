#include "MainState.h"
#include "DrawingShapeIdentifiers.h"

MainState::MainState(StateStack& stack, Context context)
    : State(stack, context),
      mWindow(*(context.window)),
      mTextures((context.textures)->getInstance()),
      mFonts((context.fonts)->getInstance()),
      mBackground(sf::Vector2f(1600, 900)),
      mPen(*(context.pen)),
      mDrawingCanvas(context,
                     sf::FloatRect(0, 210, 1600, 640),
                     sf::Vector2f(640, 480)),
      mControlTable(this, context, mPen, sf::FloatRect(0, 50, 1600, 160)),
      mHandleFileButton(mFonts, mTextures, Textures::Transparent70x40,
                                           Textures::Transparent70x40,
                                           Textures::Transparent70x40) {

    mBackground.setFillColor(sf::Color(26, 32, 49));

    mHandleFileButton.setPosition(10, 10);
    mHandleFileButton.setText("File");
    mHandleFileButton.setCallback([this] () {
		requestStackPush(States::HandleFile);
	});
}

void MainState::draw() {
    mWindow.draw(mBackground);

    mDrawingCanvas.draw();
    mControlTable.draw();
    mWindow.draw(mHandleFileButton);
}

bool MainState::update(sf::Time dt) {
    mDrawingCanvas.update();
    mControlTable.update();

    //CommandQueue& commands = mWorld.getCommandQueue();
    //mPlayer.handleRealtimeInput(commands);

    return true;
}

bool MainState::handleEvent(const sf::Event& event) {
    // Escape released, then exit the application
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
        requestStateClear();

    mDrawingCanvas.handleEvent(event);
    mControlTable.handleEvent(event);
    mHandleFileButton.handleEvent(event);

    // Game input handling
    //CommandQueue& commands = mWorld.getCommandQueue();
    //mPlayer.handleEvent(event, commands);

    return true;
}