#pragma once
#include "Button.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics.hpp>
#include <functional>

namespace GUI {

    class InputBox : public Button {
    public:
        typedef std::shared_ptr<InputBox> Ptr;

    public:
        InputBox(const FontHolder* fonts,
                 const TextureHolder* textures,
                 Textures::ID boxNormal,
                 Textures::ID boxSelected,
                 Textures::ID boxPressed,
                 std::function<bool(sf::Uint32)> validCharacter);

        void setMaxCharacters(unsigned maxCharacters);
        void setDefaultCharacter(char defaultChar);
        void setDefaultString(const std::string& defaultString);
        void setString(const std::string& string);

        virtual void activate();
        virtual void deactivate();

        virtual bool handleEvent(const sf::Event& event);

        void setTextChangedCallback(std::function<void(std::string)> callback);
        void textChanged();

    protected:
        virtual void lowerBoundText(std::string& str);
        virtual void upperBoundText(std::string& str);
        
    private:
        void updateText();

    private:
        std::function<bool(sf::Uint32)> mIsValidCharacter;
        std::function<void(std::string)> mTextChangedCallback;
        std::string mDefaultString, mString;
        unsigned mMaxCharacters;
        char mDefaultChar;
    };

} // namespace GUI
