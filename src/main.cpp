#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "cpu.hpp"
#include "video.hpp"
#include "memory.hpp"
#include "timer.hpp"

unsigned window_scale = DEFAULT_WIN_SCALE;
char *fname;
static const double DEFAULT_CPU_FREQ = 1.0;
double cpu_freq = DEFAULT_CPU_FREQ;

bool parse_args(int argc, char **argv);
void usage(char **argv);

using clk = std::chrono::system_clock;
clk::time_point last_timer_tick;

int main(int argc, char **argv)
{
    if (!parse_args(argc, argv)) return 0;
    if (!read_program(fname)) return 1;

    Screen screen(window_scale);
    screen.clear_screen();
    screen.refresh();

    last_timer_tick = clk::now();
    std::chrono::milliseconds timer_interval(1000/60);
    while (screen.isOpen()) {
        if (clk::now() <= last_timer_tick + timer_interval) {
            last_timer_tick = clk::now();
            if (timer_delay > 0) timer_delay--;
            if (timer_sound > 0) timer_sound--;
        }
        exec_instruction(&screen);
        screen.refresh();

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

        sf::sleep(sf::microseconds(1000/cpu_freq));
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
        
        if (arg == "-h" || arg == "--help") {
            usage(argv);
            return false;
        } else if (i == argc - 1) {
            fname = argv[i];
        } else if (arg == "-s" || arg == "--scale") {
            i++;
            try {
                window_scale = std::stoi(argv[i]);
            } catch (std::exception &e) {
            }
            if (window_scale < 1) window_scale = DEFAULT_WIN_SCALE;
        } else if (arg == "-f" || arg == "--freq") {
            i++;
            try {
                cpu_freq = std::stod(argv[i]);
            } catch (std::exception &e) {
            }
        }
    }
    return true;
}

void usage(char **argv) {
    std::cout << "Usage: " << argv[0] << " [OPTION]... FILE" << std::endl;
    std::cout << "Open and execute FILE." << std::endl;
    std::cout << "\t-f NUM, --freq NUM\tSet the CPU frequency. (in kHz, default: " << DEFAULT_CPU_FREQ << ")" << std::endl;
    std::cout << "\t-s NUM, --scale NUM\tScale the window resolution by NUM. (Default: " << DEFAULT_WIN_SCALE << ")" << std::endl;
    std::cout << "\t-h, --help\t\tShow this help." << std::endl;
}
