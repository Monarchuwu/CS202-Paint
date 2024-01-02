#pragma once
#include "State.h"
#include "ColorEditingCenter.h"
#include "ColorTable.h"
#include "VerticalScrollBar.h"
#include "InputBox.h"
#include "DecimalInputBox.h"
#include "Container.h"
#include "Label.h"

#include <SFML/Graphics.hpp>

#include <functional>

class ColorMenuState : public State, public ColorEditingCenter {
public:
    ColorMenuState(StateStack& stack, Context context, sf::Color inputColor, std::function<void(sf::Color)> callback);

    virtual void draw();
    virtual bool update(sf::Time deltaTime);
    virtual bool handleEvent(const sf::Event& event);

    virtual void updateActualColor(sf::Color color);
    virtual void updateDisplayColor(sf::Color color);
    virtual void updateActualColorParameter(ColorParameterType type, int value);
    virtual void updateDisplayColorParameter(ColorParameterType type, int value);

private:
    void updateDisplay();

    void setUp4InputBoxes(Context& context, sf::Vector2f position);
    void setUp2Buttons(Context& context, sf::Vector2f position);

private:
    std::function<void(sf::Color)> mOKCallback;

    float mScale;
    sf::Color mActualColor, mDisplayColor;

    sf::RectangleShape mBackground;
    ColorTable mColorTable;
    sf::RectangleShape mDisplayColorRectangle;
    VerticalScrollBar mScaleScrollBar;
    GUI::DecimalInputBox::Ptr mInputBoxR, mInputBoxG, mInputBoxB;
    GUI::InputBox::Ptr mInputBoxHexaDecimal;
    GUI::Container::Ptr mLabels, mButtons;
};