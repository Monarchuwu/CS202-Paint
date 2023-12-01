#include "Label.h"
#include "Utility.h"

namespace GUI {

    Label::Label(const std::string& text, const FontHolder* fonts)
        : mText("", fonts->get(Fonts::Sansation), 16) {
        setText(text);
    }

    bool Label::isSelectable() const {
        return false;
    }

    bool Label::handleEvent(const sf::Event& event) {
        return false;
    }

    void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(mText, states);
    }

    void Label::setText(const std::string& text) {
        mText.setString(text);
        centerOrigin(mText);
    }

} // namespace GUI