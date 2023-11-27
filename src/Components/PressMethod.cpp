#include "PressMethod.h"

PressMethod::PressMethod() : isPressed(false) {}

PressMethod::~PressMethod() {}

void PressMethod::setPressed(bool pressed) {
    isPressed = pressed;
}

bool PressMethod::getPressed() const {
    return isPressed;
}