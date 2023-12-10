#include "Button.h"
#include "Utility.h"

namespace GUI {

    Button::Button(const FontHolder* fonts,
                   const TextureHolder* textures,
                   Textures::ID buttonNormal,
                   Textures::ID buttonSelected,
                   Textures::ID buttonPressed)
        : mCallback(),
          mNormalTexture(textures->get(buttonNormal)),
          mSelectedTexture(textures->get(buttonSelected)),
          mPressedTexture(textures->get(buttonPressed)),
          mSprite(),
          mText("", fonts->get(Fonts::Sansation), 16),
          mIsToggle(false) {
        mSprite.setTexture(mNormalTexture);

        sf::FloatRect bounds = mSprite.getLocalBounds();
        mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
    }

    void Button::setCallback(Callback callback) {
        mCallback = std::move(callback);
    }

    void Button::setText(const std::string& text) {
        mText.setString(text);
        centerOrigin(mText);
    }

    void Button::setToggle(bool flag) {
        mIsToggle = flag;
    }

    bool Button::isSelectable() const {
        return true;
    }

    void Button::select() {
        Component::select();

        mSprite.setTexture(mSelectedTexture);
    }

    void Button::deselect() {
        Component::deselect();

        mSprite.setTexture(mNormalTexture);
    }

    void Button::activate() {
        Component::activate();

        // If we are toggle then we should show that the button is pressed and thus "toggled".
        if (mIsToggle)
            mSprite.setTexture(mPressedTexture);

        if (mCallback)
            mCallback();

        // If we are not a toggle then deactivate the button since we are just momentarily activated.
        if (!mIsToggle)
            deactivate();
    }

    void Button::deactivate() {
        Component::deactivate();

        if (mIsToggle) {
            // Reset texture to right one depending on if we are selected or not.
            if (isSelected())
                mSprite.setTexture(mSelectedTexture);
            else
                mSprite.setTexture(mNormalTexture);
        }
    }

    bool Button::handleEvent(const sf::Event& event) {
        if (!isVisible()) return false;

        if (event.type == sf::Event::MouseButtonPressed) {
            auto bounds = getWorldTransform().transformRect(mSprite.getGlobalBounds());
            if (bounds.contains(event.mouseButton.x, event.mouseButton.y)) {
				activate();
				return true;
            }
        }
        return false;
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (!isVisible()) return;

        states.transform *= getTransform();
        target.draw(mSprite, states);
        target.draw(mText, states);
    }

} // namespace GUI