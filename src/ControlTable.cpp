#include "ControlTable.h"
#include "Label.h"
#include "Button.h"
#include "ResourceIdentifiers.h"
#include "MainState.h"

ControlTable::ControlTable(MainState* mainState,
                           State::Context context, Pen& pen,
                           const sf::FloatRect& objectArea)
    : mMainState(mainState),
      mWindow(*(context.window)),
      mTextures(context.textures),
      mFonts(context.fonts),
      mPen(pen),
      mObjectArea(objectArea) {
    mBackground.setSize(sf::Vector2f(mObjectArea.width, mObjectArea.height));
    mBackground.setPosition(mObjectArea.left, mObjectArea.top);
    mBackground.setFillColor(sf::Color(255, 255, 255, 15));

    GUI::Container::Ptr container(new GUI::Container(sf::Vector2f(70, 160)));
    container->setPosition(10, 50);

    GUI::Label::Ptr label(new GUI::Label("Size", mFonts));
    label->setPosition(35, 130);
    container->pack(label);

    GUI::Button::Ptr button(new GUI::Button(context.fonts, context.textures,
                                            Textures::ButtonSizeNormal,
                                            Textures::ButtonSizeSelected,
                                            Textures::ButtonSizePressed));

    button->setCallback([this]() {
        mMainState->requestStackPush(States::SizeMenu);
    });
    button->setPosition(15, 35);
    container->pack(button);

    mGUIContainers.emplace_back(std::move(container));
}

void ControlTable::handleEvent(const sf::Event& event) {
    for (auto& container : mGUIContainers) {
		container->handleEvent(event);
	}
}

void ControlTable::update() {
}

void ControlTable::draw() {
	mWindow.draw(mBackground);

    for (auto& container : mGUIContainers) {
		mWindow.draw(*container);
	}
}