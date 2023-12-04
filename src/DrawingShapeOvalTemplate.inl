#include <array>
#include <cmath>

template<std::size_t N>
DrawingShapeOvalTemplate<N>::DrawingShapeOvalTemplate<N>(Pen& pen,
                                                         const sf::FloatRect& renderArea)
    : DrawingShape(pen, renderArea),
      mPen(pen),
      mStartPosition(),
      mCurrentPosition(),
      mRectangleShape(),
      mCircleShape() {
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
    int penWidth              = mPen.getWidth();
    const sf::Color& penColor = mPen.getColor();

    float pi      = acos(-1);
    float radiusX = (maxX - minX) / 2;
    float radiusY = (maxY - minY) / 2;
    float centerX = (maxX + minX) / 2;
    float centerY = (maxY + minY) / 2;
    std::array<float, N + 1> x;
    std::array<float, N + 1> y;
    for (int i = 0; i < N; ++i) {
        x[i] = centerX + radiusX * cos(2 * pi * i / N - pi / 2);
        y[i] = centerY + radiusY * sin(2 * pi * i / N - pi / 2);
    }
    x[N] = x[0];
    y[N] = y[0];

    /// draw the oval
    mRectangleShape.setFillColor(penColor);
    mRectangleShape.setOrigin(0, penWidth / 2.f);

    mCircleShape.setFillColor(penColor);
    mCircleShape.setOrigin(penWidth / 2.f, penWidth / 2.f);
    mCircleShape.setRadius(penWidth / 2.f);

    for (int i = 0; i < N; ++i) {
        float delta_x = x[i + 1] - x[i];
        float delta_y = y[i + 1] - y[i];
        float length  = std::sqrt(delta_x * delta_x + delta_y * delta_y);
        float angle   = std::atan2(delta_y, delta_x) * 180.f / pi;

        mRectangleShape.setSize(sf::Vector2f(length, penWidth));
        mRectangleShape.setRotation(angle);
        mRectangleShape.setPosition(x[i], y[i]);
        mRenderTexture.draw(mRectangleShape);

        mCircleShape.setPosition(x[i], y[i]);
        mRenderTexture.draw(mCircleShape);
    }
}