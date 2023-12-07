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

#include <cassert>

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
      mDrawingShape(nullptr) {
    registerShape<DrawingShapePencil>(DrawingShapes::Pencil);
    registerShape<DrawingShapeLine>(DrawingShapes::Line);
    registerShape<DrawingShapeRectangle>(DrawingShapes::Rectangle);
    registerShape<DrawingShapeOval>(DrawingShapes::Oval);
    registerShape<DrawingShapeTriangle>(DrawingShapes::Triangle);
    registerShape<DrawingShapeRightTriangle>(DrawingShapes::RightTriangle);
    registerShape<DrawingShapeDiamond>(DrawingShapes::Diamond);
    registerShapeTextWriting<DrawingShapeTextWriting>(DrawingShapes::TextWriting);
}

void Pen::setCanvas(DrawingCanvas& canvas) {
	mCanvas = &canvas;
}

const sf::FloatRect& Pen::getDrawingArea() const {
	assert(mCanvas != nullptr);

	return mCanvas->getRenderArea();
}

void Pen::addTexture(const sf::Texture& texture) {
	assert(mCanvas != nullptr);

	mCanvas->addTexture(texture);
}

void Pen::handleEvent(const sf::Event& event) {
	assert(mCanvas != nullptr);
	assert(mDrawingShape != nullptr);

	mDrawingShape->handleEvent(event);
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
