#include "../include/cpu.h"
#include <iostream>

int main(int argc, char* argv[]) {
    CPU cpu(argv[1]);
    cpu.loop();

    return 0;
}