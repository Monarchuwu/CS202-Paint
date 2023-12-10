#include "DrawingCanvas.h"
#include "Pen.h"

DrawingCanvas::DrawingCanvas(State::Context context,
                             const sf::FloatRect& objectArea,
                             const sf::Vector2f& renderArea)
    : mWindow(*(context.window)),
      mObjectArea(objectArea),
      mRenderTexturePermanently(),
      mRenderTexture(),
      mSprite(),
      mDrawingView(sf::FloatRect(objectArea)),
      mZoomFactor(100),
      mHistoryPanel(this, context, sf::FloatRect(1400, objectArea.top, 190, objectArea.height)),
      mPen(*(context.pen)) {
    mRenderTexturePermanently.create(renderArea.x, renderArea.y);
    mRenderTexturePermanently.clear(sf::Color::Transparent);

    mRenderTexture.create(renderArea.x, renderArea.y);
    clear();
    addTexture(mRenderTexture.getTexture());

    mSprite.setTexture(mRenderTexture.getTexture());
    mSprite.setPosition(mObjectArea.left + mObjectArea.width / 2.f,
                        mObjectArea.top + mObjectArea.height / 2.f);
    adaptRenderArea(renderArea);

    sf::FloatRect viewArea = objectArea;
    viewArea.left /= 1600;
    viewArea.top /= 900;
    viewArea.width /= 1600;
    viewArea.height /= 900;
    mDrawingView.setViewport(viewArea);
}

void DrawingCanvas::handleEvent(const sf::Event& event) {
    mPen.handleEvent(event, mDrawingView.getCenter(), mZoomFactor);
    mHistoryPanel.handleEvent(event);
}

void DrawingCanvas::update() {
    //mRenderTexture.display();
}

void DrawingCanvas::draw() {
	mRenderTexture.clear(sf::Color::Transparent);
    mRenderTexture.draw(sf::Sprite(mRenderTexturePermanently.getTexture()));

    mHistoryPanel.drawTextures(mRenderTexture);
	mRenderTexture.display();

    const sf::View currentView = mWindow.getView();
    mWindow.setView(mDrawingView);
    mWindow.draw(mSprite);
	mPen.draw();
    mWindow.setView(currentView);

    mHistoryPanel.draw();
}

void DrawingCanvas::clear(const sf::Color& color) {
	mRenderTexture.clear(color);
}

void DrawingCanvas::setZoom(unsigned int factor) {
	mDrawingView.setSize(mObjectArea.width * 100.f / factor,
	                     mObjectArea.height * 100.f / factor);
    mZoomFactor = factor;
}

void DrawingCanvas::addTexture(const sf::Texture& texture) {
    mHistoryPanel.addTexture(texture);
}

Pen& DrawingCanvas::getPen() {
	return mPen;
}

sf::Vector2f DrawingCanvas::getPositionCanvas() const {
    return mSprite.getPosition() - mSprite.getOrigin();
}

void DrawingCanvas::adaptRenderArea(const sf::Vector2f& renderArea) {
    mSprite.setOrigin(renderArea / 2.f);
}

const sf::FloatRect& DrawingCanvas::getRenderArea() const {
    sf::Vector2f size = (sf::Vector2f)mRenderTexture.getSize();
    return sf::FloatRect(getPositionCanvas(), size);
}