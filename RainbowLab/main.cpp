#include "Rainbow.h"
using namespace sf;
using namespace std;

int main()

{
    int pixelWidth = VideoMode::getDesktopMode().width;
    int pixelHeight = VideoMode::getDesktopMode().height;
    VideoMode vm(pixelWidth, pixelHeight);
    RenderWindow window(vm, "Rainbow Screen", Style::Default);

    RainbowScreen rain(pixelWidth, pixelHeight);
    bool update = true;
   

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "the left button was pressed" << endl;
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;
                    update = true;
                    
                }
            }
        }
    }
    {
        ///Input
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        ///Update
        if(update)
        {
            rain.update();
            update = false;
        }
        ///Draw
        window.clear();
        window.draw(rain);
        window.display();

    }
}



