#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cinttypes>

extern uint8_t memory[0x1000];

bool read_program(char *fname);

#endif
