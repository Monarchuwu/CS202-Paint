#pragma once
#include "ContainerOneActivate.h"
#include "Button.h"
#include "State.h"

#include <SFML/Graphics.hpp>

#include <vector>

class DrawingCanvas;

class HistoryPanel {
	friend class DrawingCanvas;

public:
    HistoryPanel(DrawingCanvas* drawingCanvas,
				 State::Context context,
                 const sf::FloatRect& objectArea);

	void handleEvent(const sf::Event& event);
	void update();
	void draw();
	void drawTextures(sf::RenderTarget& target);

	void addTexture(const sf::Texture& texture);

private:
	void drawDirectedToCanvas(const sf::Texture& texture);
 
private:
	const size_t cMaxNumberVisibleTextures;

	DrawingCanvas* mDrawingCanvas;
	sf::RenderWindow& mWindow;

	std::vector<sf::Texture> mTexturesHistory;
	GUI::ContainerOneActivate mContainer;
	std::vector<GUI::Button::Ptr> mButtons;

	size_t mNumberVisibleTextures;
};