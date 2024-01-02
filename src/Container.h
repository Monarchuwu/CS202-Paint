#pragma once
#include <vector>
#include <memory>
#include "Component.h"

namespace GUI {

    class Container : public Component {
        friend class ContainerOneActivate;

    public:
        typedef std::shared_ptr<Container> Ptr;

    public:
        Container(const sf::Vector2f& size);

        void pack(Component::Ptr component);

        virtual bool isSelectable() const;
        virtual bool handleEvent(const sf::Event& event);

        void setBackgroundColor(const sf::Color& color);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::vector<Component::Ptr> mChildren;

        sf::RectangleShape mBackground;
    };

} // namespace GUI
