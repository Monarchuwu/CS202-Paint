#include "ZoomController.h"
#include "DrawingCanvas.h"
#include "Utility.h"
#include "Button.h"

ZoomController::ZoomController(DrawingCanvas& drawingCanvas,
                               sf::RenderWindow& window,
                               TextureHolder* textures,
                               FontHolder* fonts)
    : mDrawingCanvas(&drawingCanvas),
      mWindow(window),
      mTextures(textures),
      mFonts(fonts),
      mDisplayZoomFactor(sf::Vector2f(105, 36)),
      mZoomFactorButtons(sf::Vector2f(85, 285)) {
    { // set up display zoom factor
        mDisplayZoomFactor.setPosition(1215, 857);

        mZoomFactorLabel = std::make_shared<GUI::Label>("", mFonts);
        mZoomFactorLabel->setPosition(30, 18);
        mDisplayZoomFactor.pack(mZoomFactorLabel);

        GUI::Button::Ptr zoomOptionButton(new GUI::Button(mFonts, mTextures,
														  Textures::ButtonZoomOption,
														  Textures::ButtonZoomOption,
														  Textures::ButtonZoomOption));
        zoomOptionButton->setCallback([this]() {
            mZoomFactorButtons.setVisible(!mZoomFactorButtons.isVisible());
        });
        zoomOptionButton->setPosition(60, 5);
        mDisplayZoomFactor.pack(zoomOptionButton);
    }

    { // set up zoom factor buttons
        mZoomFactorButtons.setPosition(1235, 565);
        // mZoomFactorButtons.setVisible(false);
        std::vector<unsigned int> zoomFactors = { 25, 50, 75, 100, 150, 200, 300 };

        for (int i = 0; i < zoomFactors.size(); ++i) {
			GUI::Button::Ptr zoomFactorButton(new GUI::Button(mFonts, mTextures,
															  Textures::ButtonZoomNormal,
															  Textures::ButtonZoomSelected,
															  Textures::ButtonZoomPressed));
			zoomFactorButton->setCallback([this, factor=zoomFactors[i]]() {
				setZoomFactor(factor);
				mZoomFactorButtons.setVisible(false);
			});
            zoomFactorButton->setText(std::to_string(zoomFactors[i]) + "%");
			zoomFactorButton->setPosition(10, 5 + i * (35 + 5));
			mZoomFactorButtons.pack(zoomFactorButton);
		}
    }

    setZoomFactor(100);
    mZoomFactorButtons.setVisible(false);
}

bool ZoomController::handleEvent(const sf::Event& event) {
    if (mDisplayZoomFactor.handleEvent(event)) return true;
    if (mZoomFactorButtons.handleEvent(event)) return true;
	return false;
}

void ZoomController::draw() {
	mWindow.draw(mDisplayZoomFactor);
    mWindow.draw(mZoomFactorButtons);
}

void ZoomController::setZoomFactor(unsigned int zoomFactor) {
    mDrawingCanvas->setZoom(zoomFactor);
    mZoomFactorLabel->setText(std::to_string(zoomFactor) + "%");
}