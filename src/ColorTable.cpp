#include "ColorTable.h"

#include <cassert>

ColorTable::ColorTable(ColorEditingCenter* center, const sf::FloatRect& objectArea)
    : mCenter(center),
      mObjectArea(objectArea),
      mImage(),
      mTexture(),
      mSprite(),
      mSelectedCircle(5),
      mIsHold(false) {
    memset(mCoordTable, -1, sizeof(mCoordTable));
    mImage.create(255 * 6, 256);

    int dr[7] = { 0, -1, 0, 0, 1, 0 };
    int dg[7] = { 1, 0, 0, -1, 0, 0 };
    int db[7] = { 0, 0, 1, 0, 0, -1 };
    for (int j = 0, r = 255, g = 0, b = 0; j < 255 * 6; ++j) {
        buildColumnColorTable(j, sf::Color(r, g, b));
        r += dr[j / 255];
        g += dg[j / 255];
        b += db[j / 255];
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 256; ++j) {
            if (i == 1 && j == 255) continue;
            if (i == 2 && j == 255) continue;
            for (int k = 0; k < 256; ++k) {
                if (i == 2 && k == 255) continue;
                assert(mCoordTable[i][j][k].x != -1);
            }
        }
    }

    mTexture.loadFromImage(mImage);

    mSprite.setTexture(mTexture);
    mSprite.setScale(objectArea.width / mTexture.getSize().x, objectArea.height / mTexture.getSize().y);
    mSprite.setPosition(objectArea.getPosition());

    mSelectedCircle.setFillColor(sf::Color::Transparent);
    mSelectedCircle.setOutlineColor(sf::Color::Black);
    mSelectedCircle.setOutlineThickness(2);
    mSelectedCircle.setOrigin(5, 5);
}

void ColorTable::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
			mIsHold = false;
		}
	}

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
			if (mSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                mIsHold = true;
                int x   = (event.mouseButton.x - mSprite.getPosition().x) / mSprite.getScale().x;
                int y   = (event.mouseButton.y - mSprite.getPosition().y) / mSprite.getScale().y;
                mCenter->updateActualColor(mImage.getPixel(x, y));
			}
        }
    }

    if (event.type == sf::Event::MouseMoved) {
        if (mIsHold) {
            if (mSprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                int x = (event.mouseMove.x - mSprite.getPosition().x) / mSprite.getScale().x;
				int y = (event.mouseMove.y - mSprite.getPosition().y) / mSprite.getScale().y;
                mCenter->updateActualColor(mImage.getPixel(x, y));
			}
		}
	}
}

void ColorTable::draw(sf::RenderTarget& target) const {
	target.draw(mSprite);
	target.draw(mSelectedCircle);
}

void ColorTable::updateSelectedColor(sf::Color color) {
    int mx = std::max({ color.r, color.g, color.b });
    if (mx == color.r) {
        selectPosition(mCoordTable[0][color.g][color.b]);
    }
    else if (mx == color.g) {
		selectPosition(mCoordTable[1][color.r][color.b]);
	}
    else if (mx == color.b) {
		selectPosition(mCoordTable[2][color.r][color.g]);
	}
}

void ColorTable::buildColumnColorTable(int column, sf::Color color) {
    for (int i = 0; i < 256; ++i) {
        sf::Color c = color;
        c.r += (255.f - c.r) * i / 255;
        c.g += (255.f - c.g) * i / 255;
        c.b += (255.f - c.b) * i / 255;
        mImage.setPixel(column, i, c);

        if (c.r == 255) {
            mCoordTable[0][c.g][c.b] = sf::Vector2i(column, i);
        }
        else if (c.g == 255) {
            mCoordTable[1][c.r][c.b] = sf::Vector2i(column, i);
        }
        else if (c.b == 255) {
            mCoordTable[2][c.r][c.g] = sf::Vector2i(column, i);
        }
    }
}

void ColorTable::selectPosition(sf::Vector2i position) {
    int x = position.x * mSprite.getScale().x + mSprite.getPosition().x;
    int y = position.y * mSprite.getScale().y + mSprite.getPosition().y;
    mSelectedCircle.setPosition(x, y);
}