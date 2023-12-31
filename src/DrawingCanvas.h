#pragma once
#include "State.h"
#include "HistoryPanel.h"

#include <SFML/Graphics.hpp>

#include <vector>

class Pen;

class DrawingCanvas {
public:
    DrawingCanvas(State::Context context,
				  const sf::FloatRect& objectArea,
				  const sf::Vector2f& renderArea);

    bool handleEvent(const sf::Event& event);
	void update();
	void draw();
	void clear(const sf::Color& color = sf::Color::White);
	// percentage (factor = 100 -> zoom ratio = 100%)
	void setZoom(unsigned int factor);

	void addTexture(const sf::Texture& texture);

	Pen& getPen();

	sf::Vector2f getPositionCanvas() const;
	const sf::FloatRect& getRenderArea() const;
	const sf::FloatRect& getObjectArea() const;

	const sf::Texture& getCanvasDisplay() const;

	friend void HistoryPanel::drawDirectedToCanvas(const sf::Texture& texture);

private:
	void adaptRenderArea(const sf::Vector2f& renderArea);

private:
	sf::RenderWindow& mWindow;
	sf::FloatRect mObjectArea;

	sf::RenderTexture mRenderTexturePermanently;
	sf::RenderTexture mRenderTexture;
	sf::Sprite mSprite;

	sf::View mDrawingView;
	unsigned int mZoomFactor;

	HistoryPanel mHistoryPanel;

	Pen& mPen;
};
