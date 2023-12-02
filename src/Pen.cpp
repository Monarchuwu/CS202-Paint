#include "Pen.h"
#include "DrawingCanvas.h"
#include "DrawingShape.h"
#include "DrawingShapeLinesStrip.h"
#include "DrawingShapeRectangle.h"

Pen::Context::Context(const sf::Color& color, int width)
	: color(color),
	  width(width) {
}

Pen::Pen(const Context& context)
	: mCanvas(nullptr),
	  mContext(context),
	  mDrawingShape(nullptr),
	  mIsDrawing(false) {
}

void Pen::setCanvas(DrawingCanvas& canvas) {
	mCanvas = &canvas;
}

bool Pen::isDrawing() const {
	return mIsDrawing;
}

void Pen::draw() {
	if (mDrawingShape != nullptr) {
		mDrawingShape->draw();
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

void Pen::setShape() {
	if (mDrawingShape != nullptr) {
		delete mDrawingShape;
	}
	mDrawingShape = mDrawingShape = new DrawingShapeRectangle(mCanvas->mWindow, *this,
	                                                          mCanvas->getRenderArea());
	//mDrawingShape = mDrawingShape = new DrawingShapeLinesStrip(mCanvas->mWindow, *this,
	//                                                           mCanvas->getRenderArea());
}