#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#define DEFAULT_WIN_SCALE 10
#define WINDOW_NAME "CHIP-8"

std::unique_ptr<sf::RenderWindow> create_window(unsigned window_scale);

#endif
