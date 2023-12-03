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

    void handleEvent(const sf::Event& event);
	void update();
	void draw();
	void clear(const sf::Color& color = sf::Color::White);

	void addTexture(const sf::Texture& texture);

	Pen& getPen();

	sf::Vector2f getPositionCanvas() const;
	const sf::FloatRect& getRenderArea() const;

	friend void HistoryPanel::drawDirectedToCanvas(const sf::Texture& texture);

private:
	void adaptRenderArea(const sf::Vector2f& renderArea);

private:
	sf::RenderWindow& mWindow;
	sf::FloatRect mObjectArea;

	sf::RenderTexture mRenderTexturePermanently;
	sf::RenderTexture mRenderTexture;
	sf::Sprite mSprite;

	HistoryPanel mHistoryPanel;

	Pen& mPen;
};
