#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cinttypes>

#define FONT_ADDR 0x100

extern uint8_t memory[0x1000];

bool read_program(char *fname);

#endif
