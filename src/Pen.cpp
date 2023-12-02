#include "Pen.h"
#include "DrawingShape.h"
#include "DrawingShapeLinesStrip.h"
#include "DrawingShapeLine.h"
#include "DrawingShapeRectangle.h"
#include "DrawingShapeOval.h"
#include "DrawingShapeTriangle.h"
#include "DrawingShapeRightTriangle.h"
#include "DrawingShapeDiamond.h"

#include <cassert>

Pen::Context::Context(const sf::Color& color, int width)
	: color(color),
	  width(width) {
}

Pen::Pen(const Context& context)
	: mCanvas(nullptr),
	  mContext(context),
	  mDrawingShape(nullptr),
	  mIsDrawing(false) {
	registerShape<DrawingShapeLinesStrip>(DrawingShapes::LinesStrip);
    registerShape<DrawingShapeLine>(DrawingShapes::Line);
    registerShape<DrawingShapeRectangle>(DrawingShapes::Rectangle);
    registerShape<DrawingShapeOval>(DrawingShapes::Oval);
    registerShape<DrawingShapeTriangle>(DrawingShapes::Triangle);
    registerShape<DrawingShapeRightTriangle>(DrawingShapes::RightTriangle);
    registerShape<DrawingShapeDiamond>(DrawingShapes::Diamond);
}

void Pen::setCanvas(DrawingCanvas& canvas) {
	mCanvas = &canvas;
}

bool Pen::isDrawing() const {
	return mIsDrawing;
}

void Pen::draw() {
	if (mDrawingShape != nullptr) {
		mDrawingShape->draw(mCanvas->mWindow);
	}
}

void Pen::startDrawing(const sf::Vector2f& position) {
	mIsDrawing = true;
	mDrawingShape->startDrawing(position);
}

void Pen::stopDrawing() {
	mIsDrawing = false;
	mDrawingShape->stopDrawing();

	mCanvas->mRenderTexture.draw(sf::Sprite(mDrawingShape->getCanvas()));
}

void Pen::move(const sf::Vector2f& position) {
	if (mIsDrawing) {
	    mDrawingShape->move(position);
	}
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