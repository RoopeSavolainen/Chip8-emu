#include "video.hpp"

std::unique_ptr<sf::RenderWindow> create_window(unsigned window_scale)
{
    sf::VideoMode reso(64 * window_scale, 32 * window_scale);
    sf::Uint32 win_style = sf::Style::Titlebar | sf::Style::Close;
    auto win = std::make_unique<sf::RenderWindow>(reso, WINDOW_NAME, win_style);

    return win;
}
