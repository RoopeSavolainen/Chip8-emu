#include <SFML/Graphics.hpp>

int main(int argc, char **argv)
{
    sf::RenderWindow win(sf::VideoMode(640, 480), "CHIP-8", sf::Style::Default);
    while (win.isOpen()) {
        sf::Event evt;
        while (win.pollEvent(evt)) {
            switch (evt.type) {
                case sf::Event::Closed:
                    win.close();
                    break;
                default:
                    break;
            }
        }

    }
    return 0;
}
