#include "InputBox.h"

#include <cassert>

namespace GUI {

    InputBox::InputBox(const FontHolder* fonts,
                       const TextureHolder* textures,
                       Textures::ID boxNormal,
                       Textures::ID boxSelected,
                       Textures::ID boxPressed,
                       std::function<bool(sf::Uint32)> validCharacter)
        : Button(fonts, textures, boxNormal, boxSelected, boxPressed),
		  mIsValidCharacter(validCharacter),
          mTextChangedCallback(),
          mDefaultString(""),
          mString(""),
          mMaxCharacters(-1),
          mDefaultChar('\0') {
        setToggle(true);
    }

    void InputBox::setMaxCharacters(unsigned maxCharacters) {
        mMaxCharacters = maxCharacters;
    }

    void InputBox::setDefaultCharacter(char defaultChar) {
        assert(mIsValidCharacter(defaultChar));
		assert(mMaxCharacters != -1);
        mDefaultChar = defaultChar;
		updateText();
	}

    void InputBox::setDefaultString(const std::string& defaultString) {
        mDefaultString = defaultString;
    }

	void InputBox::setString(const std::string& string) {
        mString = string;
		updateText();
    }

    void InputBox::activate() {
        Button::activate();
    }

    void InputBox::deactivate() {
		Button::deactivate();
	}

    bool InputBox::handleEvent(const sf::Event& event) {
		if (!isVisible()) return false;

        if (event.type == sf::Event::MouseButtonPressed) {
		    if (event.mouseButton.button == sf::Mouse::Left) {
		        if (getWorldBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (!isActive()) {
		                activate();
						updateText();
					}
		        }
		    }
		}

		if (event.type == sf::Event::TextEntered) {
			if (isActive()) {
		        if (event.text.unicode == '\b') {
		            if (mString.size() > 0) {
		                mString.pop_back();
						lowerBoundText(mString);
		                textChanged();
		                updateText();
		            }
				} else if (mIsValidCharacter(event.text.unicode)) {
					if (mString.size() < mMaxCharacters) {
						mString += static_cast<char>(event.text.unicode);
		                upperBoundText(mString);
						textChanged();
						updateText();
					}
				}
                return true;
			}
		}

        if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
                if (!getWorldBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
					if (isActive()) {
		                deactivate();
		                updateText();
					}
                }
			}
		}

        return false;
	}

	void InputBox::setTextChangedCallback(std::function<void(std::string)> callback) {
		mTextChangedCallback = callback;
	}
	void InputBox::textChanged() {
		if (mTextChangedCallback) {
			mTextChangedCallback(mString);
		}
	}

	void InputBox::lowerBoundText(std::string& str) {
	}
	void InputBox::upperBoundText(std::string& str) {
	}

	void InputBox::updateText() {
        if (isActive()) {
			setText(mString);
        }
        else if (mString.empty() && !mDefaultString.empty()) {
			setText(mDefaultString);
		}
        else if (mDefaultChar != '\0') {
			int cnt = std::max(0, (int)mMaxCharacters - (int)mString.size());
			setText(std::string(cnt, mDefaultChar) + mString);
        }
		else {
			setText(mString);
		}
	}

} // namespace GUI