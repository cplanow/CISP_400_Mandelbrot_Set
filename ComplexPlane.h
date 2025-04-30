//Created by Chris Planow and Ali Chenari
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <vector>

// Global constants
const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

// State enum class for tracking calculation status
enum class State
{
    CALCULATING,
    DISPLAYING
};

class ComplexPlane : public sf::Drawable
{
private:
    // Member variables
    sf::VertexArray m_vertices;
    State m_state;
    sf::Vector2f m_mouseLocation;
    sf::Vector2i m_pixelSize;
    sf::Vector2f m_planeCenter;
    sf::Vector2f m_planeSize;
    float m_zoomLevel;
    float m_aspectRatio;

    // Private methods
    void iterationsToRGB(size_t count, sf::Uint8& r, sf::Uint8& g, sf::Uint8& b);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    // Constructor
    ComplexPlane(int pixelWidth, int pixelHeight);

    // Member functions
    void zoomIn();
    void zoomOut();
    void setCenter(sf::Vector2i mousePixel);
    void setMouseLocation(sf::Vector2i mousePixel);
    void updateRender();
    void loadText(sf::Text& text);
    
    // Helper functions
    sf::Vector2f mapPixelToCoords(sf::Vector2i mousePixel);
    size_t countIterations(sf::Vector2f coord);
};