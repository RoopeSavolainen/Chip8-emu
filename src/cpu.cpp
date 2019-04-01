#include "cpu.hpp"

#include "memory.hpp"

// Registers
uint16_t    pc;
uint8_t     sp;
uint8_t     V0,
            V1,
            V2,
            V3,
            V4,
            V5,
            V6,
            V7,
            V8,
            V9,
            VA,
            VB,
            VC,
            VD,
            VE,
            VF;
uint16_t    I;
uint16_t stack[16] = {0x00};

void exec_instruction(Screen *scr)
{
    (void)scr;
}
