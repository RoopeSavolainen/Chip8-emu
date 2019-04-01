#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "cpu.hpp"
#include "video.hpp"
#include "memory.hpp"

unsigned window_scale = DEFAULT_WIN_SCALE;
char *fname;

bool parse_args(int argc, char **argv);
void usage(char **argv);

uint8_t timer1 = 0,
        timer2 = 0;

using clk = std::chrono::system_clock;
clk::time_point last_tick;

int main(int argc, char **argv)
{
    if (!parse_args(argc, argv)) return 0;
    if (!read_program(fname)) return 1;

    Screen screen(window_scale);
    screen.clear_screen();
    screen.refresh();

    last_tick = clk::now();
    std::chrono::milliseconds timer_interval(1000/60);
    while (screen.isOpen()) {
        if (clk::now() <= last_tick + timer_interval) {
            last_tick = clk::now();
            if (timer1 > 0) timer1--;
            if (timer2 > 0) timer2--;
        }

        exec_instruction(&screen);

        sf::Event evt;
        while (screen.pollEvent(evt)) {
            switch (evt.type) {
                case sf::Event::Closed:
                    screen.close();
                    break;
                default:
                    break;
            }
        }

    }
    return 0;
}

bool parse_args(int argc, char **argv) {
    if (argc < 2) {
        usage(argv);
        return false;
    }
    for (int i = 1; i < argc; i++) {
        std::string arg = std::string(argv[i]);

        if (i == argc - 1) {
            fname = argv[i];
        } else if (arg == "-s" || arg == "--scale") {
            i++;
            try {
                window_scale = std::stoi(argv[i]);
            } catch (std::exception &e) {
            }
            if (window_scale < 1) window_scale = DEFAULT_WIN_SCALE;
        } else if (arg == "-h" || arg == "--help") {
            usage(argv);
            return false;
        }
    }
    return true;
}

void usage(char **argv) {
    std::cout << "Usage: " << argv[0] << " [OPTION]... FILE" << std::endl;
    std::cout << "Open and execute FILE." << std::endl;
    std::cout << "\t-s NUM, --scale NUM\tScale the window resolution by NUM. (Default: " << DEFAULT_WIN_SCALE << ")" << std::endl;
    std::cout << "\t-h, --help\t\tShow this help." << std::endl;

}
