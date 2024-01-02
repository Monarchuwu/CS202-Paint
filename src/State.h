#pragma once
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "StateIdentifiers.h"
#include "StateParameter.h"

#include <SFML/Graphics.hpp>

class StateStack;
class Pen;

class State {
public:
    typedef std::unique_ptr<State> Ptr;
    struct Context {
        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Pen& pen);

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        Pen* pen;
    };

public:
    State(StateStack& stack, Context context);
    virtual ~State();

    virtual void draw()                              = 0;
    virtual bool update(sf::Time deltaTime)          = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void requestStackPush(States::ID stateID);
    void requestStackPush(States::ID stateID, StateParameter parameter);
    void requestStackPop();
    void requestStateClear();

    Context getContext() const;

    void quit();
    bool isAvailable() const;

private:
    StateStack* mStack;
    Context mContext;
    bool mIsAvailable;
};