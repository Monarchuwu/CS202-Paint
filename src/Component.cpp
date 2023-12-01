#include "Component.h"

namespace GUI {
    Component::Component()
        : mIsSelected(false), mIsActive(false), mParent(nullptr) {
    }

    Component::~Component() {
    }

    bool Component::isSelected() const {
        return mIsSelected;
    }

    void Component::select() {
        mIsSelected = true;
    }

    void Component::deselect() {
        mIsSelected = false;
    }

    bool Component::isActive() const {
        return mIsActive;
    }

    void Component::activate() {
        mIsActive = true;
    }

    void Component::deactivate() {
        mIsActive = false;
    }

    sf::Vector2f Component::getWorldPosition() const {
        return getWorldTransform() * sf::Vector2f();
    }

    sf::Transform Component::getWorldTransform() const {
        sf::Transform transform = sf::Transform::Identity;

        for (const Component* node = this; node != nullptr; node = node->mParent)
            transform = node->getTransform() * transform;

        return transform;
    }

    void Component::setParent(Component& parent) {
        mParent = &parent;
    }

} // namespace GUI