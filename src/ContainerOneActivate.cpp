#include "ContainerOneActivate.h"

namespace GUI {

	ContainerOneActivate::ContainerOneActivate(const sf::Vector2f& size)
        : Container(size) {
    }

    bool ContainerOneActivate::handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            auto bounds = getWorldTransform().transformRect(mBackground.getGlobalBounds());
            if (bounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                for (auto& child : mChildren) {
                    bool childActive = child->isActive();
                    if (child->handleEvent(event)) {
                        // If the child has just been activated
                        if (!childActive && child->isActive()) {
                            deactivateAllExcept(child);
						}
                        return true;
                    }
                }
                return true;
            }
        }
        return false;
	}

    void ContainerOneActivate::activate(std::size_t index) {
        if (index < mChildren.size()) {
			deactivateAllExcept(mChildren[index]);
            mChildren[index]->activate();
        }
    }

    void ContainerOneActivate::deactivateAllExcept(Component::Ptr child) {
        for (auto& c : mChildren) {
            if (c != child) {
				c->deactivate();
			}
		}
	}

} // namespace GUI