//Created by Chris Planow and Ali Chenari
#include <iostream>
#include <string>
#include <math.h>
#include "ComplexPlane.h"
#include <cmath>
#include <sstream>

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixelSize = {pixelWidth, pixelHeight};
    m_aspectRatio = static_cast<float>(pixelHeight) / static_cast<float>(pixelWidth);
    m_planeCenter = {0, 0};
    m_zoomLevel = BASE_ZOOM;
    m_state = State::CALCULATING;

    // Initialize vertex array
    m_vertices.setPrimitiveType(sf::Points);
    m_vertices.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_vertices, states);
}

void ComplexPlane::updateRender()
{
    if (m_state == State::CALCULATING)
    {
        for (int i = 0; i < m_pixelSize.y; ++i)
        {
            for (int j = 0; j < m_pixelSize.x; ++j)
            {
                m_vertices[j + i * m_pixelSize.x].position = {static_cast<float>(j), static_cast<float>(i)};
                
                sf::Vector2f coords = mapPixelToCoords({j, i});
                size_t iterations = countIterations(coords);
                
                sf::Uint8 r, g, b;
                iterationsToRGB(iterations, r, g, b);
                m_vertices[j + i * m_pixelSize.x].color = sf::Color(r, g, b);
            }
        }
        m_state = State::DISPLAYING;
    }
}

void ComplexPlane::zoomIn()
{
    m_zoomLevel++;
    float xSize = BASE_WIDTH * std::pow(BASE_ZOOM, m_zoomLevel);
    float ySize = BASE_HEIGHT * m_aspectRatio * std::pow(BASE_ZOOM, m_zoomLevel);
    m_planeSize = {xSize, ySize};
    m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomLevel--;
    float xSize = BASE_WIDTH * std::pow(BASE_ZOOM, m_zoomLevel);
    float ySize = BASE_HEIGHT * m_aspectRatio * std::pow(BASE_ZOOM, m_zoomLevel);
    m_planeSize = {xSize, ySize};
    m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(sf::Vector2i mousePixel)
{
    m_planeCenter = mapPixelToCoords(mousePixel);
    m_state = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(sf::Vector2i mousePixel)
{
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(sf::Text& text)
{
    std::stringstream ss;
    ss << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n";
    ss << "Center: (" << m_planeCenter.x << ", " << m_planeCenter.y << ")\n";
    ss << "Zoom Level: " << m_zoomLevel;
    text.setString(ss.str());
}

size_t ComplexPlane::countIterations(sf::Vector2f coord)
{
    size_t iterations = 0;
    float x = 0;
    float y = 0;
    float x2 = 0;
    float y2 = 0;
    
    while (iterations < MAX_ITER && (x2 + y2 <= 4))
    {
        y = 2 * x * y + coord.y;
        x = x2 - y2 + coord.x;
        x2 = x * x;
        y2 = y * y;
        iterations++;
    }
    
    return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b)
{
    if (count == MAX_ITER)
    {
        r = g = b = 0;  // Black for points in the set
        return;
    }

    float normalized = static_cast<float>(count) / MAX_ITER;
    if (normalized < 0.2f)
    {
        // Purple to blue
        r = static_cast<sf::Uint8>(128 * (normalized * 5));
        g = 0;
        b = 255;
    }
    else if (normalized < 0.4f)
    {
        // Blue to turquoise
        r = 0;
        g = static_cast<sf::Uint8>(255 * ((normalized - 0.2f) * 5));
        b = 255;
    }
    else if (normalized < 0.6f)
    {
        // Turquoise to green
        r = 0;
        g = 255;
        b = static_cast<sf::Uint8>(255 * (1 - ((normalized - 0.4f) * 5)));
    }
    else if (normalized < 0.8f)
    {
        // Green to yellow
        r = static_cast<sf::Uint8>(255 * ((normalized - 0.6f) * 5));
        g = 255;
        b = 0;
    }
    else
    {
        // Yellow to red
        r = 255;
        g = static_cast<sf::Uint8>(255 * (1 - ((normalized - 0.8f) * 5)));
        b = 0;
    }
}

sf::Vector2f ComplexPlane::mapPixelToCoords(sf::Vector2i mousePixel)
{
    sf::Vector2f coords;
    
    // Map x coordinate
    coords.x = ((mousePixel.x - 0.0f) / (m_pixelSize.x - 0.0f)) * m_planeSize.x + 
               (m_planeCenter.x - m_planeSize.x / 2.0f);
    
    // Map y coordinate (note the inverted Y axis)
    coords.y = ((mousePixel.y - m_pixelSize.y) / (0.0f - m_pixelSize.y)) * m_planeSize.y +
               (m_planeCenter.y - m_planeSize.y / 2.0f);
    
    return coords;
}