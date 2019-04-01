#include <iostream>

#include "memory.hpp"

uint8_t memory[4096] = {0};

bool read_program(char *fname)
{
    FILE *f = fopen(fname, "r");
    if (!f) {
        std::cerr << "Could not open '" << fname << "'." << std::endl;
        return false;
    }
    fseek(f, 0, SEEK_END);
    int len = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (len > 0xe00) {
        std::cerr << "The input file " << fname << " is too large; 0x" << std::hex << len << " bytes." << std::endl;
        return false;
    }

    int prg_it = 0x200;
    while (!feof(f))
        memory[prg_it++] = fgetc(f);
    fclose(f);

    return true;
}
