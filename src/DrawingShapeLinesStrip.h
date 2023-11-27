#pragma once
#include "DrawingShape.h"
#include "Pen.h"

class DrawingShapeLinesStrip : public DrawingShape {
public:
    DrawingShapeLinesStrip(const sf::Vector2f& size,
						   const sf::Vector2f& startingPosition,
						   const Pen::Context& context);

	virtual void draw();
	virtual void mouseMove(const sf::Vector2f& move);

private:
	void drawLine(const sf::Vector2f& from, const sf::Vector2f& to);

private:
	sf::Vector2f mCurrentPosition;
	const Pen::Context& mContext;

	sf::RectangleShape mRectangleShape;
	sf::CircleShape mCircleShape;
};
