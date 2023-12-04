#include <array>
#include <cmath>

template<std::size_t N>
DrawingShapeOvalTemplate<N>::DrawingShapeOvalTemplate<N>(Pen& pen,
                                                         const sf::FloatRect& renderArea)
    : DrawingShapeLineStrip(pen, renderArea),
      mStartPosition(),
      mCurrentPosition() {
}

template<std::size_t N>
void DrawingShapeOvalTemplate<N>::startDrawing(const sf::Vector2f& position) {
    resetBoundingBox(position);
    mStartPosition = position;
    clear();
}

template<std::size_t N>
void DrawingShapeOvalTemplate<N>::stopDrawing() {
    updateBoundingBox(mCurrentPosition);
}

template<std::size_t N>
void DrawingShapeOvalTemplate<N>::move(const sf::Vector2f& position) {
    // clear the render texture to draw a new shape
    clear();

    int minX = std::min(mStartPosition.x, position.x);
    int minY = std::min(mStartPosition.y, position.y);
    int maxX = std::max(mStartPosition.x, position.x);
    int maxY = std::max(mStartPosition.y, position.y);
    drawOval(minX, minY, maxX, maxY);

    mCurrentPosition = position;
}

template<std::size_t N>
void DrawingShapeOvalTemplate<N>::drawOval(int minX, int minY, int maxX, int maxY) {
    float pi      = acos(-1);
    float radiusX = (maxX - minX) / 2;
    float radiusY = (maxY - minY) / 2;
    float centerX = (maxX + minX) / 2;
    float centerY = (maxY + minY) / 2;

    std::vector<sf::Vector2f> points(N + 1);
    for (int i = 0; i < N; ++i) {
        points[i].x = centerX + radiusX * cos(2 * pi * i / N - pi / 2);
        points[i].y = centerY + radiusY * sin(2 * pi * i / N - pi / 2);
    }
    points[N] = points[0];

    drawLineStrip(points);
}