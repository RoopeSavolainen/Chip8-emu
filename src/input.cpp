#include "input.hpp"

#include <SFML/Window.hpp>

using sf::Keyboard;
sf::Keyboard::Key keys[0x10] = {
    Keyboard::Key::Num1, Keyboard::Key::Num2, Keyboard::Key::Num3, Keyboard::Key::Q,
    Keyboard::Key::W, Keyboard::Key::E, Keyboard::Key::A, Keyboard::Key::S,
    Keyboard::Key::D, Keyboard::Key::X, Keyboard::Key::Z, Keyboard::Key::C,
    Keyboard::Key::Num4, Keyboard::Key::R, Keyboard::Key::F, Keyboard::Key::V,
};

bool check_key(uint8_t key)
{
    return Keyboard::isKeyPressed(keys[key]);
}

uint8_t poll_key()
{
    for (;;) {
        for (uint8_t i = 0; i < 0x10; i++)
            if (Keyboard::isKeyPressed(keys[i])) return i;
        sf::sleep(sf::microseconds(10));
    }
}
