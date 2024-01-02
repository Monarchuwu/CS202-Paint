#pragma once
#include "InputBox.h"

namespace GUI {

    class DecimalInputBox : public InputBox {
    public:
        typedef std::shared_ptr<DecimalInputBox> Ptr;

    public:
        DecimalInputBox(const FontHolder* fonts,
                        const TextureHolder* textures,
                        Textures::ID boxNormal,
                        Textures::ID boxSelected,
                        Textures::ID boxPressed);

        void setMinValue(int minValue);
        void setMaxValue(int maxValue);

    protected:
        virtual void lowerBoundText(std::string& str);
        virtual void upperBoundText(std::string& str);

    private:
        int mMinValue;
		int mMaxValue;
        bool mSetMinValue;
        bool mSetMaxValue;
    };

} // namespace GUI
