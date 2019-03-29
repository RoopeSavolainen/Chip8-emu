#include "video.hpp"

Screen::Screen(unsigned _window_scale) : sf::RenderWindow(), window_scale(_window_scale)
{
    // Create the window object
    sf::VideoMode reso(64 * window_scale, 32 * window_scale);
    sf::Uint32 win_style = sf::Style::Titlebar | sf::Style::Close;
    create(reso, WINDOW_NAME, win_style);

    // Populate the pixels
    sf::Vector2f size(window_scale, window_scale);
    sf::RectangleShape px(size);
    px.setOutlineThickness(0);
    px.setFillColor(sf::Color::Black);
    for (unsigned y = 0; y < 32; y++) {
        for (unsigned x = 0; x < 64; x++) {
            px.setPosition(x*window_scale, y*window_scale);
            pixels.push_back(px);
        }
    }
}

void Screen::refresh()
{
    clear();
    for (auto px : pixels)
        draw(px);
    display();
}

void Screen::set_pixel(sf::Vector2u coord, bool on)
{
    pixels[coord.y*64 + coord.x].setFillColor(on ? sf::Color::Black : sf::Color::White);
}

void Screen::clear_screen()
{
    for (unsigned y = 0; y < 32; y++)
        for (unsigned x = 0; x < 64; x++)
            set_pixel(sf::Vector2u(x,y), false);
}
