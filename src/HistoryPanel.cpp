#include "HistoryPanel.h"
#include "Button.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "DrawingCanvas.h"

HistoryPanel::HistoryPanel(DrawingCanvas* drawingCanvas,
                           State::Context context,
                           const sf::FloatRect& objectArea)
    : cMaxNumberVisibleTextures(10),
      mDrawingCanvas(drawingCanvas),
      mWindow(*context.window),
  	  mContainer(objectArea.getSize()),
      mButtons(),
      mNumberVisibleTextures(0) {
    mContainer.setPosition(objectArea.getPosition());

    for (int i = 0; i < cMaxNumberVisibleTextures; ++i) {
        GUI::Button::Ptr button(new GUI::Button(context.fonts, context.textures,
                                                Textures::ButtonHistoryPanelNormal,
                                                Textures::ButtonHistoryPanelSelected,
                                                Textures::ButtonHistoryPanelPressed));
        button->setCallback([this, i]() {
            mNumberVisibleTextures = i + 1;
        });
        button->setPosition(11, 5 + i * 63);
        button->setText("History Object " + toString(i));
        button->setToggle(true);
        button->setVisible(false);
        mContainer.pack(button);
        mButtons.push_back(std::move(button));
    }
}

void HistoryPanel::handleEvent(const sf::Event& event) {
	mContainer.handleEvent(event);
}

void HistoryPanel::update() {
}

void HistoryPanel::draw() {
	mWindow.draw(mContainer);
}

void HistoryPanel::drawTextures(sf::RenderTarget& target) {
	for (int i = 0; i < mTexturesHistory.size() && i < mNumberVisibleTextures; ++i) {
        target.draw(sf::Sprite(mTexturesHistory[i]));
	}
}

void HistoryPanel::addTexture(const sf::Texture& texture) {
    // Delete all textures after the current
    mTexturesHistory.erase(mTexturesHistory.begin() + mNumberVisibleTextures, mTexturesHistory.end());
    for (int i = mNumberVisibleTextures; i < cMaxNumberVisibleTextures; ++i) {
		mButtons[i]->setVisible(false);
    }

    // and add the new texture to the end
    mTexturesHistory.push_back(texture);

    if (mNumberVisibleTextures == cMaxNumberVisibleTextures) {
        // Draw the oldest texture to canvas
        drawDirectedToCanvas(mTexturesHistory[0]);
        // and remove it from history panel
        mTexturesHistory.erase(mTexturesHistory.begin());
        --mNumberVisibleTextures;
	}

    ++mNumberVisibleTextures;
    mButtons[mNumberVisibleTextures - 1]->setVisible(true);

	mContainer.activate(mNumberVisibleTextures - 1);
}

void HistoryPanel::drawDirectedToCanvas(const sf::Texture& texture) {
	mDrawingCanvas->mRenderTexturePermanently.draw(sf::Sprite(texture));
	mDrawingCanvas->mRenderTexturePermanently.display();
}