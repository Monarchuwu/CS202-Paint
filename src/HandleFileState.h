#pragma once
#include "State.h"
#include "Container.h"

#include <SFML/Graphics.hpp>

class HandleFileState : public State {
public:
    HandleFileState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time deltaTime);
    virtual bool handleEvent(const sf::Event& event);

private:
    void saveFile(const std::string& filename);

private:
    GUI::Container mGUIContainer;
};