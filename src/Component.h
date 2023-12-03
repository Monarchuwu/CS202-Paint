#pragma once
#include <SFML/Graphics.hpp>

#include <memory>

namespace GUI {

    class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
        friend class Container;

    public:
        typedef std::shared_ptr<Component> Ptr;

    protected:
        Component();

    public:
        virtual ~Component();

        virtual bool isSelectable() const = 0;
        bool isSelected() const;
        virtual void select();
        virtual void deselect();

        virtual bool isActive() const;
        virtual void activate();
        virtual void deactivate();

        virtual bool isVisible() const;
        virtual void setVisible(bool flag);

        virtual bool handleEvent(const sf::Event& event) = 0;

        sf::Vector2f getWorldPosition() const;
        sf::Transform getWorldTransform() const;

    private:
        void setParent(Component& parent);
    private:
        bool mIsSelected;
        bool mIsActive;
        bool mIsVisible;

        Component* mParent;
    };

} // namespace GUI