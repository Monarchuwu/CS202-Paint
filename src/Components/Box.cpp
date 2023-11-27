#include "Box.h"

Box::Box(const sf::Vector2f& size)
    : sf::RectangleShape(size),
	  mIsAlignCenter(false) {}

void Box::setFont(const sf::Font& font) {
	mFont = &font;
    mText.setFont(*mFont);
}

void Box::setText(const std::string& text) {
    mString = text;
    displayText();
}

const std::string& Box::getText() const {
	return mString;
}

void Box::addChar(const sf::Uint32& c) {
	if (c == ' ' && (mString.empty() || mString.back() == ' ')) return;
	mString += c;
	displayText();
}

void Box::removeChar() {
	if (mString.size() > 0) {
		mString.pop_back();
	    displayText();
	}
}

void Box::setStyle(sf::Uint32 style) {
	mText.setStyle(style);
	setTextPosition();
}

void Box::setCharacterSize(unsigned int size) {
	mText.setCharacterSize(size);
	setTextPosition();
}

void Box::setTextColor(const sf::Color& color) {
	mText.setFillColor(color);
}

void Box::setAlignCenter(bool alignCenter) {
	mIsAlignCenter = alignCenter;
	setTextPosition();
}

bool Box::getAlignCenter() const {
	return mIsAlignCenter;
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(static_cast<sf::RectangleShape>(*this), states);
	states.transform *= getTransform();
	target.draw(mText, states);
}

bool Box::isContain(sf::Vector2f point) const {
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
bool Box::isContain(float x, float y) const {
	return isContain(sf::Vector2f(x, y));
}

void Box::displayText() {
	mText.setString(mString);
	int* pos = new int[mString.size() + 2];
	for (int i = 0; i <= mString.size() + 1; ++i) {
	    pos[i] = mText.findCharacterPos(i).x;
	}

	std::string displayString = "";
	std::string currentLine   = "";
	std::string currentWord   = "";
	int lenLine               = 0;
	int startWord             = 0;

	for (int i = 0; i <= mString.size(); ++i) {
		if (mString[i] == ' ' || i == mString.size()) {
			// if current word is empty
			// then it is not neecessary to add it to current line
	        if (!currentWord.empty()) {
	            // add current word to current line if possible
	            if (lenLine + (pos[i + 1] - pos[startWord]) <= getSize().x - 20) {
	                if (!currentLine.empty()) {
	                    currentLine += ' ' + currentWord;
	                    lenLine += pos[i + 1] - pos[startWord];
	                }
	                else {
	                    currentLine += currentWord;
	                    lenLine += pos[i] - pos[startWord];
	                }
	                currentWord = "";
	                startWord   = i + 1;
	            }
	            // add current line to display string
	            // if cannot add current word to current line
	            if (!currentWord.empty()) {
	                if (!currentLine.empty()) {
	                    if (!displayString.empty()) displayString += '\n';
	                    displayString += currentLine;
	                }
	                currentLine = currentWord;
	                lenLine     = pos[i] - pos[startWord];
	                currentWord = "";
	                startWord   = i + 1;
	            }
	        }
			// add current line to display string
			// if current word is the last word
			if (i == mString.size()) {
				if (!displayString.empty()) displayString += '\n';
				displayString += currentLine;
			}
		}
		else currentWord += mString[i];
	}

	delete[] pos;
	mText.setString(displayString);
	setTextPosition();
}
void Box::setTextPosition() {
	sf::FloatRect textRect = mText.getLocalBounds();
	if (mIsAlignCenter) {
		mText.setPosition(getSize().x / 2 - textRect.width / 2 - textRect.left,
						getSize().y / 2 - textRect.height / 2 - textRect.top);
	}
	else {
		mText.setPosition(10, getSize().y / 2 - textRect.height / 2 - textRect.top);
	}
}