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
      mObjectArea(objectArea),
	  mGUIContainers(),
      mColorDisplayerIndex(),
      mColorDisplayer(),
      mGradientFirstColor(),
	  mGradientSecondColor(),
      mBackground() {
    mBackground.setSize(sf::Vector2f(mObjectArea.width, mObjectArea.height));
    mBackground.setPosition(mObjectArea.left, mObjectArea.top);
    mBackground.setFillColor(sf::Color(255, 255, 255, 15));

	mPen.setCanvas(mMainState->mDrawingCanvas);

    addSizeCategory(context);
    addShapeCategory(context);
	addColorCategory(context);
}

bool ControlTable::handleEvent(const sf::Event& event) {
    for (auto& container : mGUIContainers) {
		if (container->handleEvent(event)) return true;
	}
    return false;
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
	    mPen.setShape(DrawingShapes::Pencil);
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
	// shape: text writing
	buttonShape = GUI::Button::Ptr(new GUI::Button(context.fonts, context.textures,
	                                               Textures::ButtonShapeTextWritingNormal,
	                                               Textures::ButtonShapeTextWritingSelected,
	                                               Textures::ButtonShapeTextWritingPressed));
	buttonShape->setCallback([this]() {
		mPen.setShape(DrawingShapes::TextWriting);
	});
	buttonShape->setPosition(3 + 28 + 28, 3 + 28);
	buttonShape->setToggle(true);
	containerShape->pack(buttonShape);

	/// add shape container to the main container
	mGUIContainers.emplace_back(std::move(container));
}

void ControlTable::addColorCategory(State::Context& context) {
	Pen* pen = context.pen;

	GUI::Container::Ptr container(new GUI::Container(sf::Vector2f(600, 160)));
	container->setPosition(220, 50);

	GUI::Label::Ptr label(new GUI::Label("Colors", mFonts));
	label->setPosition(300, 130);
	container->pack(std::move(label));

	for (int i = 0; i < 3; ++i) {
		mColorDisplayer[i].reset(new GUI::Button(context.fonts, context.textures,
		                                      Textures::CircleWhite30x30,
		                                      Textures::CircleWhite30x30,
		                                      Textures::CircleWhite30x30));
		mColorDisplayer[i]->setCallback([this, i]() {
			mColorDisplayerIndex = i;
		});
		mColorDisplayer[i]->setPosition(25, 20 + 40 * i);
		container->pack(mColorDisplayer[i]);
	}
	mColorDisplayer[2]->activate();
	setColorOfColorDisplayer(sf::Color::White);
	mColorDisplayer[1]->activate();
	setColorOfColorDisplayer(sf::Color::White);
	mColorDisplayer[0]->activate();
	// set color of gradient to white-white
	// and choose displayer 0 (pen color)

	struct MyColor {
		std::string name;
		sf::Color color;
		MyColor(const std::string& name, const sf::Color& color)
		    : name(name), color(color) {}
	};

	// source for 28 colors
	// https://csydes.miraheze.org/wiki/Default_Microsoft_Paint_Fill_Colours_-_95-2003
    std::vector<MyColor> colorList = {
	    MyColor("Black", sf::Color(0, 0, 0)),
	    MyColor("Grey", sf::Color(128, 128, 128)),
	    MyColor("Dark Red", sf::Color(128, 0, 0)),
	    MyColor("Dark Yellow", sf::Color(128, 128, 0)),
	    MyColor("Dark Green", sf::Color(0, 128, 0)),
	    MyColor("Dark Teal", sf::Color(0, 128, 128)),
	    MyColor("Dark Blue", sf::Color(0, 0, 128)),
	    MyColor("Dark Purple", sf::Color(128, 0, 128)),
	    MyColor("Brown", sf::Color(128, 128, 64)),
	    MyColor("Dark Teal", sf::Color(0, 64, 64)),
	    MyColor("Blue", sf::Color(0, 128, 255)),
	    MyColor("Dark Blue", sf::Color(0, 64, 128)),
	    MyColor("Purple", sf::Color(128, 0, 255)),
	    MyColor("Brown", sf::Color(128, 64, 0)),
		MyColor("White", sf::Color(255, 255, 255)),
	    MyColor("Grey", sf::Color(192, 192, 192)),
	    MyColor("Red", sf::Color(255, 0, 0)),
	    MyColor("Yellow", sf::Color(255, 255, 0)),
	    MyColor("Green", sf::Color(0, 255, 0)),
	    MyColor("Aqua", sf::Color(0, 255, 255)),
	    MyColor("Blue", sf::Color(0, 0, 255)),
	    MyColor("Purple", sf::Color(255, 0, 255)),
	    MyColor("Light Yellow", sf::Color(255, 255, 128)),
	    MyColor("Green", sf::Color(0, 255, 128)),
	    MyColor("Sky Blue", sf::Color(128, 255, 255)),
	    MyColor("Light Blue", sf::Color(128, 128, 255)),
	    MyColor("Pink", sf::Color(255, 0, 128)),
	    MyColor("Orange", sf::Color(255, 128, 64)),
	};

	for (size_t i = 0; i < colorList.size(); ++i) {
		MyColor& myColor = colorList[i];

		GUI::Button::Ptr button(new GUI::Button(context.fonts, context.textures,
		                                        Textures::CircleWhite20x20,
		                                        Textures::CircleWhite20x20,
		                                        Textures::CircleWhite20x20));
		button->setCallback([this, myColor]() {
			setColorOfColorDisplayer(myColor.color);
		});
		button->setColor(myColor.color);
		button->setPosition(90 + 30 * (i % 14), 20 + 30 * (i / 14));

		if (i == 0) {
			button->activate();
		}

		container->pack(std::move(button));
    }

	GUI::Button::Ptr buttonEditColor(new GUI::Button(context.fonts, context.textures,
			                                        Textures::ButtonColorEditNormal,
			                                        Textures::ButtonColorEditSelected,
			                                        Textures::ButtonColorEditPressed));
	StateParameter stateParameter;
	stateParameter.colorMenu.callback = [this, pen](sf::Color color) {
		setColorOfColorDisplayer(color);
	};
    buttonEditColor->setCallback([this, stateParameter]() {
		StateParameter parameter = stateParameter;
	    parameter.colorMenu.inputColor = mPen.getColor();
		mMainState->requestStackPush(States::ColorMenu, parameter);
	});
	buttonEditColor->setPosition(520, 40);
	container->pack(std::move(buttonEditColor));

	mGUIContainers.emplace_back(std::move(container));
}

void ControlTable::setColorOfColorDisplayer(sf::Color color) {
	mColorDisplayer[mColorDisplayerIndex]->setColor(color);
	if (mColorDisplayerIndex == 0) {
		mPen.setColor(color);
	}
	else {
		if (mColorDisplayerIndex == 1) {
			mGradientFirstColor = color;
		}
		else if (mColorDisplayerIndex == 2) {
			mGradientSecondColor = color;
		}
		else {
			assert(false);
		}
		// update the gradient color
		mPen.setGradientColor(mGradientFirstColor, mGradientSecondColor);
	}
}