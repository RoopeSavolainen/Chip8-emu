#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#define DEFAULT_WIN_SCALE 10
#define WINDOW_NAME "CHIP-8"

class Screen : public sf::RenderWindow {
    private:
        unsigned window_scale;
        std::vector<sf::RectangleShape> pixels;

    public:
        Screen(unsigned window_scale);
        void refresh();
        bool toggle_pixel(sf::Vector2u coord);
        void clear_screen();
};

#endif
