#include "DecimalInputBox.h"
#include "Utility.h"

#include <string>

namespace GUI {

    DecimalInputBox::DecimalInputBox(const FontHolder* fonts,
                                     const TextureHolder* textures,
                                     Textures::ID boxNormal,
                                     Textures::ID boxSelected,
                                     Textures::ID boxPressed)
        : InputBox(fonts, textures,
                   boxNormal, boxSelected, boxPressed,
                   [](sf::Uint32 c) -> bool {
                       return (c >= '0' && c <= '9');
                   }),
          mSetMinValue(false),
          mSetMaxValue(false),
          mMinValue(),
          mMaxValue() {
    }

    void DecimalInputBox::setMinValue(int minValue) {
        mSetMinValue = true;
        mMinValue    = minValue;
    }

    void DecimalInputBox::setMaxValue(int maxValue) {
        mSetMaxValue = true;
        mMaxValue    = maxValue;
    }

    void DecimalInputBox::lowerBoundText(std::string& str) {
        if (mSetMinValue) {
            int value = str.empty() ? 0 : std::stoi(str);
            if (value < mMinValue) {
                str = std::to_string(mMinValue);
            }
        }
    }

    void DecimalInputBox::upperBoundText(std::string& str) {
        if (mSetMaxValue) {
            int value = str.empty() ? 0 : std::stoi(str);
            if (value > mMaxValue) {
                str = std::to_string(mMaxValue);
            }
        }
    }

} // namespace GUI