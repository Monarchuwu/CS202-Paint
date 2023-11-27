#include "ButtonSprite.h"

ButtonSprite::ButtonSprite() {
    mTexture = nullptr;
}

ButtonSprite::ButtonSprite(const sf::Texture* texture) {
    setTexture(texture);
}

void ButtonSprite::setTexture(const sf::Texture* texture) {
	mTexture = texture;
    sf::Sprite::setTexture(*mTexture);
}

const sf::Texture* ButtonSprite::getTexture() const {
	return mTexture;
}

bool ButtonSprite::isContain(sf::Vector2f point) const {
	point -= getPosition();
	sf::Transformable transform;
	transform.rotate(-getRotation());
	point = transform.getTransform().transformPoint(point);

	sf::FloatRect rect = getLocalBounds();
	sf::Transformable transform2;
	transform2.setScale(getScale());
	rect = transform2.getTransform().transformRect(rect);

	return rect.contains(point);
}
bool ButtonSprite::isContain(float x, float y) const {
	return isContain(sf::Vector2f(x, y));
}