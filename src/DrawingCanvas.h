#pragma once
#include "Pen.h"

#include <SFML/Graphics.hpp>

class DrawingCanvas {
    friend class Pen;

public:
    DrawingCanvas(sf::RenderWindow& window,
				  const sf::FloatRect& objectArea,
				  const sf::Vector2f& renderArea);
	~DrawingCanvas();

    void handleEvent(const sf::Event& event);
	void update();
	void draw();
	void clear(const sf::Color& color = sf::Color(255, 255, 255, 255));

	Pen& getPen();

private:
	sf::Vector2f getPositionCanvas() const;
	void adaptRenderArea(const sf::Vector2f& renderArea);

private:
	sf::RenderWindow& mWindow;
	sf::FloatRect mObjectArea;

	sf::RenderTexture mRenderTexture;
	sf::Sprite mSprite;

	Pen* mPen;
};
