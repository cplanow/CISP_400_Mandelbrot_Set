#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class RainbowScreen : public Drawable
{

public:
    RainbowScreen(int pixelWidth, int pixelHeight);
    void update(); //update to pixels
    void draw(RenderTarget& target, RenderStates states) const override;

private:
    VertexArray m_va;
    Vector2i m_pixel_size;
};
