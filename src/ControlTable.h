#pragma once
#include "State.h"
#include "Pen.h"
#include "Container.h"
#include "Button.h"
#include "DrawingShapeIdentifiers.h"

#include <SFML/Graphics.hpp>

#include <vector>

class MainState;

class ControlTable {
public:
    ControlTable(MainState* mainState,
                 State::Context context, Pen& pen,
		         const sf::FloatRect& objectArea);

    bool handleEvent(const sf::Event& event);
    void update();
    void draw();

	//CommandQueue& getCommandQueue();

private:
    void addSizeCategory(State::Context& context);
    void addShapeCategory(State::Context& context);
    void addColorCategory(State::Context& context);

private:
    MainState* mMainState;
	sf::RenderWindow& mWindow;
    TextureHolder* mTextures;
	FontHolder* mFonts;
    Pen& mPen;
	sf::FloatRect mObjectArea;

    //CommandQueue mCommandQueue;
	std::vector <GUI::Container::Ptr> mGUIContainers;

    // Colors
	GUI::Button::Ptr mColorDisplayer;

	sf::RectangleShape mBackground;
};
