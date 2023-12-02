#include "ControlTable.h"
#include "ContainerOneActivate.h"
#include "Label.h"
#include "Button.h"
#include "ResourceIdentifiers.h"
#include "DrawingShapeIdentifiers.h"
#include "MainState.h"

ControlTable::ControlTable(MainState* mainState,
                           State::Context context, Pen& pen,
                           const sf::FloatRect& objectArea)
    : mMainState(mainState),
      mWindow(*(context.window)),
      mTextures(context.textures),
      mFonts(context.fonts),
      mPen(pen),
      mObjectArea(objectArea) {
    mBackground.setSize(sf::Vector2f(mObjectArea.width, mObjectArea.height));
    mBackground.setPosition(mObjectArea.left, mObjectArea.top);
    mBackground.setFillColor(sf::Color(255, 255, 255, 15));

	mPen.setCanvas(mMainState->mDrawingCanvas);

    addSizeCategory(context);
    addShapeCategory(context);
}

void ControlTable::handleEvent(const sf::Event& event) {
    for (auto& container : mGUIContainers) {
		container->handleEvent(event);
	}
}

void ControlTable::update() {
}

void ControlTable::draw() {
	mWindow.draw(mBackground);

    for (auto& container : mGUIContainers) {
		mWindow.draw(*container);
	}
}

void ControlTable::addSizeCategory(State::Context& context) {
	GUI::Container::Ptr container(new GUI::Container(sf::Vector2f(70, 160)));
	container->setPosition(10, 50);

	GUI::Label::Ptr label(new GUI::Label("Size", mFonts));
	label->setPosition(35, 130);
	container->pack(label);

	GUI::Button::Ptr button(new GUI::Button(context.fonts, context.textures,
	                                        Textures::ButtonSizeNormal,
	                                        Textures::ButtonSizeSelected,
	                                        Textures::ButtonSizePressed));

	button->setCallback([this]() {
	    mMainState->requestStackPush(States::SizeMenu);
	});
	button->setPosition(15, 35);
	container->pack(button);

	mGUIContainers.emplace_back(std::move(container));
}

void ControlTable::addShapeCategory(State::Context& context) {
	// main container
	GUI::Container::Ptr container(new GUI::Container(sf::Vector2f(120, 160)));
	container->setPosition(90, 50);

	// label of the main container
	GUI::Label::Ptr label(new GUI::Label("Shapes", mFonts));
	label->setPosition(60, 135);
	container->pack(label);

	// shape container
	GUI::Container::Ptr containerShape(new GUI::ContainerOneActivate(sf::Vector2f(90, 90)));
	containerShape->setPosition(15, 20);
	container->pack(containerShape);

	/// add all shapes and activate the first one
	GUI::Button::Ptr buttonShape;
	// shape: lines strip
	buttonShape = GUI::Button::Ptr(new GUI::Button(context.fonts, context.textures,
	                                               Textures::ButtonShapeLinesStripNormal,
	                                               Textures::ButtonShapeLinesStripSelected,
	                                               Textures::ButtonShapeLinesStripPressed));
	buttonShape->setCallback([this]() {
	    mPen.setShape(DrawingShapes::LinesStrip);
	});
	buttonShape->setPosition(3, 3);
	buttonShape->setToggle(true);
	buttonShape->activate(); // ACTIVATE THE FIRST SHAPE
	containerShape->pack(buttonShape);
	// shape: line
	buttonShape = GUI::Button::Ptr(new GUI::Button(context.fonts, context.textures,
			                                               Textures::ButtonShapeLineNormal,
			                                               Textures::ButtonShapeLineSelected,
			                                               Textures::ButtonShapeLinePressed));
	buttonShape->setCallback([this]() {
		mPen.setShape(DrawingShapes::Line);
	});
	buttonShape->setPosition(3, 3 + 28);
	buttonShape->setToggle(true);
	containerShape->pack(buttonShape);
	// shape: rectangle
	buttonShape = GUI::Button::Ptr(new GUI::Button(context.fonts, context.textures,
					                                               Textures::ButtonShapeRectangleNormal,
					                                               Textures::ButtonShapeRectangleSelected,
					                                               Textures::ButtonShapeRectanglePressed));
	buttonShape->setCallback([this]() {
		mPen.setShape(DrawingShapes::Rectangle);
	});
	buttonShape->setPosition(3, 3 + 28 + 28);
	buttonShape->setToggle(true);
	containerShape->pack(buttonShape);
	// shape: oval
	buttonShape = GUI::Button::Ptr(new GUI::Button(context.fonts, context.textures,
							                                               Textures::ButtonShapeOvalNormal,
							                                               Textures::ButtonShapeOvalSelected,
							                                               Textures::ButtonShapeOvalPressed));
	buttonShape->setCallback([this]() {
		mPen.setShape(DrawingShapes::Oval);
	});
	buttonShape->setPosition(3 + 28, 3);
	buttonShape->setToggle(true);
	containerShape->pack(buttonShape);
	// shape: triangle
	buttonShape = GUI::Button::Ptr(new GUI::Button(context.fonts, context.textures,
	                                               Textures::ButtonShapeTriangleNormal,
	                                               Textures::ButtonShapeTriangleSelected,
	                                               Textures::ButtonShapeTrianglePressed));
	buttonShape->setCallback([this]() {
	    mPen.setShape(DrawingShapes::Triangle);
	});
	buttonShape->setPosition(3 + 28, 3 + 28);
	buttonShape->setToggle(true);
	containerShape->pack(buttonShape);
	// shape: right triangle
	buttonShape = GUI::Button::Ptr(new GUI::Button(context.fonts, context.textures,
	                                               Textures::ButtonShapeRightTriangleNormal,
	                                               Textures::ButtonShapeRightTriangleSelected,
	                                               Textures::ButtonShapeRightTrianglePressed));
	buttonShape->setCallback([this]() {
	    mPen.setShape(DrawingShapes::RightTriangle);
	});
	buttonShape->setPosition(3 + 28, 3 + 28 + 28);
	buttonShape->setToggle(true);
	containerShape->pack(buttonShape);
	// shape: diamond
	buttonShape = GUI::Button::Ptr(new GUI::Button(context.fonts, context.textures,
											                                               Textures::ButtonShapeDiamondNormal,
											                                               Textures::ButtonShapeDiamondSelected,
											                                               Textures::ButtonShapeDiamondPressed));
	buttonShape->setCallback([this]() {
		mPen.setShape(DrawingShapes::Diamond);
	});
	buttonShape->setPosition(3 + 28 + 28, 3);
	buttonShape->setToggle(true);
	containerShape->pack(buttonShape);

	/// add shape container to the main container
	mGUIContainers.emplace_back(std::move(container));
}