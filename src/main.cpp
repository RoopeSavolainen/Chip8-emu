#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "video.hpp"

unsigned window_scale = DEFAULT_WIN_SCALE;

bool parse_args(int argc, char **argv);

int main(int argc, char **argv)
{
    if (!parse_args(argc, argv)) return 0;

    auto win = create_window(window_scale);
    while (win->isOpen()) {
        sf::Event evt;
        while (win->pollEvent(evt)) {
            switch (evt.type) {
                case sf::Event::Closed:
                    win->close();
                    break;
                default:
                    break;
            }
        }

    }
    return 0;
}

bool parse_args(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        std::string arg = std::string(argv[i]);

        if (arg == "-s" || arg == "--scale") {
            i++;
            try {
                window_scale = std::stoi(argv[i]);
            } catch (std::exception &e) {
            }
            if (window_scale < 1) window_scale = DEFAULT_WIN_SCALE;
        } else if (arg == "-h" || arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [OPTION]... FILE" << std::endl;
            std::cout << "Open and execute FILE." << std::endl;
            std::cout << "\t-s NUM, --scale NUM\tScale the window resolution by NUM. (Default: " << DEFAULT_WIN_SCALE << ")" << std::endl;
            std::cout << "\t-h, --help\t\tShow this help." << std::endl;
            return false;
        }
    }
    return true;
}
