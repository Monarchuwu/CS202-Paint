#pragma once
#include "Container.h"

namespace GUI {

    // Container that activates only one component at a time
    class ContainerOneActivate : public Container {
    public:
        ContainerOneActivate(const sf::Vector2f& size);

        virtual bool handleEvent(const sf::Event& event);

        void activate(std::size_t index);

    protected:
        void deactivateAllExcept(Component::Ptr child);
    };

} // namespace GUI