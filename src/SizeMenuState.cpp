#include "SizeMenuState.h"
#include "Button.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "Button.h"

#include <SFML/Graphics.hpp>

SizeMenuState::SizeMenuState(StateStack& stack, Context context)
    : State(stack, context),
      mGUIContainer(sf::Vector2f(190, 230)) {
    mGUIContainer.setPosition(10, 220);
    Pen* pen = context.pen;

    // 1px button
    GUI::Button::Ptr size1pxButton(new GUI::Button(context.fonts, context.textures,
                                                   Textures::ButtonSize1pxNormal,
                                                   Textures::ButtonSize1pxSelected,
                                                   Textures::ButtonSize1pxPressed));
    size1pxButton->setCallback([this, pen]() {
        pen->setWidth(1);
        requestStackPop();
    });
    size1pxButton->setPosition(3, 6);
    if (pen->getWidth() == 1) {
        size1pxButton->select();
    }
    mGUIContainer.pack(size1pxButton);

    // 3px button
    GUI::Button::Ptr size3pxButton(new GUI::Button(context.fonts, context.textures,
                                                   Textures::ButtonSize3pxNormal,
                                                   Textures::ButtonSize3pxSelected,
                                                   Textures::ButtonSize3pxPressed));
    size3pxButton->setCallback([this, pen]() {
        pen->setWidth(3);
        requestStackPop();
    });
    size3pxButton->setPosition(3, 62);
    if (pen->getWidth() == 3) {
        size3pxButton->select();
    }
    mGUIContainer.pack(size3pxButton);

    // 5px button
    GUI::Button::Ptr size5pxButton(new GUI::Button(context.fonts, context.textures,
                                                   Textures::ButtonSize5pxNormal,
                                                   Textures::ButtonSize5pxSelected,
                                                   Textures::ButtonSize5pxPressed));
    size5pxButton->setCallback([this, pen]() {
        pen->setWidth(5);
        requestStackPop();
    });
    size5pxButton->setPosition(3, 118);
    if (pen->getWidth() == 5) {
        size5pxButton->select();
    }
    mGUIContainer.pack(size5pxButton);

    // 8px button
    GUI::Button::Ptr size8pxButton(new GUI::Button(context.fonts, context.textures,
                                                   Textures::ButtonSize8pxNormal,
                                                   Textures::ButtonSize8pxSelected,
                                                   Textures::ButtonSize8pxPressed));
    size8pxButton->setCallback([this, pen]() {
        pen->setWidth(8);
        requestStackPop();
    });
    size8pxButton->setPosition(3, 174);
    if (pen->getWidth() == 8) {
        size8pxButton->select();
    }
    mGUIContainer.pack(size8pxButton);
}

void SizeMenuState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mGUIContainer);
}

bool SizeMenuState::update(sf::Time) {
    return false;
}

bool SizeMenuState::handleEvent(const sf::Event& event) {
    mGUIContainer.handleEvent(event);
    return false;
}