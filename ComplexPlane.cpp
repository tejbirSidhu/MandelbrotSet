#include "ComplexPlane.h"
#include <complex>
#include <cmath>
#include <SFML/Graphics/VertexArray.hpp>

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size = Vector2i (pixelWidth, pixelHeight);
    m_aspectRatio = static_cast<float>(pixelHeight)/pixelWidth;
    m_plane_center = Vector2f {0,0};
    m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
    m_zoomCount = 0;
    m_state = State::CALCULATING;
    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    int xSize = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount));
    int ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount));
    m_plane_size = {xSize, ySize};
    m_state = State:: CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    int xSize = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount));
    int ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount));
    m_plane_size = {xSize, ySize};
    m_state = State:: CALCULATING;    
}

void ComplexPlane::updateRender()
{
    if (m_state == CALCULATING)
    {
        for (int i = 0; i < m_pixel_size.y ; i++)
        {
            for (int j = 0; j < m_pixel_size.x; j++)
            {
                int index = j + i*m_pixel_size.x;
                m_vArray[index].position = {(float)j,float(i)};
                Vector2f coord = mapPixelToCoords(Vector2i(j,i));
                size_t numIterations = countIterations(coord);

                Uint8 r, g, b;
                iterationsToRGB(numIterations, r, g, b);
                m_vArray[j + i * m_pixel_size.x].color = {r,g,b};
            }
        }
        m_state = State:: DISPLAYING;
    }
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
    Vector2f screenPixelLocation;
    screenPixelLocation = mapPixelToCoords(mousePixel);
    m_plane_center = screenPixelLocation;
    m_state = State:: CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    Vector2f screenPixelLocation;
    screenPixelLocation = mapPixelToCoords(mousePixel);
    m_mouseLocation = screenPixelLocation;
}

void ComplexPlane::loadText(Text& text)
{
    stringstream ss;
    ss << "Mandelbrot Set\n";
    ss << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")\n";
    ss << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")\n";
    ss << "Left-click to Zoom in\n";
    ss << "Right-click to Zoom out\n";
}

size_t ComplexPlane:: countIterations(Vector2f coord)
{

}
void ComplexPlane:: iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}
Vector2f ComplexPlane:: mapPixelToCoords(Vector2i mousePixel)
{
    
}

