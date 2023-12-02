#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

class Pen;

class DrawingCanvas {
public:
    DrawingCanvas(sf::RenderWindow& window, Pen& pen,
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

private:
	void adaptRenderArea(const sf::Vector2f& renderArea);

private:
	sf::RenderWindow& mWindow;
	sf::FloatRect mObjectArea;

	sf::RenderTexture mRenderTexture;
	sf::Sprite mSprite;

	std::vector<sf::Texture> mTexturesHistory;

	Pen& mPen;
};
