#pragma once
#include "Pen.h"

#include <SFML/Graphics.hpp>

class DrawingCanvas {
    friend class Pen;

public:
    DrawingCanvas(sf::RenderWindow& window, Pen& pen,
				  const sf::FloatRect& objectArea,
				  const sf::Vector2f& renderArea);

    void handleEvent(const sf::Event& event);
	void update();
	void draw();
	void clear(const sf::Color& color = sf::Color(255, 255, 255, 255));

	Pen& getPen();

private:
	sf::Vector2f getPositionCanvas() const;
	void adaptRenderArea(const sf::Vector2f& renderArea);
	const sf::FloatRect& getRenderArea() const;

private:
	sf::RenderWindow& mWindow;
	sf::FloatRect mObjectArea;

	sf::RenderTexture mRenderTexture;
	sf::Sprite mSprite;

	Pen& mPen;
};
