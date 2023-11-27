#include "EventHandler.h"

EventHandler::EventHandler() {}

bool EventHandler::handleEvent(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::Resized:
            return eventResized(event.size);
            break;

        case sf::Event::LostFocus:
            return eventLostFocus();
            break;

        case sf::Event::GainedFocus:
            return eventGainedFocus();
            break;

        case sf::Event::TextEntered:
            return eventTextEntered(event.text);
            break;

        case sf::Event::KeyPressed:
            return eventKeyPressed(event.key);
            break;

        case sf::Event::KeyReleased:
            return eventKeyReleased(event.key);
            break;

        case sf::Event::MouseWheelScrolled:
            return eventMouseWheelScrolled(event.mouseWheel);
            break;

        case sf::Event::MouseButtonPressed:
            return eventMouseButtonPressed(event.mouseButton);
            break;

        case sf::Event::MouseButtonReleased:
            return eventMouseButtonReleased(event.mouseButton);
            break;

        case sf::Event::MouseMoved:
            return eventMouseMoved(event.mouseMove);
            break;

        case sf::Event::MouseEntered:
            return eventMouseEntered();
            break;

        case sf::Event::MouseLeft:
            return eventMouseLeft();
            break;

        case sf::Event::JoystickButtonPressed:
            return eventJoystickButtonPressed(event.joystickButton);
            break;

        case sf::Event::JoystickButtonReleased:
            return eventJoystickButtonReleased(event.joystickButton);
            break;

        case sf::Event::JoystickMoved:
            return eventJoystickMoved(event.joystickMove);
            break;

        case sf::Event::JoystickConnected:
            return eventJoystickConnected(event.joystickConnect);
            break;

        case sf::Event::JoystickDisconnected:
            return eventJoystickDisconnected(event.joystickConnect);
            break;

        case sf::Event::TouchBegan:
            return eventTouchBegan(event.touch);
            break;

        case sf::Event::TouchMoved:
            return eventTouchMoved(event.touch);
            break;

        case sf::Event::TouchEnded:
            return eventTouchEnded(event.touch);
            break;

        case sf::Event::SensorChanged:
            return eventSensorChanged(event.sensor);
            break;
    }
    return false;
}
bool EventHandler::eventResized(const sf::Event::SizeEvent& size) {
	return false;
}
bool EventHandler::eventLostFocus() {
	return false;
}
bool EventHandler::eventGainedFocus() {
	return false;
}
bool EventHandler::eventTextEntered(const sf::Event::TextEvent& text) {
	return false;
}
bool EventHandler::eventKeyPressed(const sf::Event::KeyEvent& key) {
	return false;
}
bool EventHandler::eventKeyReleased(const sf::Event::KeyEvent& key) {
	return false;
}
bool EventHandler::eventMouseWheelScrolled(const sf::Event::MouseWheelEvent& mouseWheel) {
	return false;
}
bool EventHandler::eventMouseButtonPressed(const sf::Event::MouseButtonEvent& mouse) {
	return false;
}
bool EventHandler::eventMouseButtonReleased(const sf::Event::MouseButtonEvent& mouse) {
	return false;
}
bool EventHandler::eventMouseMoved(const sf::Event::MouseMoveEvent& mouse) {
	return false;
}
bool EventHandler::eventMouseEntered() {
	return false;
}
bool EventHandler::eventMouseLeft() {
	return false;
}
bool EventHandler::eventJoystickButtonPressed(const sf::Event::JoystickButtonEvent& joystick) {
	return false;
}
bool EventHandler::eventJoystickButtonReleased(const sf::Event::JoystickButtonEvent& joystick) {
	return false;
}
bool EventHandler::eventJoystickMoved(const sf::Event::JoystickMoveEvent& joystick) {
	return false;
}
bool EventHandler::eventJoystickConnected(const sf::Event::JoystickConnectEvent& joystick) {
	return false;
}
bool EventHandler::eventJoystickDisconnected(const sf::Event::JoystickConnectEvent& joystick) {
	return false;
}
bool EventHandler::eventTouchBegan(const sf::Event::TouchEvent& touch) {
	return false;
}
bool EventHandler::eventTouchMoved(const sf::Event::TouchEvent& touch) {
	return false;
}
bool EventHandler::eventTouchEnded(const sf::Event::TouchEvent& touch) {
	return false;
}
bool EventHandler::eventSensorChanged(const sf::Event::SensorEvent& sensor) {
	return false;
}
// Path: src/EventHandler.cpp