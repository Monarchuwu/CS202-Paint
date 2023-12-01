#pragma once
#include "State.h"
#include "Container.h"

#include <SFML/Graphics.hpp>

class SizeMenuState : public State {
public:
    SizeMenuState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time deltaTime);
    virtual bool handleEvent(const sf::Event& event);

private:
    GUI::Container mGUIContainer;
};