#include "ContainerOneActivate.h"

namespace GUI {

	ContainerOneActivate::ContainerOneActivate(const sf::Vector2f& size)
        : Container(size) {
    }

    bool ContainerOneActivate::handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::MouseButtonReleased) {
            auto bounds = getWorldTransform().transformRect(mBackground.getGlobalBounds());
            if (bounds.contains(event.mouseButton.x, event.mouseButton.y)) {
                for (auto& child : mChildren) {
                    bool childActive = child->isActive();
                    if (child->handleEvent(event)) {
                        // If the child has just been activated
                        if (!childActive && child->isActive()) {
                            // Deactivate all other children
                            for (auto& otherChild : mChildren) {
                                if (&otherChild != &child) {
									otherChild->deactivate();
								}
							}
						}
                        return true;
                    }
                }
            }
        }
        return false;
	}

} // namespace GUI