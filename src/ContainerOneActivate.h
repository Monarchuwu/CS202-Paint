#pragma once
#include "Container.h"

namespace GUI {

    // Container that activates only one component at a time
    class ContainerOneActivate : public Container {
    public:
        ContainerOneActivate(const sf::Vector2f& size);

        virtual bool handleEvent(const sf::Event& event);
    };

} // namespace GUI