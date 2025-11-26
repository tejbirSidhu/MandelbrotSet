#include "ComplexPlane.h"
#include <complex>
#include <cmath>
#include <sstream>
#include <SFML/Graphics/VertexArray.hpp>
using namespace std;
using namespace sf;

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

void ComplexPlane::draw(sf:: RenderTarget& target, sf:: RenderStates states) const
{
    target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float xSize = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = {xSize, ySize};
    m_state = State:: CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float xSize = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = {xSize, ySize};
    m_state = State:: CALCULATING;    
}

void ComplexPlane::updateRender()
{
    if (m_state == State::CALCULATING)
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

    text.setString(ss.str());
}

size_t ComplexPlane:: countIterations(Vector2f coord)
{
    complex<float> c (coord.x, coord.y);
    complex<float> z (0,0);

    for(size_t iteration = 0; iteration < MAX_ITER; iteration++)
    {
        z = z * z + c;
        if(abs(z) > 2.0)
        {
            return iteration;
        }
    }
    return MAX_ITER; //holds same value as iteration but since we can't access we used MAX_ITER instead
}
void ComplexPlane:: iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    if(count == MAX_ITER)
    {
        r = 0;
        g = 0;
        b = 0;
    }
    else if(count < MAX_ITER)
    {
        if(count <= 13)
        {
            r = 203;
            g = 8;
            b = 247;
        }
        else if(count <= 26)
        {
            r = 8;
            g = 171;
            b = 247;
        }
        else if(count <= 39)
        {
            r = 8;
            g = 247;
            b = 84;
        }
        else if(count <= 52)
        {
            r = 243;
            g = 247;
            b = 8;
        }
        else
        {
            r = 247;
            g = 24;
            b = 8;
        }
    }
}
Vector2f ComplexPlane:: mapPixelToCoords(Vector2i mousePixel)
{
    float realMin = m_plane_center.x-m_plane_size.x/2.0f;
    float realMax = m_plane_center.x + m_plane_size.x/2.0f;
    float realNum = ((float)(mousePixel.x - 0)/(float)(m_pixel_size.x -0)) * (realMax - realMin) + realMin;

    float imagMin = m_plane_center.y - m_plane_size.y/2.0f;
    float imagMax = m_plane_center.y + m_plane_size.y/2.0f;
    float imagNum = ((float)(mousePixel.y - m_pixel_size.y)/(float)(0 - m_pixel_size.y)) * (imagMax - imagMin) + imagMin;

    return Vector2f(realNum, imagNum);
}

