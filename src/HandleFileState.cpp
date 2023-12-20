#include "HandleFileState.h"
#include "Button.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Pen.h"

#include <SFML/Graphics.hpp>

HandleFileState::HandleFileState(StateStack& stack, Context context)
    : State(stack, context),
      mGUIContainer(sf::Vector2f(100, 200)) {
    mGUIContainer.setPosition(10, 50);
    Pen* pen = context.pen;

    // save to BMP button
    GUI::Button::Ptr saveBMPButton(new GUI::Button(context.fonts, context.textures,
                                                   Textures::Transparent70x40,
                                                   Textures::Transparent70x40,
                                                   Textures::Transparent70x40));
    saveBMPButton->setText("Save to BMP");
    saveBMPButton->setCallback([this]() {
        saveFile("data/SaveImages/screen.bmp");
        requestStackPop();
        quit();
    });
    saveBMPButton->setPosition(15, 0);
    mGUIContainer.pack(saveBMPButton);

    // save to PNG button
    GUI::Button::Ptr savePNGButton(new GUI::Button(context.fonts, context.textures,
                                                   Textures::Transparent70x40,
                                                   Textures::Transparent70x40,
                                                   Textures::Transparent70x40));
    savePNGButton->setText("Save to PNG");
    savePNGButton->setCallback([this]() {
        saveFile("data/SaveImages/screen.png");
        requestStackPop();
        quit();
    });
    savePNGButton->setPosition(15, 45);
    mGUIContainer.pack(savePNGButton);

    // save to JPG button
    GUI::Button::Ptr saveJPGButton(new GUI::Button(context.fonts, context.textures,
                                                   Textures::Transparent70x40,
                                                   Textures::Transparent70x40,
                                                   Textures::Transparent70x40));
    saveJPGButton->setText("Save to JPG");
    saveJPGButton->setCallback([this]() {
        saveFile("data/SaveImages/screen.jpg");
        requestStackPop();
        quit();
    });
    saveJPGButton->setPosition(15, 90);
    mGUIContainer.pack(saveJPGButton);

    // cancel button
    GUI::Button::Ptr cancelButton(new GUI::Button(context.fonts, context.textures,
                                                  Textures::Transparent70x40,
                                                  Textures::Transparent70x40,
                                                  Textures::Transparent70x40));
    cancelButton->setText("Cancel");
    cancelButton->setCallback([this]() {
        requestStackPop();
        quit();
    });
    cancelButton->setPosition(15, 135);
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

    if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Escape) {
			requestStackPop();
		    quit();
		}
	}

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