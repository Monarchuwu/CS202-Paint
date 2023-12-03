#include "State.h"
#include "StateStack.h"
#include "Pen.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Pen& pen)
    : window(&window), textures(&textures), fonts(&fonts), pen(&pen) {
}

State::State(StateStack& stack, Context context)
    : mStack(&stack), mContext(context) {
}

State::~State() {
}

void State::requestStackPush(States::ID stateID) {
    mStack->pushState(stateID);
}

void State::requestStackPop() {
    mStack->popState();
}

void State::requestStateClear() {
    mStack->clearStates();
}

State::Context State::getContext() const {
    return mContext;
}