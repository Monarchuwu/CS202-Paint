#include "Pen.h"
#include "DrawingShape.h"
#include "DrawingShapePencil.h"
#include "DrawingShapeLine.h"
#include "DrawingShapeRectangle.h"
#include "DrawingShapeOval.h"
#include "DrawingShapeTriangle.h"
#include "DrawingShapeRightTriangle.h"
#include "DrawingShapeDiamond.h"
#include "DrawingShapeTextWriting.h"
#include "DrawingFill.h"

#include <cassert>

template<>
void Pen::registerShape<DrawingShapeTextWriting>(DrawingShapes::ID shapeID) {
    mShapeFactories[shapeID] = [this]() {
        return new DrawingShapeTextWriting(*this, mTextures, mFonts, mCanvas->getRenderArea());
    };
}
Pen::Context::Context(const sf::Color& color, int width)
	: color(color),
	  width(width) {
}

Pen::Pen(sf::RenderWindow& window,
         TextureHolder* textures,
         FontHolder* fonts,
         const Context& context)
    : mWindow(window),
      mTextures(textures),
      mFonts(fonts),
      mCanvas(nullptr),
      mContext(context),
      mGradientTexture(),
      mDrawingShape(nullptr) {
    registerShape<DrawingShapePencil>(DrawingShapes::Pencil);
    registerShape<DrawingShapeLine>(DrawingShapes::Line);
    registerShape<DrawingShapeRectangle>(DrawingShapes::Rectangle);
    registerShape<DrawingShapeOval>(DrawingShapes::Oval);
    registerShape<DrawingShapeTriangle>(DrawingShapes::Triangle);
    registerShape<DrawingShapeRightTriangle>(DrawingShapes::RightTriangle);
    registerShape<DrawingShapeDiamond>(DrawingShapes::Diamond);
    registerShape<DrawingShapeTextWriting>(DrawingShapes::TextWriting);
    registerShape<DrawingFill>(DrawingShapes::Fill);
}

void Pen::setCanvas(DrawingCanvas& canvas) {
	mCanvas = &canvas;
}

const DrawingCanvas& Pen::getCanvas() const {
	assert(mCanvas != nullptr);
	return *mCanvas;
}

const sf::FloatRect& Pen::getDrawingArea() const {
	assert(mCanvas != nullptr);

	return mCanvas->getRenderArea();
}

const sf::FloatRect& Pen::getDisplayArea() const {
	assert(mCanvas != nullptr);

	return mCanvas->getObjectArea();
}

void Pen::addTexture(const sf::Texture& texture) {
	assert(mCanvas != nullptr);

	mCanvas->addTexture(texture);
}

bool Pen::handleEvent(const sf::Event& event, const sf::Vector2f& drawingCenter, unsigned int zoomFactor) {
	assert(mCanvas != nullptr);
	assert(mDrawingShape != nullptr);

	if (mDrawingShape->handleEvent(event, drawingCenter, zoomFactor)) return true;
	return false;
}

void Pen::draw() {
	assert(mDrawingShape != nullptr);

	mDrawingShape->drawToWindow(mWindow);
}

void Pen::setWidth(int width) {
	mContext.width = width;
}

int Pen::getWidth() const {
	return mContext.width;
}

void Pen::setColor(const sf::Color& color) {
	mContext.color = color;
}

const sf::Color& Pen::getColor() const {
	return mContext.color;
}

void Pen::setGradientColor(const sf::Color& firstColor, const sf::Color& secondColor) {
	int WIDTH = 256;
	int r1 = firstColor.r;
	int g1 = firstColor.g;
	int b1 = firstColor.b;
	int r2 = secondColor.r;
	int g2 = secondColor.g;
	int b2 = secondColor.b;

	sf::Image image;
	image.create(256, 1);
	for (int i = 0; i < WIDTH; ++i) {
	    sf::Color c;
		c.r = static_cast<sf::Uint8>(r1 + (r2 - r1) * i / (WIDTH - 1));
		c.g = static_cast<sf::Uint8>(g1 + (g2 - g1) * i / (WIDTH - 1));
		c.b = static_cast<sf::Uint8>(b1 + (b2 - b1) * i / (WIDTH - 1));
		image.setPixel(i, 0, c);
	}
	mGradientTexture.loadFromImage(image);
}

const sf::Texture& Pen::getGradientTexture() const {
	return mGradientTexture;
}

void Pen::setShape(DrawingShapes::ID shapeID) {
	if (mDrawingShape != nullptr) {
	    delete mDrawingShape;
	}
	mDrawingShape = createShape(shapeID);
}

DrawingShape* Pen::createShape(DrawingShapes::ID shapeID) {
	auto found = mShapeFactories.find(shapeID);
	assert(found != mShapeFactories.end());
	return found->second();
}

void Pen::startDrawing(const sf::Vector2f& position) {
	mDrawingShape->startDrawing(position);
}

void Pen::stopDrawing() {
	mDrawingShape->stopDrawing();
}

void Pen::move(const sf::Vector2f& position) {
	mDrawingShape->move(position);
}
