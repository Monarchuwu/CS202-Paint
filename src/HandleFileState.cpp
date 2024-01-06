#include "HandleFileState.h"
#include "Button.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Pen.h"

#include <SFML/Graphics.hpp>

HandleFileState::HandleFileState(StateStack& stack, Context context)
    : State(stack, context),
      mGUIContainer(sf::Vector2f(110, 185)) {
    mGUIContainer.setPosition(10, 50);
    mGUIContainer.setBackgroundColor(sf::Color(128, 128, 128));
    Pen* pen = context.pen;

    // save to BMP button
    GUI::Button::Ptr saveBMPButton(new GUI::Button(context.fonts, context.textures,
                                                   Textures::DarkGray100x40,
                                                   Textures::DarkGray100x40,
                                                   Textures::DarkGray100x40));
    saveBMPButton->setText("Save to BMP");
    saveBMPButton->setCallback([this]() {
        saveFile("data/SaveImages/screen.bmp");
        requestStackPop();
        quit();
    });
    saveBMPButton->setPosition(5, 5);
    mGUIContainer.pack(saveBMPButton);

    // save to PNG button
    GUI::Button::Ptr savePNGButton(new GUI::Button(context.fonts, context.textures,
                                                   Textures::DarkGray100x40,
                                                   Textures::DarkGray100x40,
                                                   Textures::DarkGray100x40));
    savePNGButton->setText("Save to PNG");
    savePNGButton->setCallback([this]() {
        saveFile("data/SaveImages/screen.png");
        requestStackPop();
        quit();
    });
    savePNGButton->setPosition(5, 50);
    mGUIContainer.pack(savePNGButton);

    // save to JPG button
    GUI::Button::Ptr saveJPGButton(new GUI::Button(context.fonts, context.textures,
                                                   Textures::DarkGray100x40,
                                                   Textures::DarkGray100x40,
                                                   Textures::DarkGray100x40));
    saveJPGButton->setText("Save to JPG");
    saveJPGButton->setCallback([this]() {
        saveFile("data/SaveImages/screen.jpg");
        requestStackPop();
        quit();
    });
    saveJPGButton->setPosition(5, 95);
    mGUIContainer.pack(saveJPGButton);

    // cancel button
    GUI::Button::Ptr cancelButton(new GUI::Button(context.fonts, context.textures,
                                                  Textures::DarkGray100x40,
                                                  Textures::DarkGray100x40,
                                                  Textures::DarkGray100x40));
    cancelButton->setText("Cancel");
    cancelButton->setCallback([this]() {
        requestStackPop();
        quit();
    });
    cancelButton->setPosition(5, 140);
    mGUIContainer.pack(cancelButton);
}

void HandleFileState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mGUIContainer);
}

bool HandleFileState::update(sf::Time) {
    return false;
}

bool HandleFileState::handleEvent(const sf::Event& event) {
    if (!isAvailable()) return false;

    mGUIContainer.handleEvent(event);
    return false;
}

void HandleFileState::saveFile(const std::string& filename) {
    // The supported image formats are bmp, png, tga and jpg.
	sf::RenderWindow& window = *getContext().window;
	sf::Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);
	texture.copyToImage().saveToFile(filename);
}