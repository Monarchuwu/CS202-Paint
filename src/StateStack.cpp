#include "StateStack.h"

#include <cassert>

template<>
void StateStack::registerState<ColorMenuState>(States::ID stateID) {
    mFactories[stateID] = [this](StateParameter parameter) {
        return State::Ptr(new ColorMenuState(*this, mContext, parameter.colorMenu.inputColor, parameter.colorMenu.callback));
    };
}

StateStack::StateStack(State::Context context)
    : mStack(), mPendingList(), mContext(context), mFactories() {
}

void StateStack::update(sf::Time dt) {
    // Iterate from top to bottom, stop as soon as update() returns false
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
        if (!(*itr)->update(dt))
            break;
    }
    applyPendingChanges();
}

void StateStack::draw() {
    // Draw all active states from bottom to top
    for (State::Ptr& state : mStack) {
        state->draw();
    }
}

void StateStack::handleEvent(const sf::Event& event) {
    // Iterate from top to bottom, stop as soon as handleEvent() returns false
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
        if (!(*itr)->handleEvent(event))
            break;
    }
}

void StateStack::pushState(States::ID stateID) {
    mPendingList.push_back(PendingChange(Push, stateID, StateParameter()));
}

void StateStack::pushState(States::ID stateID, StateParameter parameter) {
    mPendingList.push_back(PendingChange(Push, stateID, parameter));
}

void StateStack::popState() {
    mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates() {
    mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const {
    return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID, StateParameter parameter) {
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    return found->second(parameter);
}

void StateStack::applyPendingChanges() {
    for (PendingChange change : mPendingList) {
        switch (change.action) {
            case Push:
                mStack.push_back(createState(change.stateID, change.parameter));
                break;
            case Pop:
                mStack.pop_back();
                break;
            case Clear:
                mStack.clear();
                break;
        }
    }
    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action)
    : action(action), stateID(States::None), parameter() {
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID, StateParameter parameter)
    : action(action), stateID(stateID), parameter(parameter) {
}