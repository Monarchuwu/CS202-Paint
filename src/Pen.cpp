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

bool Pen::isDrawing() const {
	return mDrawingStatus != PenStatus::WAIT_TO_DRAW;
}

void Pen::handleEvent(const sf::Event& event) {
	assert(mCanvas != nullptr);

	switch (mDrawingStatus) {
	    case PenStatus::WAIT_TO_DRAW: {
	        if (event.type == sf::Event::MouseButtonPressed) {
	            if (event.mouseButton.button == sf::Mouse::Left) {
	                sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
	                sf::FloatRect renderArea = mCanvas->getRenderArea();
	                if (renderArea.contains(mousePosition)) {
	                    startDrawing(mousePosition - renderArea.getPosition());
	                    mDrawingStatus = PenStatus::DRAWING;
	                }
	            }
	        }
	        break;
		}

		case PenStatus::DRAWING: {
	        if (event.type == sf::Event::MouseButtonReleased) {
	            if (event.mouseButton.button == sf::Mouse::Left) {
	                stopDrawing();
	                mDrawingStatus = PenStatus::DRAWED;
	            }
	        }
	        else if (event.type == sf::Event::MouseMoved) {
	            move(sf::Vector2f(event.mouseMove.x, event.mouseMove.y) - mCanvas->getPositionCanvas());
	        }
	        break;
		}

		case PenStatus::DRAWED: {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
	                sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
	                sf::FloatRect renderArea = mCanvas->getRenderArea();
					if (renderArea.contains(mousePosition)) {
						sf::FloatRect boundingBox = mDrawingShape->getBoundingBox();
						if (!boundingBox.contains(mousePosition)) {
						    mCanvas->addTexture(mDrawingShape->getCanvas());
						    mDrawingStatus = PenStatus::WAIT_TO_DRAW;
						    break;
	                    }
	                }
	            }
	        }
			mDrawingShape->handleEvent(event);
	        break;
		}
	}
}

void Pen::draw() {
	if (mDrawingShape == nullptr) return;

	switch (mDrawingStatus) {
		case PenStatus::WAIT_TO_DRAW: {
	        break;
		}

		case PenStatus::DRAWING: {
	        mDrawingShape->draw(mWindow);
	        break;
		}

		case PenStatus::DRAWED: {
	        mDrawingShape->draw(mWindow);
	        mDrawingShape->drawBoundingBox(mWindow);
	        break;
		}
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

	mDrawingStatus = PenStatus::WAIT_TO_DRAW;
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
