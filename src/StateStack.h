#pragma once
#include "ResourceIdentifiers.h"
#include "State.h"
#include "StateIdentifiers.h"
#include "StateParameter.h"

#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>
#include <map>

class StateStack : private sf::NonCopyable {
public:
    enum Action {
        Push,
        Pop,
        Clear,
    };

public:
    explicit StateStack(State::Context context);

    template<typename T>
    void registerState(States::ID stateID);

    void update(sf::Time dt);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushState(States::ID stateID);
    void pushState(States::ID stateID, StateParameter parameter);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    State::Ptr createState(States::ID stateID, StateParameter parameter);
    void applyPendingChanges();

private:
    struct PendingChange {
        PendingChange(Action action);
        PendingChange(Action action, States::ID stateID, StateParameter parameter);
        Action action;
        States::ID stateID;
        StateParameter parameter;
    };

private:
    std::vector<State::Ptr> mStack;
    std::vector<PendingChange> mPendingList;

    State::Context mContext;
    std::map<States::ID, std::function<State::Ptr(StateParameter)>> mFactories;
};

template<typename T>
void StateStack::registerState(States::ID stateID) {
    mFactories[stateID] = [this](StateParameter) {
        return State::Ptr(new T(*this, mContext));
    };
}

class ColorMenuState;
class HandleFileState;

template<>
void StateStack::registerState<ColorMenuState>(States::ID stateID);

template<>
void StateStack::registerState<HandleFileState>(States::ID stateID);
