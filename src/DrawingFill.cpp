#include "DrawingFill.h"

#include <queue>

DrawingFill::DrawingFill(Pen& pen, TextureHolder* textures,
                         const sf::FloatRect& renderArea)
    : DrawingShape(pen, textures, renderArea),
      mPen(pen) {
    turnStatusDRAWING(false);
    turnStatusDRAWED(false);
}

void DrawingFill::startDrawing(const sf::Vector2f& position) {
    // the current canvas -> BFS on image
    sf::Image image = mPen.getCanvas().getCanvasDisplay().copyToImage();
    // WIDTH and HEIGHT
    int WIDTH = image.getSize().x;
    int HEIGHT = image.getSize().y;
    // store the result of the bfs in a new image
    sf::Image imageResult;
    imageResult.create(WIDTH, HEIGHT, sf::Color::Transparent);

    // colorBFS and colorDelete are created to serve the BFS algorithm
    sf::Color colorBFS = image.getPixel(position.x, position.y);
    sf::Color colorDelete = colorBFS;
    --colorDelete.r; // to be sure that colorDelete is different from colorBFS
    sf::Color colorPen = mPen.getColor();

    std::queue<sf::Vector2i> q;
    image.setPixel(position.x, position.y, colorDelete);
    imageResult.setPixel(position.x, position.y, colorPen);
    q.push(sf::Vector2i(position.x, position.y));

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    while (!q.empty()) {
        sf::Vector2i pos = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int x = pos.x + dx[i];
            int y = pos.y + dy[i];
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT
                && image.getPixel(x, y) == colorBFS) {
                image.setPixel(x, y, colorDelete);
                imageResult.setPixel(x, y, colorPen);
                q.push(sf::Vector2i(x, y));
            }
        }
    }

    // draw the result of the BFS on the renderTexture
    clear();
    sf::Texture texture;
    texture.loadFromImage(imageResult);
    mRenderTexture.draw(sf::Sprite(texture));
}

void DrawingFill::stopDrawing() {
    // nothing to do
}

void DrawingFill::move(const sf::Vector2f& position) {
    // nothing to do
}
