#include "Container.h"

namespace GUI {

    Container::Container(const sf::Vector2f& size)
        : mChildren(),
          mBackground(size) {
        mBackground.setFillColor(sf::Color(255, 255, 255, 15));
    }

    void Container::pack(Component::Ptr component) {
        mChildren.push_back(component);
        component->setParent(*this);
    }

    bool Container::isSelectable() const {
        return false;
    }

    bool Container::handleEvent(const sf::Event& event) {
        if (!isVisible()) return false;

        if (event.type == sf::Event::MouseButtonPressed) {
            auto bounds = getWorldTransform().transformRect(mBackground.getGlobalBounds());
            if (bounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                for (auto& child : mChildren) {
                    if (child->handleEvent(event)) {
                        return true;
                    }
                }
                return true;
            }
        }
        return false;
    }

    void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (!isVisible()) return;

        states.transform *= getTransform();
        drawCurrent(target, states);
        drawChildren(target, states);
    }

    void Container::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(mBackground, states);
    }

    void Container::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
        for (const Component::Ptr& child : mChildren) {
            target.draw(*child, states);
        }
    }

} // namespace GUI