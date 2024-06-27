#include "../include/cpu.h"
#include <fstream>
#include <iostream>
#include <iostream>
#include <iomanip>
#include "../include/tools.h"
#include "../include/instructions.h"
#include <string.h>
#include "../include/registers.h"
#include <unistd.h>

Registers::Registers()
{
    AF = 0x01B0;
    BC = 0x0013;
    DE = 0x00D8;
    HL = 0x014D;
    SP = 0xFFFE;
    PC = 0x0100;

    A = (uint8_t*)&AF + 1;
    F = (uint8_t*)&AF;
    B = (uint8_t*)&BC + 1;
    C = (uint8_t*)&BC;
    D = (uint8_t*)&DE + 1;
    E = (uint8_t*)&DE;
    H = (uint8_t*)&HL + 1;
    L = (uint8_t*)&HL;
}


CPU::CPU(std::string filename) : registers(), cart(), haltState(0), stopped(false), haltBugPC(0), IME(false),
IEaddr(0xFFFF), IFaddr(0xFF0F), DIVaddr(0xFF04), TIMAaddr(0xFF05), TMAaddr(0xFF06), TMCaddr(0xFF07),
clockSpeed(4194304), frequency(4096), maxCycles(69905), selectedROMBank(1), selectedRAMBank(0), renderer(160,144)
{
    //std::cout << "A:01 F:B0 B:00 C:13 D:00 E:D8 H:01 L:4D SP:FFFE PC:0100 PCMEM:00,C3,13,02" << std::endl;
    memset(memory, 0, sizeof(memory));
    if (loadROM(filename)) {
        throw std::runtime_error("Error loading ROM");
        return;
        }
    else {
            std::cout << "ROM loaded successfully" << std::endl;
    }

    memory[0xFF00] = 0xCF;
    memory[0xFF05] = 0x00;
    memory[0xFF06] = 0x00;
    memory[0xFF07] = 0x00;
    memory[0xFF10] = 0x80;
    memory[0xFF11] = 0xBF;
    memory[0xFF12] = 0xF3;
    memory[0xFF14] = 0xBF;
    memory[0xFF16] = 0x3F;
    memory[0xFF17] = 0x00;
    memory[0xFF19] = 0xBF;
    memory[0xFF1A] = 0x7F;
    memory[0xFF1B] = 0xFF;
    memory[0xFF1C] = 0x9F;
    memory[0xFF1E] = 0xBF;
    memory[0xFF20] = 0xFF;
    memory[0xFF21] = 0x00;
    memory[0xFF22] = 0x00;
    memory[0xFF23] = 0xBF;
    memory[0xFF24] = 0x77;
    memory[0xFF25] = 0xF3;
    memory[0xFF26] = 0xF1;
    memory[0xFF40] = 0x91;
    memory[0xFF42] = 0x00;
    memory[0xFF43] = 0x00;
    memory[0xFF45] = 0x00;
    memory[0xFF47] = 0xFC;
    memory[0xFF48] = 0xFF;
    memory[0xFF49] = 0xFF;
    memory[0xFF4A] = 0x00;
    memory[0xFF4B] = 0x00;
    memory[0xFF4D] = 0xFF;
    memory[0xFFFF] = 0x00;

    loadCartHeader();
    std::cout << "Cart header loaded" << std::endl;
    switch (cart.cartType) {
    case 0: MBC = 0; std::cout << "ROM ONLY" << std::endl; break;
    case 1: MBC = 1; std::cout << "MBC1" << std::endl; break;
    case 2: MBC = 1; std::cout << "MBC1+RAM" << std::endl; break;
    case 3: MBC = 1; std::cout << "MBC1+RAM+BATTERY" << std::endl; break;
    case 5: MBC = 2; std::cout << "MBC2" << std::endl; break;
    case 6: MBC = 2; std::cout << "MBC2+BATTERY" << std::endl; break;
    default: MBC = 0; std::cout << "OTHER -> ROM ONLY" << std::endl; break;
    }
    timerCounter = 4194304 / 4096.0;
    memset(screenData, 128, sizeof(screenData));
    memset(&RAM, 0, sizeof(RAM));
    std::cout << "CPU initialized" << std::endl;
}

CPU::~CPU()
{
    delete[] ROMBanks;
}

int CPU::loadROM(std::string filename) {
    inputFile.open(filename, std::ios_base::binary);
    if (!inputFile.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return 1;
    }

    inputFile.seekg(0, std::ios::end);
    int size = inputFile.tellg();
    ROMBanks = new uint8_t[size];
    memset(ROMBanks, 0, size);
    inputFile.seekg(0, std::ios::beg);
    if (size > 0x4000) {
        inputFile.read((char*)memory, 0x4000);
        inputFile.read((char*)ROMBanks, size - 0x4000);
    }
    else {
        inputFile.read((char*)memory, size);
    }
    inputFile.close();
    return 0;
}


void CPU::loadCartHeader() {
    //std::cout << "Loading cart header" << std::endl;
    std::copy(&memory[0x100], &memory[0x100] + 4, cart.intro);
    std::copy(&memory[0x104], &memory[0x104] + 48, cart.logo);
    std::copy(&memory[0x134], &memory[0x134] + 16, cart.title);
    cart.CGB = memory[0x143];
    std::copy(&memory[0x144], &memory[0x144] + 2, cart.newLicense);
    cart.SGB = memory[0x146];
    cart.cartType = memory[0x147];
    cart.ROMSize = memory[0x148];
    cart.RAMSize = memory[0x149];
    cart.destCode = memory[0x14A];
    cart.oldLicense = memory[0x14B];
    cart.maskRomVer = memory[0x14C];
    cart.headerChecksum = memory[0x14D];
    std::copy(&memory[0x14E], &memory[0x14E] + 2, cart.globalChecksum);
    /*std::cout << "Cart info:" << std::endl;
    std::cout << "Title: " << cart.title << std::endl;
    std::cout << "CGB: " << std::hex << (int)cart.CGB << std::endl;
    std::cout << "SGB: " << std::hex << (int)cart.SGB << std::endl;
    std::cout << "Cart type: " << std::hex << (int)cart.cartType << std::endl;
    std::cout << "ROM size: " << std::hex << (int)cart.ROMSize << std::endl;
    std::cout << "RAM size: " << std::hex << (int)cart.RAMSize << std::endl;
    std::cout << "Dest code: " << std::hex << (int)cart.destCode << std::endl;
    std::cout << "Old license: " << std::hex << (int)cart.oldLicense << std::endl;
    std::cout << "Mask ROM version: " << std::hex << (int)cart.maskRomVer << std::endl;
    std::cout << "Header checksum: " << std::hex << (int)cart.headerChecksum << std::endl;
    std::cout << "Global checksum: " << std::hex << (int)cart.globalChecksum[0] << std::hex << (int)cart.globalChecksum[1] << std::endl;*/
}

/////////////////////////////////////////////////////////////////////////////////////
uint8_t CPU::readMemory(uint16_t addr) {
    if ((addr >= 0x4000) & (addr <= 0x7FFF)) { // reading from ROM bank
        return ROMBanks[(addr - 0x4000) + ((selectedROMBank - 1) * 0x4000)];
    }
    else if ((addr >= 0xA000) & (addr <= 0xBFFF)) { // reading from RAM bank
        return RAM[(addr - 0xA000) + (selectedRAMBank * 0x2000)];
    }
    else if (addr == 0xFF00) { // joypad
        return getJoypadState();
    }
    return memory[addr]; // remaining memory is read normally
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::writeMemory(uint16_t addr, uint8_t value) {
    if (addr < 0x8000) // cant write into ROM
    {
        handleBanking(addr, value);
    }
    //else if (addr == 0xFF01)         std::cout << (char)value << std::flush; //blargg debug serial
    else if ((addr >= 0xE000) && (addr <= 0xFDFF))
    {
        memory[addr] = value;
        writeMemory(addr - 0x2000, value);
    }
    else if ((addr >= 0xFEA0) && (addr < 0xFEFF))
    {
    }
    else if (DIVaddr == addr)
    {
        memory[DIVaddr] = 0;
    }
    else if (TMCaddr == addr)
    {
        uint8_t currentfreq = getClockFrequency();
        memory[TMCaddr] = value;
        uint8_t newfreq = getClockFrequency();

        if (currentfreq != newfreq)
        {
            setClockFrequency();
        }
    }
    else if (addr == 0xFF44) // reset scanline if written to
    {
        memory[0xFF44] = 0;
    }
    else if (addr == 0xFF46)
    {
        DMATransfer(value);
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF && enableRAM) // Ram bank
    {
        RAM[(addr - 0xA000) + (selectedRAMBank * 0x2000)] = value;
    }
    else
    {
        memory[addr] = value;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::DMATransfer(uint8_t source) {
    uint16_t addr = source << 8;
    for (int i = 0; i < 160; i++) { // move 160 bytes to 0xFE00
        writeMemory(0xFE00 + i, readMemory(addr + i));
    }
}

/////////////////////////////////////////////////////////////////////////////////////
int CPU::runNextOpcode() {
    using namespace Instr;
    
    int opcode = readMemory(registers.PC);
    if (0xCB == opcode) {
        registers.PC++;
        opcode = readMemory(registers.PC) + 0x100;
    }

    switch (opcode) {
    case 0x00: return NOP(*this);
    case 0x03: return INC(*this, BC);
    case 0x04: return INC(*this, B);
    case 0x23: return INC(*this, HL);
    case 0x24: return INC(*this, H);
    case 0x0C: return INC(*this, C);
    case 0x13: return INC(*this, DE);
    case 0x14: return INC(*this, D);
    case 0x1C: return INC(*this, E);
    case 0x2C: return INC(*this, L);
    case 0x33: return INC(*this, SP);
    case 0x34: return INC(*this, HLa);
    case 0x3C: return INC(*this, A);
    case 0x05: return DEC(*this, B);
    case 0x0B: return DEC(*this, BC);
    case 0x0D: return DEC(*this, C);
    case 0x15: return DEC(*this, D);
    case 0x1B: return DEC(*this, DE);
    case 0x1D: return DEC(*this, E);
    case 0x25: return DEC(*this, H);
    case 0x2B: return DEC(*this, HL);
    case 0x2D: return DEC(*this, L);
    case 0x35: return DEC(*this, HLa);
    case 0x3B: return DEC(*this, SP);
    case 0x3D: return DEC(*this, A);
    case 0x01: return LD(*this, BC, d16, 2);
    case 0x11: return LD(*this, DE, d16, 2);
    case 0x21: return LD(*this, HL, d16, 2);
    case 0x31: return LD(*this, SP, d16, 2);
    case 0x08: return LD(*this, a16, SP, 2);
    case 0xF8: return LD(*this, HL, SPr8, 2);
    case 0xF9: return LD(*this, SP, HL, 2);

    case 0x02: return LD(*this, BCa, A, 1);
    case 0x06: return LD(*this, B, d8, 1);
    case 0x0A: return LD(*this, A, BCa, 1);
    case 0x0E: return LD(*this, C, d8, 1);
    case 0x12: return LD(*this, DEa, A, 1);
    case 0x16: return LD(*this, D, d8, 1);
    case 0x1A: return LD(*this, A, DEa, 1);
    case 0x1E: return LD(*this, E, d8, 1);
    case 0x22: return LD(*this, HLi, A, 1);
    case 0x2E: return LD(*this, L, d8, 1);
    case 0x26: return LD(*this, H, d8, 1);
    case 0x2A: return LD(*this, A, HLi, 1);
    case 0x32: return LD(*this, HLd, A, 1);
    case 0x36: return LD(*this, HLa, d8, 1);
    case 0x3A: return LD(*this, A, HLd, 1);
    case 0x3E: return LD(*this, A, d8, 1);
    case 0x40: return LD(*this, B, B, 1);
    case 0x41: return LD(*this, B, C, 1);
    case 0x42: return LD(*this, B, D, 1);
    case 0x43: return LD(*this, B, E, 1);
    case 0x44: return LD(*this, B, H, 1);
    case 0x45: return LD(*this, B, L, 1);
    case 0x46: return LD(*this, B, HLa, 1);
    case 0x47: return LD(*this, B, A, 1);
    case 0x48: return LD(*this, C, B, 1);
    case 0x49: return LD(*this, C, C, 1);
    case 0x4A: return LD(*this, C, D, 1);
    case 0x4B: return LD(*this, C, E, 1);
    case 0x4C: return LD(*this, C, H, 1);
    case 0x4D: return LD(*this, C, L, 1);
    case 0x4E: return LD(*this, C, HLa, 1);
    case 0x4F: return LD(*this, C, A, 1);
    case 0x50: return LD(*this, D, B, 1);
    case 0x51: return LD(*this, D, C, 1);
    case 0x52: return LD(*this, D, D, 1);
    case 0x53: return LD(*this, D, E, 1);
    case 0x54: return LD(*this, D, H, 1);
    case 0x55: return LD(*this, D, L, 1);
    case 0x56: return LD(*this, D, HLa, 1);
    case 0x57: return LD(*this, D, A, 1);
    case 0x58: return LD(*this, E, B, 1);
    case 0x59: return LD(*this, E, C, 1);
    case 0x5A: return LD(*this, E, D, 1);
    case 0x5B: return LD(*this, E, E, 1);
    case 0x5C: return LD(*this, E, H, 1);
    case 0x5D: return LD(*this, E, L, 1);
    case 0x5E: return LD(*this, E, HLa, 1);
    case 0x5F: return LD(*this, E, A, 1);
    case 0x60: return LD(*this, H, B, 1);
    case 0x61: return LD(*this, H, C, 1);
    case 0x62: return LD(*this, H, D, 1);
    case 0x63: return LD(*this, H, E, 1);
    case 0x64: return LD(*this, H, H, 1);
    case 0x65: return LD(*this, H, L, 1);
    case 0x66: return LD(*this, H, HLa, 1);
    case 0x67: return LD(*this, H, A, 1);
    case 0x68: return LD(*this, L, B, 1);
    case 0x69: return LD(*this, L, C, 1);
    case 0x6A: return LD(*this, L, D, 1);
    case 0x6B: return LD(*this, L, E, 1);
    case 0x6C: return LD(*this, L, H, 1);
    case 0x6D: return LD(*this, L, L, 1);
    case 0x6E: return LD(*this, L, HLa, 1);
    case 0x6F: return LD(*this, L, A, 1);
    case 0x70: return LD(*this, HLa, B, 1);
    case 0x71: return LD(*this, HLa, C, 1);
    case 0x72: return LD(*this, HLa, D, 1);
    case 0x73: return LD(*this, HLa, E, 1);
    case 0x74: return LD(*this, HLa, H, 1);
    case 0x75: return LD(*this, HLa, L, 1);
    case 0x77: return LD(*this, HLa, A, 1);
    case 0x78: return LD(*this, A, B, 1);
    case 0x79: return LD(*this, A, C, 1);
    case 0x7A: return LD(*this, A, D, 1);
    case 0x7B: return LD(*this, A, E, 1);
    case 0x7C: return LD(*this, A, H, 1);
    case 0x7D: return LD(*this, A, L, 1);
    case 0x7E: return LD(*this, A, HLa, 1);
    case 0x7F: return LD(*this, A, A, 1);
    case 0xE2: return LD(*this, Ca, A, 1);
    case 0xEA: return LD(*this, a16, A, 1);
    case 0xF2: return LD(*this, A, Ca, 1);
    case 0xFA: return LD(*this, A, a16, 1);
    case 0xE0: return LD(*this, a8, A, 1);
    case 0xF0: return LD(*this, A, a8, 1);
    case 0x09: return ADD(*this, HL, BC);
    case 0x19: return ADD(*this, HL, DE);
    case 0x29: return ADD(*this, HL, HL);
    case 0x39: return ADD(*this, HL, SP);
    case 0x80: return ADD(*this, A, B);
    case 0x81: return ADD(*this, A, C);
    case 0x82: return ADD(*this, A, D);
    case 0x83: return ADD(*this, A, E);
    case 0x84: return ADD(*this, A, H);
    case 0x85: return ADD(*this, A, L);
    case 0x86: return ADD(*this, A, HLa);
    case 0x87: return ADD(*this, A, A);
    case 0xC6: return ADD(*this, A, d8);
    case 0xE8: return ADD(*this, SP, r8);
    case 0x88: return ADC(*this, B);
    case 0x89: return ADC(*this, C);
    case 0x8A: return ADC(*this, D);
    case 0x8B: return ADC(*this, E);
    case 0x8C: return ADC(*this, H);
    case 0x8D: return ADC(*this, L);
    case 0x8E: return ADC(*this, HLa);
    case 0x8F: return ADC(*this, A);
    case 0xCE: return ADC(*this, d8);
    case 0x90: return SUB(*this, B);
    case 0x91: return SUB(*this, C);
    case 0x92: return SUB(*this, D);
    case 0x93: return SUB(*this, E);
    case 0x94: return SUB(*this, H);
    case 0x95: return SUB(*this, L);
    case 0x96: return SUB(*this, HLa);
    case 0x97: return SUB(*this, A);
    case 0xD6: return SUB(*this, d8);
    case 0x98: return SBC(*this, B);
    case 0x99: return SBC(*this, C);
    case 0x9A: return SBC(*this, D);
    case 0x9B: return SBC(*this, E);
    case 0x9C: return SBC(*this, H);
    case 0x9D: return SBC(*this, L);
    case 0x9E: return SBC(*this, HLa);
    case 0x9F: return SBC(*this, A);
    case 0xDE: return SBC(*this, d8);
    case 0xA0: return AND(*this, B);
    case 0xA1: return AND(*this, C);
    case 0xA2: return AND(*this, D);
    case 0xA3: return AND(*this, E);
    case 0xA4: return AND(*this, H);
    case 0xA5: return AND(*this, L);
    case 0xA6: return AND(*this, HLa);
    case 0xA7: return AND(*this, A);
    case 0xE6: return AND(*this, d8);
    case 0xB0: return OR(*this, B);
    case 0xB1: return OR(*this, C);
    case 0xB2: return OR(*this, D);
    case 0xB3: return OR(*this, E);
    case 0xB4: return OR(*this, H);
    case 0xB5: return OR(*this, L);
    case 0xB6: return OR(*this, HLa);
    case 0xB7: return OR(*this, A);
    case 0xF6: return OR(*this, d8);
    case 0xA8: return XOR(*this, B);
    case 0xA9: return XOR(*this, C);
    case 0xAA: return XOR(*this, D);
    case 0xAB: return XOR(*this, E);
    case 0xAC: return XOR(*this, H);
    case 0xAD: return XOR(*this, L);
    case 0xAE: return XOR(*this, HLa);
    case 0xAF: return XOR(*this, A);
    case 0xEE: return XOR(*this, d8);
    case 0x18: return JR(*this, jNONE);
    case 0x20: return JR(*this, jNZ);
    case 0x28: return JR(*this, jZ);
    case 0x30: return JR(*this, jNC);
    case 0x38: return JR(*this, jC);
    case 0xC2: return JP(*this, jNZ, a16);
    case 0xC3: return JP(*this, jNONE, a16);
    case 0xCA: return JP(*this, jZ, a16);
    case 0xD2: return JP(*this, jNC, a16);
    case 0xDA: return JP(*this, jC, a16);
    case 0xE9: return JP(*this, jNONE, HLa);
    case 0xC4: return CALL(*this, jNZ);
    case 0xCC: return CALL(*this, jZ);
    case 0xCD: return CALL(*this, jNONE);
    case 0xDC: return CALL(*this, jC);
    case 0xD4: return CALL(*this, jNC);
    case 0xB8: return CP(*this, B);
    case 0xB9: return CP(*this, C);
    case 0xBA: return CP(*this, D);
    case 0xBB: return CP(*this, E);
    case 0xBC: return CP(*this, H);
    case 0xBD: return CP(*this, L);
    case 0xBE: return CP(*this, HLa);
    case 0xBF: return CP(*this, A);
    case 0xFE: return CP(*this, d8);
    case 0xC0: return RET(*this, jNZ);
    case 0xC8: return RET(*this, jZ);
    case 0xC9: return RET(*this, jNONE);
    case 0xD0: return RET(*this, jNC);
    case 0xD8: return RET(*this, jC);
    case 0xD9: return RETI(*this);
    case 0xC7: return RST(*this, 0xC7); // RST 00H
    case 0xCF: return RST(*this, 0xCF); // RST 08H
    case 0xD7: return RST(*this, 0xD7); // RST 10H
    case 0xDF: return RST(*this, 0xDF); // RST 18H
    case 0xE7: return RST(*this, 0xE7); // RST 20H
    case 0xEF: return RST(*this, 0xEF); // RST 28H
    case 0xF7: return RST(*this, 0xF7); // RST 30H
    case 0xFF: return RST(*this, 0xFF); // RST 38H
    case 0xC1: return POP(*this, BC);
    case 0xD1: return POP(*this, DE);
    case 0xE1: return POP(*this, HL);
    case 0xF1: return POP(*this, AF);
    case 0xC5: return PUSH(*this, BC);
    case 0xD5: return PUSH(*this, DE);
    case 0xE5: return PUSH(*this, HL);
    case 0xF5: return PUSH(*this, AF);
    case 0x07: return RLCA(*this);
    case 0x0F: return RRCA(*this);
    case 0x10: return STOP(*this);
    case 0x17: return RLA(*this);
    case 0x1F: return RRA(*this);
    case 0x27: return DAA(*this);
    case 0x2F: return CPL(*this);
    case 0x37: return SCF(*this);
    case 0x3F: return CCF(*this);
    case 0x76: return HALT(*this);
    case 0xF3: return DI(*this);
    case 0xFB: return EI(*this);
    case 0x100: return RLC(*this, B);
    case 0x101: return RLC(*this, C);
    case 0x102: return RLC(*this, D);
    case 0x103: return RLC(*this, E);
    case 0x104: return RLC(*this, H);
    case 0x105: return RLC(*this, L);
    case 0x106: return RLC(*this, HLa);
    case 0x107: return RLC(*this, A);
    case 0x108: return RRC(*this, B);
    case 0x109: return RRC(*this, C);
    case 0x10A: return RRC(*this, D);
    case 0x10B: return RRC(*this, E);
    case 0x10C: return RRC(*this, H);
    case 0x10D: return RRC(*this, L);
    case 0x10E: return RRC(*this, HLa);
    case 0x10F: return RRC(*this, A);
    case 0x110: return RL(*this, B);
    case 0x111: return RL(*this, C);
    case 0x112: return RL(*this, D);
    case 0x113: return RL(*this, E);
    case 0x114: return RL(*this, H);
    case 0x115: return RL(*this, L);
    case 0x116: return RL(*this, HLa);
    case 0x117: return RL(*this, A);
    case 0x118: return RR(*this, B);
    case 0x119: return RR(*this, C);
    case 0x11A: return RR(*this, D);
    case 0x11B: return RR(*this, E);
    case 0x11C: return RR(*this, H);
    case 0x11D: return RR(*this, L);
    case 0x11E: return RR(*this, HLa);
    case 0x11F: return RR(*this, A);
    case 0x120: return SLA(*this, B);
    case 0x121: return SLA(*this, C);
    case 0x122: return SLA(*this, D);
    case 0x123: return SLA(*this, E);
    case 0x124: return SLA(*this, H);
    case 0x125: return SLA(*this, L);
    case 0x126: return SLA(*this, HLa);
    case 0x127: return SLA(*this, A);
    case 0x128: return SRA(*this, B);
    case 0x129: return SRA(*this, C);
    case 0x12A: return SRA(*this, D);
    case 0x12B: return SRA(*this, E);
    case 0x12C: return SRA(*this, H);
    case 0x12D: return SRA(*this, L);
    case 0x12E: return SRA(*this, HLa);
    case 0x12F: return SRA(*this, A);
    case 0x130: return SWAP(*this, B);
    case 0x131: return SWAP(*this, C);
    case 0x132: return SWAP(*this, D);
    case 0x133: return SWAP(*this, E);
    case 0x134: return SWAP(*this, H);
    case 0x135: return SWAP(*this, L);
    case 0x136: return SWAP(*this, HLa);
    case 0x137: return SWAP(*this, A);
    case 0x138: return SRL(*this, B);
    case 0x139: return SRL(*this, C);
    case 0x13A: return SRL(*this, D);
    case 0x13B: return SRL(*this, E);
    case 0x13C: return SRL(*this, H);
    case 0x13D: return SRL(*this, L);
    case 0x13E: return SRL(*this, HLa);
    case 0x13F: return SRL(*this, A);
    case 0x140: return BIT(*this, B, 1);
    case 0x141: return BIT(*this, C, 1);
    case 0x142: return BIT(*this, D, 1);
    case 0x143: return BIT(*this, E, 1);
    case 0x144: return BIT(*this, H, 1);
    case 0x145: return BIT(*this, L, 1);
    case 0x146: return BIT(*this, HLa, 1);
    case 0x147: return BIT(*this, A, 1);
    case 0x148: return BIT(*this, B, 2);
    case 0x149: return BIT(*this, C, 2);
    case 0x14A: return BIT(*this, D, 2);
    case 0x14B: return BIT(*this, E, 2);
    case 0x14C: return BIT(*this, H, 2);
    case 0x14D: return BIT(*this, L, 2);
    case 0x14E: return BIT(*this, HLa, 2);
    case 0x14F: return BIT(*this, A, 2);
    case 0x150: return BIT(*this, B, 4);
    case 0x151: return BIT(*this, C, 4);
    case 0x152: return BIT(*this, D, 4);
    case 0x153: return BIT(*this, E, 4);
    case 0x154: return BIT(*this, H, 4);
    case 0x155: return BIT(*this, L, 4);
    case 0x156: return BIT(*this, HLa, 4);
    case 0x157: return BIT(*this, A, 4);
    case 0x158: return BIT(*this, B, 8);
    case 0x159: return BIT(*this, C, 8);
    case 0x15A: return BIT(*this, D, 8);
    case 0x15B: return BIT(*this, E, 8);
    case 0x15C: return BIT(*this, H, 8);
    case 0x15D: return BIT(*this, L, 8);
    case 0x15E: return BIT(*this, HLa, 8);
    case 0x15F: return BIT(*this, A, 8);
    case 0x160: return BIT(*this, B, 16);
    case 0x161: return BIT(*this, C, 16);
    case 0x162: return BIT(*this, D, 16);
    case 0x163: return BIT(*this, E, 16);
    case 0x164: return BIT(*this, H, 16);
    case 0x165: return BIT(*this, L, 16);
    case 0x166: return BIT(*this, HLa, 16);
    case 0x167: return BIT(*this, A, 16);
    case 0x168: return BIT(*this, B, 32);
    case 0x169: return BIT(*this, C, 32);
    case 0x16A: return BIT(*this, D, 32);
    case 0x16B: return BIT(*this, E, 32);
    case 0x16C: return BIT(*this, H, 32);
    case 0x16D: return BIT(*this, L, 32);
    case 0x16E: return BIT(*this, HLa, 32);
    case 0x16F: return BIT(*this, A, 32);
    case 0x170: return BIT(*this, B, 64);
    case 0x171: return BIT(*this, C, 64);
    case 0x172: return BIT(*this, D, 64);
    case 0x173: return BIT(*this, E, 64);
    case 0x174: return BIT(*this, H, 64);
    case 0x175: return BIT(*this, L, 64);
    case 0x176: return BIT(*this, HLa, 64);
    case 0x177: return BIT(*this, A, 64);
    case 0x178: return BIT(*this, B, 128);
    case 0x179: return BIT(*this, C, 128);
    case 0x17A: return BIT(*this, D, 128);
    case 0x17B: return BIT(*this, E, 128);
    case 0x17C: return BIT(*this, H, 128);
    case 0x17D: return BIT(*this, L, 128);
    case 0x17E: return BIT(*this, HLa, 128);
    case 0x17F: return BIT(*this, A, 128);
    case 0x180: return RES(*this, B, 1);
    case 0x181: return RES(*this, C, 1);
    case 0x182: return RES(*this, D, 1);
    case 0x183: return RES(*this, E, 1);
    case 0x184: return RES(*this, H, 1);
    case 0x185: return RES(*this, L, 1);
    case 0x186: return RES(*this, HLa, 1);
    case 0x187: return RES(*this, A, 1);
    case 0x188: return RES(*this, B, 2);
    case 0x189: return RES(*this, C, 2);
    case 0x18A: return RES(*this, D, 2);
    case 0x18B: return RES(*this, E, 2);
    case 0x18C: return RES(*this, H, 2);
    case 0x18D: return RES(*this, L, 2);
    case 0x18E: return RES(*this, HLa, 2);
    case 0x18F: return RES(*this, A, 2);
    case 0x190: return RES(*this, B, 4);
    case 0x191: return RES(*this, C, 4);
    case 0x192: return RES(*this, D, 4);
    case 0x193: return RES(*this, E, 4);
    case 0x194: return RES(*this, H, 4);
    case 0x195: return RES(*this, L, 4);
    case 0x196: return RES(*this, HLa, 4);
    case 0x197: return RES(*this, A, 4);
    case 0x198: return RES(*this, B, 8);
    case 0x199: return RES(*this, C, 8);
    case 0x19A: return RES(*this, D, 8);
    case 0x19B: return RES(*this, E, 8);
    case 0x19C: return RES(*this, H, 8);
    case 0x19D: return RES(*this, L, 8);
    case 0x19E: return RES(*this, HLa, 8);
    case 0x19F: return RES(*this, A, 8);
    case 0x1A0: return RES(*this, B, 16);
    case 0x1A1: return RES(*this, C, 16);
    case 0x1A2: return RES(*this, D, 16);
    case 0x1A3: return RES(*this, E, 16);
    case 0x1A4: return RES(*this, H, 16);
    case 0x1A5: return RES(*this, L, 16);
    case 0x1A6: return RES(*this, HLa, 16);
    case 0x1A7: return RES(*this, A, 16);
    case 0x1A8: return RES(*this, B, 32);
    case 0x1A9: return RES(*this, C, 32);
    case 0x1AA: return RES(*this, D, 32);
    case 0x1AB: return RES(*this, E, 32);
    case 0x1AC: return RES(*this, H, 32);
    case 0x1AD: return RES(*this, L, 32);
    case 0x1AE: return RES(*this, HLa, 32);
    case 0x1AF: return RES(*this, A, 32);
    case 0x1B0: return RES(*this, B, 64);
    case 0x1B1: return RES(*this, C, 64);
    case 0x1B2: return RES(*this, D, 64);
    case 0x1B3: return RES(*this, E, 64);
    case 0x1B4: return RES(*this, H, 64);
    case 0x1B5: return RES(*this, L, 64);
    case 0x1B6: return RES(*this, HLa, 64);
    case 0x1B7: return RES(*this, A, 64);
    case 0x1B8: return RES(*this, B, 128);
    case 0x1B9: return RES(*this, C, 128);
    case 0x1BA: return RES(*this, D, 128);
    case 0x1BB: return RES(*this, E, 128);
    case 0x1BC: return RES(*this, H, 128);
    case 0x1BD: return RES(*this, L, 128);
    case 0x1BE: return RES(*this, HLa, 128);
    case 0x1BF: return RES(*this, A, 128);
    case 0x1C0: return SET(*this, B, 1);
    case 0x1C1: return SET(*this, C, 1);
    case 0x1C2: return SET(*this, D, 1);
    case 0x1C3: return SET(*this, E, 1);
    case 0x1C4: return SET(*this, H, 1);
    case 0x1C5: return SET(*this, L, 1);
    case 0x1C6: return SET(*this, HLa, 1);
    case 0x1C7: return SET(*this, A, 1);
    case 0x1C8: return SET(*this, B, 2);
    case 0x1C9: return SET(*this, C, 2);
    case 0x1CA: return SET(*this, D, 2);
    case 0x1CB: return SET(*this, E, 2);
    case 0x1CC: return SET(*this, H, 2);
    case 0x1CD: return SET(*this, L, 2);
    case 0x1CE: return SET(*this, HLa, 2);
    case 0x1CF: return SET(*this, A, 2);
    case 0x1D0: return SET(*this, B, 4);
    case 0x1D1: return SET(*this, C, 4);
    case 0x1D2: return SET(*this, D, 4);
    case 0x1D3: return SET(*this, E, 4);
    case 0x1D4: return SET(*this, H, 4);
    case 0x1D5: return SET(*this, L, 4);
    case 0x1D6: return SET(*this, HLa, 4);
    case 0x1D7: return SET(*this, A, 4);
    case 0x1D8: return SET(*this, B, 8);
    case 0x1D9: return SET(*this, C, 8);
    case 0x1DA: return SET(*this, D, 8);
    case 0x1DB: return SET(*this, E, 8);
    case 0x1DC: return SET(*this, H, 8);
    case 0x1DD: return SET(*this, L, 8);
    case 0x1DE: return SET(*this, HLa, 8);
    case 0x1DF: return SET(*this, A, 8);
    case 0x1E0: return SET(*this, B, 16);
    case 0x1E1: return SET(*this, C, 16);
    case 0x1E2: return SET(*this, D, 16);
    case 0x1E3: return SET(*this, E, 16);
    case 0x1E4: return SET(*this, H, 16);
    case 0x1E5: return SET(*this, L, 16);
    case 0x1E6: return SET(*this, HLa, 16);
    case 0x1E7: return SET(*this, A, 16);
    case 0x1E8: return SET(*this, B, 32);
    case 0x1E9: return SET(*this, C, 32);
    case 0x1EA: return SET(*this, D, 32);
    case 0x1EB: return SET(*this, E, 32);
    case 0x1EC: return SET(*this, H, 32);
    case 0x1ED: return SET(*this, L, 32);
    case 0x1EE: return SET(*this, HLa, 32);
    case 0x1EF: return SET(*this, A, 32);
    case 0x1F0: return SET(*this, B, 64);
    case 0x1F1: return SET(*this, C, 64);
    case 0x1F2: return SET(*this, D, 64);
    case 0x1F3: return SET(*this, E, 64);
    case 0x1F4: return SET(*this, H, 64);
    case 0x1F5: return SET(*this, L, 64);
    case 0x1F6: return SET(*this, HLa, 64);
    case 0x1F7: return SET(*this, A, 64);
    case 0x1F8: return SET(*this, B, 128);
    case 0x1F9: return SET(*this, C, 128);
    case 0x1FA: return SET(*this, D, 128);
    case 0x1FB: return SET(*this, E, 128);
    case 0x1FC: return SET(*this, H, 128);
    case 0x1FD: return SET(*this, L, 128);
    case 0x1FE: return SET(*this, HLa, 128);
    case 0x1FF: return SET(*this, A, 128);
    default:
        registers.PC++;
        return 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::interruptCall(uint8_t interrupt) {
    IME = false;
    registers.SP -= 2;
    writeMemory(registers.SP, registers.PC & 0xFF);
    writeMemory(registers.SP + 1, (registers.PC >> 8));
    registers.PC = interrupt;
    haltState = 0;
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::handleInterrupts() {
    if (IME) {
        if (readMemory(IEaddr) & readMemory(IFaddr) & 0b0001) { // VBLANK
            writeMemory(IFaddr, readMemory(IFaddr) & 0b1110);
            interruptCall(0x40);
        }
        if (readMemory(IEaddr) & readMemory(IFaddr) & 0b0010) { // LCD STAT
            writeMemory(IFaddr, readMemory(IFaddr) & 0b1101);
            interruptCall(0x48);
        }
        if (readMemory(IEaddr) & readMemory(IFaddr) & 0b0100) { // TIMER
            writeMemory(IFaddr, readMemory(IFaddr) & 0b1011);
            interruptCall(0x50);
        }
        if (readMemory(IEaddr) & readMemory(IFaddr) & 0b1000) { // SERIAL
            writeMemory(IFaddr, readMemory(IFaddr) & 0b0111);
            interruptCall(0x58);
        }
        if (readMemory(IEaddr) & readMemory(IFaddr) & 0b10000) { // JOYPAD
            writeMemory(IFaddr, readMemory(IFaddr) & 0b1110);
            interruptCall(0x60);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::setInterrupt(int interrupt) {
    switch (interrupt) {
    case 1:
        writeMemory(IFaddr, readMemory(IFaddr) | 0b0001);
        break;
    case 2:
        writeMemory(IFaddr, readMemory(IFaddr) | 0b0010);
        break;
    case 3:
        writeMemory(IFaddr, readMemory(IFaddr) | 0b0100);
        break;
    case 4:
        writeMemory(IFaddr, readMemory(IFaddr) | 0b1000);
        break;
    case 5:
        writeMemory(IFaddr, readMemory(IFaddr) | 0b10000);
        break;
    }
}


/////////////////////////////////////////////////////////////////////////////////////
void CPU::update() {
    int sumCycles = 0;
    int cycles = 0;
    while (sumCycles < maxCycles) {
        if (haltState) {
            cycles = 4;
            sumCycles += cycles;
            if (haltState == 2 && (readMemory(IEaddr) & readMemory(IFaddr) & 0x1F))
            {
                haltState = 0;
            }
        }
        else if (stopped) {
            sumCycles += 4;
        }
        else {
            cycles = runNextOpcode();
            sumCycles += cycles;
        }

        updateTimers(cycles);
        updateGraphics(cycles);
        if (haltBugPC != 0) {
            registers.PC = haltBugPC;
            haltBugPC = 0;
        }
        handleInterrupts();
        
        //printRegisters();
    }
    renderer.prepareScene();
    renderer.loadBitmap(screenData);
    renderer.presentScene();
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::setClockFrequency() {

    switch (getClockFrequency()) {
    case 0:
        timerCounter = 1024;
        break;
    case 1:
        timerCounter = 16;
        break;
    case 2:
        timerCounter = 64;
        break;
    case 3:
        timerCounter = 256;
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
uint8_t CPU::getClockFrequency() {
    return (readMemory(TMCaddr) & 0x3);
}

/////////////////////////////////////////////////////////////////////////////////////
bool CPU::isClockEnabled() {
    return (readMemory(TMCaddr) & 0b100);
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::updateTimers(int cycles) {
    DoDividerRegister(cycles);
    if (isClockEnabled()) {
        timerCounter -= cycles;

        while (timerCounter <= 0) { // while or if? not sure
            setClockFrequency();

            if (readMemory(TIMAaddr) == 0xFF) {
                writeMemory(TIMAaddr, readMemory(TMAaddr));
                setInterrupt(3);
            }
            else {
                writeMemory(TIMAaddr, readMemory(TIMAaddr) + 1);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::DoDividerRegister(int cycles) {
    dividerCounter += cycles;

    if (dividerCounter >= 255) {
        dividerCounter = 0;
        memory[DIVaddr] += 1;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::updateGraphics(int cycles) {
    setLCDStatus();

    if (isLCDOn()) {
        scanlineCounter -= cycles;
    }
    else
    {
        return;
    }

    if (scanlineCounter <= 0) {
        memory[0xFF44] += 1; // write memory resets current scanline to 0
        uint8_t currentLine = readMemory(0xFF44);

        scanlineCounter = 456;

        if (currentLine == 144) {
            setInterrupt(1);
        }
        else if (currentLine > 153) {
            writeMemory(0xFF44, 0);
        }
        else if (currentLine < 144) {
            drawScanline();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::setLCDStatus() {
    uint8_t status = readMemory(0xFF41);

    if (!isLCDOn()) // set LCD mode to 1 when LCD is disabled and reset scanline counter
    {
        scanlineCounter = 456;
        writeMemory(0xFF44, 0);
        status &= 0b11111100;
        status |= 0b00000001;
        writeMemory(0xFF41, status);
        return;
    }

    uint8_t currentLine = readMemory(0xFF44);
    uint8_t currentMode = status & 0b00000011;

    uint8_t mode = 0;
    bool reqInt = false;

    if (currentLine >= 144) // VBLANK
    {
        mode = 1;
        status |= 0b00000001;
        status &= 0b11111101;
        reqInt = (status & 0b00010000) != 0;
    }
    else
    {
        if (scanlineCounter >= 376) // mode 2 (376 = bounds)
        {
            mode = 2;
            status |= 0b00000010;
            status &= 0b11111110;
            reqInt = (status & 0b00100000) != 0;
        }
        else if (scanlineCounter >= 204) // mode 3 (204 = bounds)
        {
            mode = 3;
            status |= 0b00000011;
        }
        else // mode 0
        {
            mode = 0;
            status &= 0b11111100;
            reqInt = (status & 0b00001000) != 0;
        }
    }

    if (reqInt && mode != currentMode)
    {
        setInterrupt(2);
    }

    if (currentLine == readMemory(0xFF45)) // coincidence flag
    {
        status |= 0b00000100;
        if ((status & 0b01000000) != 0) // coincidence interrupt
        {
            setInterrupt(2);
        }
    }
    else
    {
        status &= 0b11111011;
    }
    writeMemory(0xFF41, status);
}

/////////////////////////////////////////////////////////////////////////////////////
bool CPU::isLCDOn() {
    return (readMemory(0xFF40) & 0b10000000);
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::drawScanline() {
    uint8_t LCDCtrl = readMemory(0xFF40);
    if ((LCDCtrl & 0b00000001) != 0) // background enabled
    {
        drawBackground();
    }
    if ((LCDCtrl & 0b00000010) != 0) // sprites enabled
    {
        drawSprites();
    }
}

/////////////////////////////////////////////////////////////////////////////////////

void CPU::drawBackground() {
    uint16_t tileData = 0;
    uint16_t backgroundMemory = 0;
    bool unsig = true;

    uint8_t scrollY = readMemory(0xFF42);
    uint8_t scrollX = readMemory(0xFF43);
    uint8_t windowY = readMemory(0xFF4A);
    uint8_t windowX = readMemory(0xFF4B) - 7;

    bool usingWindow = false;

    if ((readMemory(0xFF40) & 0b00100000) != 0) // window enabled, is it correct bit?
    {
        if (windowY <= readMemory(0xFF44)) // window is on current scanline
        {
            usingWindow = true;
        }
    }

    if ((readMemory(0xFF40) & 0b00010000) != 0) // unsigned tile data
    {
        tileData = 0x8000;
    }
    else // signed tile data
    {
        tileData = 0x8800;
        unsig = false;
    }

    if (!usingWindow) {
        if ((readMemory(0xFF40) & 0b00001000) != 0) // tile map display select
        {
            backgroundMemory = 0x9C00;
        }
        else
        {
            backgroundMemory = 0x9800;
        }
    }
    else
    {
        if ((readMemory(0xFF40) & 0b01000000) != 0) // window tile map display select
        {
            backgroundMemory = 0x9C00;
        }
        else
        {
            backgroundMemory = 0x9800;
        }
    }

    uint8_t yPos = 0;

    if (!usingWindow) {
        yPos = scrollY + readMemory(0xFF44);
    }
    else
    {
        yPos = readMemory(0xFF44) - windowY;
    }

    uint16_t tileRow = (((uint8_t)(yPos / 8)) * 32);


    for (int pixel = 0; pixel < 160; pixel++) {
        uint8_t xPos = pixel + scrollX;

        if (usingWindow) {
            if (pixel >= windowX) {
                xPos = pixel - windowX;
            }
        }

        uint16_t tileCol = (xPos / 8);
        int16_t tileNum;

        uint16_t tileAddr = backgroundMemory + tileRow + tileCol;

        if (unsig) {
            tileNum = (uint8_t)readMemory(tileAddr);
        }
        else
        {
            tileNum = (int8_t)readMemory(tileAddr);
        }

        uint16_t tileLocation = tileData;

        if (unsig) {
            tileLocation += (tileNum * 16);
        }
        else
        {
            tileLocation += ((tileNum + 128) * 16);
        }

        // find correct vertical line
        uint8_t line = yPos % 8;
        line *= 2;

        uint8_t data1 = readMemory(tileLocation + line);
        uint8_t data2 = readMemory(tileLocation + line + 1);

        int colorBit = xPos % 8;
        colorBit -= 7;
        colorBit *= -1;

        // combine data 1 and data 2 to get color number for pixel
        int colorNum = (data2 >> colorBit) & 0b1;
        colorNum <<= 1;
        colorNum |= (data1 >> colorBit) & 0b1;

        Color col = getColorBG(colorNum);
        int red = 0;
        int green = 0;
        int blue = 0;

        switch (col)
        {
        case WHITE:
            red = 0xFF;
            green = 0xFF;
            blue = 0xFF;
            break;
        case LIGHT_GRAY:
            red = 0xCC;
            green = 0xCC;
            blue = 0xCC;
            break;
        case DARK_GRAY:
            red = 0x77;
            green = 0x77;
            blue = 0x77;
            break;
        case BLACK:
            red = 0x00;
            green = 0x00;
            blue = 0x00;
            break;
        }

        int finaly = readMemory(0xFF44);

        if (finaly < 0 || finaly > 143 || pixel < 0 || pixel > 159) {
            continue;
        }
        screenData[160 * finaly + pixel] = 0xFF000000 | (red << 16) | (green << 8) | blue;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::drawSprites() {
    bool use8x16 = false;
    if ((readMemory(0xFF40) & 0b00000100) != 0) // sprite size
    {
        use8x16 = true;
    }

    for (int sprite = 0; sprite < 40; sprite++) {
        uint8_t index = sprite * 4;
        uint8_t yPos = readMemory(0xFE00 + index) - 16;
        uint8_t xPos = readMemory(0xFE00 + index + 1) - 8;
        uint8_t tileLocation = readMemory(0xFE00 + index + 2);
        uint8_t attributes = readMemory(0xFE00 + index + 3);

        bool yFlip = (attributes & 0b01000000) != 0;
        bool xFlip = (attributes & 0b00100000) != 0;

        int scanline = readMemory(0xFF44);

        int ysize = 8;
        if (use8x16) {
            ysize = 16;
        }

        if ((scanline >= yPos) && (scanline < (yPos + ysize)))
        {
            int line = scanline - yPos;

            if (yFlip) {
                line -= ysize;
                line *= -1;
            }

            line *= 2;
            uint16_t dataAddress = (0x8000 + (tileLocation * 16)) + line;
            uint8_t data1 = readMemory(dataAddress);
            uint8_t data2 = readMemory(dataAddress + 1);

            for (int tilePixel = 7; tilePixel >= 0; tilePixel--)
            {
                int colorBit = tilePixel;

                if (xFlip) {
                    colorBit -= 7;
                    colorBit *= -1;
                }
                int colorNum = (data2 >> colorBit) & 0b1;
                colorNum <<= 1;
                colorNum |= (data1 >> colorBit) & 0b1;

                uint16_t colorAddress = 0xFF48 + ((attributes >> 4) & 0b00000001); // select palette
                Color col = getColorSprite(colorNum, colorAddress);

                if (col == TRANSPARENT) {
                    continue;
                }
                int red = 0, green = 0, blue = 0;

                switch (col) {
                case WHITE:
                    red = 0xFF;
                    green = 0xFF;
                    blue = 0xFF;
                    break;
                case LIGHT_GRAY:
                    red = 0xCC;
                    green = 0xCC;
                    blue = 0xCC;
                    break;
                case DARK_GRAY:
                    red = 0x77;
                    green = 0x77;
                    blue = 0x77;
                    break;
                case BLACK:
                    red = 0x00;
                    green = 0x00;
                    blue = 0x00;
                    break;
                }

                int xPix = 0 - tilePixel;
                xPix += 7;

                int pixel = xPos + xPix;

                if (scanline < 0 || scanline > 143 || pixel < 0 || pixel > 159) {
                    continue;
                }
                uint32_t finalPixel = 0xFF000000 | (red << 16) | (green << 8) | blue;
                screenData[160 * scanline + pixel] = finalPixel;
            }
        }
    }
}



/////////////////////////////////////////////////////////////////////////////////////
Color CPU::getColorSprite(uint8_t colorNum, uint16_t address) {   
    uint8_t palette = readMemory(address);

    switch (colorNum)
    {
    case 0:
        palette &= 0b00000011;
        return TRANSPARENT;
        break;
    case 1:
        palette &= 0b00001100;
        palette >>= 2;
        break;
    case 2:
        palette &= 0b00110000;
        palette >>= 4;
        break;
    case 3:
        palette &= 0b11000000;
        palette >>= 6;
        break;
    }
    return static_cast<Color>(palette);
}


/////////////////////////////////////////////////////////////////////////////////////
Color CPU::getColor(uint8_t colorNum, uint16_t address) {
    uint8_t palette = readMemory(address);
    int hi = 0;
    int lo = 0;

    switch (colorNum)
    {
    case 0:
        hi = 1;
        lo = 0;
        break;
    case 1:
        hi = 3;
        lo = 2;
        break;
    case 2:
        hi = 5;
        lo = 4;
        break;
    case 3:
        hi = 7;
        lo = 6;
        break;
    }

    int color = 0;
    color = (palette >> hi) & 0b1;
    color <<= 1;
    color |= (palette >> lo) & 0b1;

    switch (color)
    {
    case 0:
        return WHITE;
        break;
    case 1:
        return LIGHT_GRAY;
        break;
    case 2:
        return DARK_GRAY;
        break;
    case 3:
        return BLACK;
        break;
    }
    return WHITE;
}

/////////////////////////////////////////////////////////////////////////////////////
Color CPU::getColorBG(uint8_t colorNum) {   
    uint8_t palette = readMemory(0xFF47);
    palette >>= (colorNum * 2);
    palette &= 0b00000011;
    return static_cast<Color>(palette);
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::handleBanking(uint16_t addr, uint8_t value) {
    if (addr < 0x2000 && MBC > 0) { // Enable RAM
        if ((MBC == 2) && (addr & 0b00010000)) return;

        if ((value & 0xF) == 0xA) {
            enableRAM = true;
        }
        else if ((value & 0xF) == 0x0) {
            enableRAM = false;
        }
    }
    else if ((addr >= 0x2000) && (addr < 0x4000) && (MBC > 0)) { // ROM Bank
        if (MBC == 2) {
            selectedROMBank = value & 0xF;
        }
        else {
            selectedROMBank &= 0b11100000;
            selectedROMBank |= (value & 0b00011111);
        }
        if (selectedROMBank == 0) selectedROMBank = 1;
    }
    else if ((addr >= 0x4000) && (addr < 0x6000) && (MBC == 1)) { // ROM/RAM Mode Select
        if (ROMBanking) {
            selectedROMBank &= 0b00011111;
            selectedROMBank |= (value & 0b11100000);
            if (selectedROMBank == 0) selectedROMBank = 1;
        }
        else {
            selectedRAMBank = value & 0b11;
        }
    }
    else if ((addr >= 0x6000) && (addr < 0x8000) && (MBC = 1)) {
        ROMBanking = (value & 0x1) == 0;
        if (ROMBanking) selectedRAMBank = 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::keyPressed(uint8_t keyMask) {
    bool previouslyUnset = false;
    if ((readMemory(0xFF00) & keyMask) == 0) {
        previouslyUnset = true;
    }

    joypadState &= ~keyMask;

    bool buttonType = true;

    if (keyMask & 0xF0) {
        buttonType = true; // Regular
    }
    else {
        buttonType = false; // Directional
    }

    uint8_t request = readMemory(0xFF00);
    bool requestInterrupt = false;

    if (buttonType && !(request & 0b00100000)) {
        requestInterrupt = true;
    }
    else if (!buttonType && !(request & 0b00100000)) {
        requestInterrupt = true;
    }

    if (!previouslyUnset && requestInterrupt) {
        setInterrupt(5);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::keyReleased(uint8_t keyMask) {
    joypadState |= keyMask;
}

/////////////////////////////////////////////////////////////////////////////////////
uint8_t CPU::getJoypadState() {
    uint8_t res = memory[0xFF00]; // Get current state of joypad register

    res ^= 0xFF;

    if ((res & 0b00010000) == 0) { // standard buttons
        res &= ((joypadState >> 4) | 0xF0);
    }
    else if ((res & 0b00100000) == 0) { // directional buttons
        res &= ((joypadState & 0xF) | 0xF0);
    }
    return res;
}

/////////////////////////////////////////////////////////////////////////////////////
void CPU::printRegisters() {
    std::cout << "A:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)*registers.A;
    std::cout << " F:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)*registers.F;
    std::cout << " B:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)*registers.B;
    std::cout << " C:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)*registers.C;
    std::cout << " D:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)*registers.D;
    std::cout << " E:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)*registers.E;
    std::cout << " H:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)*registers.H;
    std::cout << " L:" << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)*registers.L;
    std::cout << " SP:" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << (int)registers.SP;
    std::cout << " PC:" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << (int)registers.PC;
    std::cout << " PCMEM:" << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)readMemory(registers.PC) << "," << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)readMemory(registers.PC + 1) << "," << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)readMemory(registers.PC + 2) << "," << std::hex << std::uppercase << std::setfill('0') << std::setw(2) << (int)readMemory(registers.PC + 3) << std::endl;
}




/////////////////////////////////////////////////////////////////////////////////////
void CPU::loop() {
    while (renderer.handleInput(*this)) {
        update();
    }
}