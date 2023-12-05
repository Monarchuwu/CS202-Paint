#pragma once
#include "State.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "DrawingCanvas.h"
#include "Pen.h"
#include "ControlTable.h"
#include "Button.h"

#include <SFML/Graphics.hpp>

class MainState : public State {
    friend class ControlTable;

public:
    MainState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time deltaTime);
    virtual bool handleEvent(const sf::Event& event);

private:
    //void shapeChanged();
    //void penChanged();
    //void brushChanged();
    //void colorChanged();
    //void thicknessChanged();
	//void saveToFile();
	//void loadFromFile();

private:
    sf::RenderWindow &mWindow;
    TextureHolder* mTextures;
    FontHolder* mFonts;

    sf::RectangleShape mBackground;

    Pen& mPen;
    DrawingCanvas mDrawingCanvas;
    ControlTable mControlTable;

    GUI::Button mHandleFileButton;

    //QLabel *shapeLabel;
    //QLabel *penWidthLabel;
    //QLabel *penStyleLabel;
    //QLabel *brushStyleLabel;
    //QComboBox *shapeComboBox;
    //QComboBox *penStyleComboBox;
    //QComboBox *brushStyleComboBox;
};