#pragma once
#include "State.h"
#include "Container.h"

#include <SFML/Graphics.hpp>

#include <memory>

class HandleFileState : public State {
public:
    HandleFileState(StateStack& stack, Context context, const sf::Texture* saveTexture);

    virtual void draw();
    virtual bool update(sf::Time deltaTime);
    virtual bool handleEvent(const sf::Event& event);

private:
    void saveFile(const std::string& filename);

private:
    const sf::Texture* mSaveTexture;
    GUI::Container mGUIContainer;
};