#include "Rainbow.h"

RainbowScreen::RainbowScreen(int pixelWidth, int pixelHeight)
{
    m_pixel_size = { pixelWidth, pixelHeight };
    m_va.setPrimitiveType(Points);
    m_va.resize(pixelWidth * pixelHeight);
}

void RainbowScreen::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_va);
}

void RainbowScreen::update()
{
    int pixelHeight = m_pixel_size.y;
    int pixelWidth = m_pixel_size.x;
    for(int i = 0; i < pixelHeight; i++) //row loop
    {
        Uint8 r, g, b;
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;
        for(int j = 0; j <pixelWidth; j++) //column loop
        {
            m_va[i * pixelWidth + j].position = {(float)j, (float)i};
            m_va[i * pixelWidth + j].color = {r, g, b};
        }
    }
}
