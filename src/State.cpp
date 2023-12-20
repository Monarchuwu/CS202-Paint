#include "State.h"
#include "StateStack.h"
#include "Pen.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Pen& pen)
    : window(&window), textures(&textures), fonts(&fonts), pen(&pen) {
}

State::State(StateStack& stack, Context context)
    : mStack(&stack), mContext(context), mIsAvailable(true) {
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

void State::quit() {
    mIsAvailable = false;
}

bool State::isAvailable() const {
	return mIsAvailable;
}