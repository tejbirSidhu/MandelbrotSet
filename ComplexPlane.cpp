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
    m_state = CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    int xSize = BASE_WIDTH * (pow(BASE_ZOOM, m_ZoomCount));
    int ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_ZoomCount));
    m_plane_size = {xSize, ySize};
    m_state = CALCULATING;    
}

void complexPlane::updateRender()
{
    if (m_state == CALCULATING)
    {
        for (int i = 0; i < ; i++)
        {
            for (int j = 0; j < ; j++)
            {

            }
        }
    }
}