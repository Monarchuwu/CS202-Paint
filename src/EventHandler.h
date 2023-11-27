#pragma once
#include <SFML/Graphics.hpp>

class EventHandler {
protected:
    EventHandler();

public:
    bool handleEvent(const sf::Event& event);
    // The window was resized
    virtual bool eventResized(const sf::Event::SizeEvent& size);
    // The window lost the focus
    virtual bool eventLostFocus();
    // The window gained the focus
    virtual bool eventGainedFocus();
    // A character was entered
    virtual bool eventTextEntered(const sf::Event::TextEvent& text);
    // A key was pressed
    virtual bool eventKeyPressed(const sf::Event::KeyEvent& key);
    // A key was released
    virtual bool eventKeyReleased(const sf::Event::KeyEvent& key);
    // The mouse wheel was scrolled
    virtual bool eventMouseWheelScrolled(const sf::Event::MouseWheelEvent& mouseWheel);
    // A mouse button was pressed
    virtual bool eventMouseButtonPressed(const sf::Event::MouseButtonEvent& mouse);
    // A mouse button was released
    virtual bool eventMouseButtonReleased(const sf::Event::MouseButtonEvent& mouse);
    // The mouse cursor moved
    virtual bool eventMouseMoved(const sf::Event::MouseMoveEvent& mouse);
    // The mouse cursor entered the area of the window
    virtual bool eventMouseEntered();
    // The mouse cursor left the area of the window
    virtual bool eventMouseLeft();
    // A joystick button was pressed
    virtual bool eventJoystickButtonPressed(const sf::Event::JoystickButtonEvent& joystick);
    // A joystick button was released
    virtual bool eventJoystickButtonReleased(const sf::Event::JoystickButtonEvent& joystick);
    // The joystick moved along an axis
    virtual bool eventJoystickMoved(const sf::Event::JoystickMoveEvent& joystick);
    // A joystick was connected
    virtual bool eventJoystickConnected(const sf::Event::JoystickConnectEvent& joystick);
    // A joystick was disconnected
    virtual bool eventJoystickDisconnected(const sf::Event::JoystickConnectEvent& joystick);
    // A touch event began
    virtual bool eventTouchBegan(const sf::Event::TouchEvent& touch);
    // A touch moved
    virtual bool eventTouchMoved(const sf::Event::TouchEvent& touch);
    // A touch event ended
    virtual bool eventTouchEnded(const sf::Event::TouchEvent& touch);
    // The sensor value changed
    virtual bool eventSensorChanged(const sf::Event::SensorEvent& sensor);
};
