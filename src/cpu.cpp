#include <iostream>
#include <iomanip>
#include <random>

#include "cpu.hpp"
#include "memory.hpp"
#include "timer.hpp"

// Registers
uint16_t    pc = 0x200;
uint8_t     sp = 0;
uint8_t     Vx[16] = {0};
uint16_t    I = 0;

uint16_t stack[16] = {0x00};

// RNG stuff for RND
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<uint8_t> dstr(0, 255);

void exec_instruction(Screen *scr)
{
    uint16_t _pc = pc;
    bool nonrec = false;

    uint8_t instr_h = memory[pc++];
    uint8_t instr_l = memory[pc++];

    switch (instr_h & 0xf0) {
        case 0x00:
            switch (instr_l) {
                case 0xe0:  // CLS
                    scr->clear_screen();
                    break;
                case 0xee:  // RET
                    pc = stack[sp];
                    sp--;
                    break;
                default:
                    nonrec = true;
                    std::cerr << "A ";
                    break;
            }
            break;
        case 0x10:  // JP
            {
                uint16_t addr = ((instr_h & 0x0f) << 8) | (instr_l);
                pc = addr;
            }
            break;
        case 0x20:  // CALL
            {
                stack[++sp] = pc;
                uint16_t addr = ((instr_h & 0x0f) << 8) | (instr_l);
                pc = addr;
            }
            break;
        case 0x30:  // SE
            if (Vx[instr_h & 0x0f] == instr_l) {
                pc += 2;
            }
            break;
        case 0x40:  // SNE
            if (Vx[instr_h & 0x0f] != instr_l) {
                pc += 2;
            }
            break;
        case 0x50:  // SE
            if (Vx[instr_h & 0x0f] == Vx[instr_l >> 4]) {
                pc += 2;
            }
            break;
        case 0x60:  // LD
            Vx[instr_h & 0x0f] = instr_l;
            break;
        case 0x70:  // ADD
            Vx[instr_h & 0x0f] += instr_l;
            break;
        case 0x80:
            switch (instr_l & 0x0f) {
                case 0x00:  // LD
                    Vx[instr_h & 0x0f] = Vx[instr_l >> 4];
                    break;
                case 0x01:  // OR
                    Vx[instr_h & 0x0f] |= Vx[instr_l >> 4];
                    break;
                case 0x02:  // AND
                    Vx[instr_h & 0x0f] &= Vx[instr_l >> 4];
                    break;
                case 0x03:  // XOR
                    Vx[instr_h & 0x0f] ^= Vx[instr_l >> 4];
                    break;
                case 0x04:  // ADD (with carry)
                    Vx[instr_h & 0x0f] += Vx[instr_l >> 4];
                    Vx[0x0f] = (Vx[instr_h & 0x0f] + Vx[instr_l >> 4] > 255) ? 1 : 0;
                    break;
                case 0x05:  // SUB (with borrow)
                    Vx[0x0f] = (Vx[instr_h & 0x0f] > Vx[instr_l >> 4]) ? 1 : 0;
                    Vx[instr_h & 0x0f] -= Vx[instr_l >> 4];
                    break;
                case 0x06:  // SHR
                    Vx[0x0f] = (Vx[instr_h & 0x0f] & 0x01) ? 1 : 0;
                    Vx[instr_h & 0x0f] >>= 1;
                    break;
                case 0x07:  // SUBN
                    Vx[0x0f] = (Vx[instr_l >> 4] > Vx[instr_h & 0x0f]) ? 1 : 0;
                    Vx[instr_h & 0x0f] = Vx[instr_l >> 4] - Vx[instr_h & 0x0f];
                    break;
                case 0x0e:  // SHL
                    Vx[0x0f] = (Vx[instr_h & 0x0f] & 0x80) ? 1 : 0;
                    Vx[instr_h & 0x0f] <<= 1;
                    break;
                default:
                    nonrec = true;
                    break;
            }
            break;
        case 0x90:  // SNE
            if (Vx[instr_h & 0x0f] != Vx[instr_l >> 4]) {
                pc += 2;
            }
            break;
        case 0xa0:  // LD (I)
            I = ((instr_h & 0x0f) << 8) | instr_l;
            break;
        case 0xb0:  // JP (+V0)
            pc = ((instr_h & 0x0f) << 8) | instr_l + Vx[0x00];
            break;
        case 0xc0:  // RND
            Vx[instr_h & 0x0f] = dstr(rng) & instr_l;
            break;
        case 0xd0:  // DRW
            // TODO: implement
            break;
        case 0xe0:
            switch (instr_l) {
                case 0x9e:  // SKP
                    // TODO: implement
                    break;
                case 0xa1:  // SKPN
                    // TODO: implement
                    break;
                default:
                    nonrec = true;
                    break;
            }
            break;
        case 0xf0:
            switch (instr_l) {
                case 0x07:  // LD Vx = DT
                    Vx[instr_h & 0x0f] = timer_delay;
                    break;
                case 0x0a:  // LD Vx = K
                    // TODO: implement
                    break;
                case 0x15:  // LD DT = Vx
                    timer_delay = Vx[instr_h & 0x0f];
                    break;
                case 0x18:  // LD ST = Vx
                    timer_sound = Vx[instr_h & 0x0f];
                    break;
                case 0x1e:  // ADD I, Vx
                    I += Vx[instr_h & 0x0f];
                    break;
                case 0x29:  // LD F, Vx
                    // TODO: implement
                    break;
                case 0x33:  // LD B, Vx
                    {
                        uint8_t val = Vx[instr_h & 0x0f];
                        memory[I] = val / 100;
                        memory[I+1] = (val % 100) / 10;
                        memory[I+2] = val % 10;
                    }
                    break;
                case 0x55:  // LD [I], Vx
                    for (unsigned int i = 0; i < 0x10; i++) memory[I++] = Vx[i];
                    break;
                case 0x65:  // LD Vx, [I]
                    for (unsigned int i = 0; i < 0x10; i++) memory[I++] = Vx[i];
                    break;
                default:
                    nonrec = true;
                    break;
            }
            break;
        default:
            nonrec = true;
            break;
    }
    if (nonrec)
        std::cerr << "Non-recognized opcode at PC = 0x" << std::hex << std::setfill('0') << std::setw(4) << _pc
            << " encountered: 0x" << std::hex << std::setfill('0') << std::setw(2) << (int)instr_h
                                  << std::hex << std::setfill('0') << std::setw(2) << (int)instr_l << std::endl;
}
