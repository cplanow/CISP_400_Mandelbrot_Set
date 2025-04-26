#include <iostream>
#include <string>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

using namespace sf;

int main()
{
    // Get desktop resolution and scale it down by 2 for better performance
    int width = VideoMode::getDesktopMode().width / 2;
    int height = VideoMode::getDesktopMode().height / 2;

    // Create the render window
    RenderWindow window(VideoMode(width, height), "Mandelbrot Set");

    // Create the ComplexPlane object
    ComplexPlane plane(width, height);

    // Set up font and text
    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Error loading font" << endl;
        return -1;
    }
    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(10, 10);

    // Main loop
    while (window.isOpen())
    {
        // Handle Input
        Event event;
        while (window.pollEvent(event))
        {
            // Handle window close button
            if (event.type == Event::Closed)
                window.close();

            // Handle mouse clicks
            if (event.type == Event::MouseButtonPressed)
            {
                // Get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                
                // Right click to zoom out
                if (event.mouseButton.button == Mouse::Right)
                {
                    plane.zoomOut();
                    plane.setCenter(mousePos.x, mousePos.y);
                }
                // Left click to zoom in
                else if (event.mouseButton.button == Mouse::Left)
                {
                    plane.zoomIn();
                    plane.setCenter(mousePos.x, mousePos.y);
                }
            }

            // Handle mouse movement
            if (event.type == Event::MouseMoved)
            {
                // Update mouse location in ComplexPlane
                Vector2i mousePos = Mouse::getPosition(window);
                plane.setMouseLocation(mousePos.x, mousePos.y);
            }
        }

        // Check for escape key to close window
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        // Update Scene
        plane.updateRender();
        plane.loadText(text);

        // Draw Scene
        window.clear();
        window.draw(plane);
        window.draw(text);
        window.display();
    }

    return 0;
}