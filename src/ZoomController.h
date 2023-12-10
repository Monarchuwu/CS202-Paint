#pragma once
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "Container.h"
#include "Label.h"

#include <SFML/Graphics.hpp>

class DrawingCanvas;

class ZoomController {
public:
	ZoomController(DrawingCanvas& drawingCanvas,
                   sf::RenderWindow& window,
		           TextureHolder* textures,
		           FontHolder* fonts);

	bool handleEvent(const sf::Event& event);
	void draw();

private:
	void setZoomFactor(unsigned int zoomFactor);

private:
	DrawingCanvas* mDrawingCanvas;
    sf::RenderWindow& mWindow;
	TextureHolder* mTextures;
	FontHolder* mFonts;

	GUI::Container mDisplayZoomFactor;
	GUI::Label::Ptr mZoomFactorLabel;
	GUI::Container mZoomFactorButtons;
};
