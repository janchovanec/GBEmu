#include "../include/instructions.h"
    
// Increment register or memory
int Instr::INC(CPU& cpu, Operand operand1)
{
    int cycles = 4;
    switch (operand1)
    {
    case BC:
        cpu.registers.BC += 1;
        cycles = 8;
        break;
    case DE:
        cpu.registers.DE += 1;
        cycles = 8;
        break;
    case HL:
        cpu.registers.HL += 1;
        cycles = 8;
        break;
    case SP:
        cpu.registers.SP += 1;
        cycles = 8;
        break;
    case HLa:
        *cpu.registers.F = (*cpu.registers.F & 0b00011111);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(cpu.readMemory(cpu.registers.HL), 1);
        cpu.writeMemory(cpu.registers.HL, cpu.readMemory(cpu.registers.HL) + 1);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(cpu.readMemory(cpu.registers.HL));
        cycles = 12;
        break;
    case B:
        *cpu.registers.F = (*cpu.registers.F & 0b00011111);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.B, 1);
        *cpu.registers.B += 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.B);
        break;
    case H:
        *cpu.registers.F = (*cpu.registers.F & 0b00011111);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.H, 1);
        *cpu.registers.H += 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.H);
        break;
    case C:
        *cpu.registers.F = (*cpu.registers.F & 0b00011111);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.C, 1);
        *cpu.registers.C += 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.C);
        break;
    case D:
        *cpu.registers.F = (*cpu.registers.F & 0b00011111);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.D, 1);
        *cpu.registers.D += 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.D);
        break;
    case E:
        *cpu.registers.F = (*cpu.registers.F & 0b00011111);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.E, 1);
        *cpu.registers.E += 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.E);
        break;
    case L:
        *cpu.registers.F = (*cpu.registers.F & 0b00011111);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.L, 1);
        *cpu.registers.L += 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.L);
        break;
    case A:
        *cpu.registers.F = (*cpu.registers.F & 0b00011111);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, 1);
        *cpu.registers.A += 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Decrement register or memory
int Instr::DEC(CPU& cpu, Operand operand1)
{
    int cycles = 4;
    switch (operand1)
    {
    case BC:
        cpu.registers.BC -= 1;
        cycles = 8;
        break;
    case DE:
        cpu.registers.DE -= 1;
        cycles = 8;
        break;
    case HL:
        cpu.registers.HL -= 1;
        cycles = 8;
        break;
    case SP:
        cpu.registers.SP -= 1;
        cycles = 8;
        break;
    case HLa:
        *cpu.registers.F = (*cpu.registers.F & 0b01011111) | 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(cpu.readMemory(cpu.registers.HL), 1);
        cpu.writeMemory(cpu.registers.HL, cpu.readMemory(cpu.registers.HL) - 1);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(cpu.readMemory(cpu.registers.HL));
        cycles = 12;
        break;
    case B:
        *cpu.registers.F = (*cpu.registers.F & 0b01011111) | 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.B, 1);
        *cpu.registers.B -= 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.B);

        break;
    case H:
        *cpu.registers.F = (*cpu.registers.F & 0b01011111) | 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.H, 1);
        *cpu.registers.H -= 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.H);
        break;
    case C:
        *cpu.registers.F = (*cpu.registers.F & 0b01011111) | 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.C, 1);
        *cpu.registers.C -= 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.C);
        break;
    case D:
        *cpu.registers.F = (*cpu.registers.F & 0b01011111) | 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.D, 1);
        *cpu.registers.D -= 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.D);
        break;
    case E:
        *cpu.registers.F = (*cpu.registers.F & 0b01011111) | 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.E, 1);
        *cpu.registers.E -= 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.E);
        break;
    case L:
        *cpu.registers.F = (*cpu.registers.F & 0b01011111) | 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.L, 1);
        *cpu.registers.L -= 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.L);
        break;
    case A:
        *cpu.registers.F = (*cpu.registers.F & 0b01011111) | 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, 1);
        *cpu.registers.A -= 1;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    }

    cpu.registers.PC += 1;

    return cycles;
}

// No operation
int Instr::NOP(CPU& cpu)
{
    cpu.registers.PC += 1;

    return 4;
}

// Load register or memory
int Instr::LD(CPU& cpu, Operand operand1, Operand operand2, int type)
{
    int cycles = 4;

    if (type == 1) {
        uint8_t value;
        switch (operand2) {// get value
        case A:
            value = *cpu.registers.A;
            break;
        case B:
            value = *cpu.registers.B;
            break;
        case C:
            value = *cpu.registers.C;
            break;
        case D:
            value = *cpu.registers.D;
            break;
        case E:
            value = *cpu.registers.E;
            break;
        case H:
            value = *cpu.registers.H;
            break;
        case L:
            value = *cpu.registers.L;
            break;
        case a16:
            value = cpu.readMemory(cpu.readMemory(cpu.registers.PC + 1) + (cpu.readMemory(cpu.registers.PC + 2) << 8));
            cpu.registers.PC += 2;
            cycles = 16;
            break;
        case a8:
            value = cpu.readMemory(0xFF00 + cpu.readMemory(cpu.registers.PC + 1));
            cpu.registers.PC += 1;
            cycles = 12;
            break;
        case d8:
            value = cpu.readMemory(cpu.registers.PC + 1);
            cpu.registers.PC += 1;
            cycles = 8;
            break;
        case BCa:
            value = cpu.readMemory(cpu.registers.BC);
            cycles = 8;
            break;
        case DEa:
            value = cpu.readMemory(cpu.registers.DE);
            cycles = 8;
            break;
        case HLa:
            value = cpu.readMemory(cpu.registers.HL);
            cycles = 8;
            break;
        case Ca:
            value = cpu.readMemory(0xFF00 + *cpu.registers.C);
            cycles = 8;
            break;
        case HLi:
            value = cpu.readMemory(cpu.registers.HL);
            cpu.registers.HL += 1;
            cycles = 8;
            break;
        case HLd:
            value = cpu.readMemory(cpu.registers.HL);
            cpu.registers.HL -= 1;
            cycles = 8;
            break;
        default:
            break;
        }

        switch (operand1) {// set value
        case A:
            *cpu.registers.A = value;
            break;
        case B:
            *cpu.registers.B = value;
            break;
        case C:
            *cpu.registers.C = value;
            break;
        case D:
            *cpu.registers.D = value;
            break;
        case E:
            *cpu.registers.E = value;
            break;
        case H:
            *cpu.registers.H = value;
            break;
        case L:
            *cpu.registers.L = value;
            break;
        case a16:
            cpu.writeMemory(cpu.readMemory(cpu.registers.PC + 1) + (cpu.readMemory(cpu.registers.PC + 2) << 8), value);
            cpu.registers.PC += 2;
            cycles = 16;
            break;
        case a8:
            cpu.writeMemory(0xFF00 | cpu.readMemory(cpu.registers.PC + 1), value);
            cpu.registers.PC += 1;
            cycles = 12;
            break;
        case BCa:
            cpu.writeMemory(cpu.registers.BC, value);
            cycles = 8;
            break;
        case DEa:
            cpu.writeMemory(cpu.registers.DE, value);
            cycles = 8;
            break;
        case HLa:
            cpu.writeMemory(cpu.registers.HL, value);
            cycles = 8;
            break;
        case Ca:
            cpu.writeMemory(0xFF00 + *cpu.registers.C, value);
            cycles = 8;
            break;
        case HLi:
            cpu.writeMemory(cpu.registers.HL, value);
            cpu.registers.HL += 1;
            cycles = 8;
            break;
        case HLd:
            cpu.writeMemory(cpu.registers.HL, value);
            cpu.registers.HL -= 1;
            cycles = 8;
            break;
        default:
            break;
        }
    }
    else if (type == 2) {
        uint16_t value;
        switch (operand2) {// get value
        case HL:
            value = cpu.registers.HL;
            break;
        case SP:
            value = cpu.registers.SP;
            break;
        case d16:
            value = cpu.readMemory(cpu.registers.PC + 1) + (cpu.readMemory(cpu.registers.PC + 2) << 8);
            cpu.registers.PC += 2;
            cycles = 12;
            break;
        case SPr8:
            value = cpu.registers.SP + (int8_t)cpu.readMemory(cpu.registers.PC + 1);
            *cpu.registers.F = 0;
            *cpu.registers.F |= HalfCarryOnAddition(cpu.registers.SP, (int8_t)cpu.readMemory(cpu.registers.PC + 1)); // half carry
            *cpu.registers.F |= CarryOnAddition(cpu.registers.SP, (int8_t)cpu.readMemory(cpu.registers.PC + 1)); // carry
            cpu.registers.PC += 1;
            cycles = 12;
            break;
        default:
            break;
        }

        switch (operand1) {// set value
        case BC:
            cpu.registers.BC = value;
            break;
        case DE:
            cpu.registers.DE = value;
            break;
        case HL:
            cpu.registers.HL = value;
            break;
        case SP:
            cpu.registers.SP = value;
            break;
        case a16: // only SP can be written to a16
            cpu.writeMemory(cpu.readMemory(cpu.registers.PC + 1) + (cpu.readMemory(cpu.registers.PC + 2) << 8), value & 0x00FF);
            cpu.writeMemory(cpu.readMemory(cpu.registers.PC + 1) + (cpu.readMemory(cpu.registers.PC + 2) << 8) + 1, value >> 8);
            cpu.registers.PC += 2;
            cycles = 16;
            break;
        default:
            break;
        }
    }

    cpu.registers.PC += 1;
    return cycles;
}

// Add operand2 to operand1
int Instr::ADD(CPU& cpu, Operand operand1, Operand operand2)
{
    int cycles = 4;
    uint16_t source;
    switch (operand2)
    {
    case A:
        source = *cpu.registers.A & 0x00FF;
        break;
    case B:
        source = *cpu.registers.B & 0x00FF;
        break;
    case C:
        source = *cpu.registers.C & 0x00FF;
        break;
    case D:
        source = *cpu.registers.D & 0x00FF;
        break;
    case E:
        source = *cpu.registers.E & 0x00FF;
        break;
    case H:
        source = *cpu.registers.H & 0x00FF;
        break;
    case L:
        source = *cpu.registers.L & 0x00FF;
        break;
    case BC:
        source = cpu.registers.BC;
        break;
    case DE:
        source = cpu.registers.DE;
        break;
    case HL:
        source = cpu.registers.HL;
        break;
    case SP:
        source = cpu.registers.SP;
        break;
    case HLa:
        source = cpu.readMemory(cpu.registers.HL);
        cycles = 8;
        break;
    case d8:
        source = cpu.readMemory(cpu.registers.PC + 1);
        cpu.registers.PC += 1;
        cycles = 8;
        break;
    case r8:
        source = cpu.readMemory(cpu.registers.PC + 1);
        cpu.registers.PC += 1;
        cycles = 16;
        break;
    default:
        break;
    }

    switch (operand1)
    {
    case A:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, (uint8_t)source);
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(*cpu.registers.A, (uint8_t)source);
        *cpu.registers.A = *cpu.registers.A + (uint8_t)source;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case HL:
        *cpu.registers.F = *cpu.registers.F & 0b10000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition16((uint16_t)cpu.registers.HL, (uint16_t)source);
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition16(cpu.registers.HL, (uint16_t)source);
        cpu.registers.HL = cpu.registers.HL + (uint16_t)source;
        cycles = 8;
        break;
    case SP:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition((uint16_t)cpu.registers.SP, (int16_t)source);
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(cpu.registers.SP, (int16_t)source);
        cpu.registers.SP = cpu.registers.SP + (int8_t)source;
        break;
    default:
        break;
    }

    cpu.registers.PC += 1;

    return cycles;
}

// Add operand2 and carry flag to accumulator
int Instr::ADC(CPU& cpu, Operand operand2)
{
    int cycles = 4;
    uint8_t carry = (*cpu.registers.F >> 4) & 1;
    switch (operand2)
    {
    case A:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(*cpu.registers.A, *cpu.registers.A, carry);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, *cpu.registers.A, carry);
        *cpu.registers.A = *cpu.registers.A + *cpu.registers.A + carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(*cpu.registers.A, *cpu.registers.B, carry);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, *cpu.registers.B, carry);
        *cpu.registers.A = *cpu.registers.A + *cpu.registers.B + carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case C:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(*cpu.registers.A, *cpu.registers.C, carry);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, *cpu.registers.C, carry);
        *cpu.registers.A = *cpu.registers.A + *cpu.registers.C + carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case D:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(*cpu.registers.A, *cpu.registers.D, carry);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, *cpu.registers.D, carry);
        *cpu.registers.A = *cpu.registers.A + *cpu.registers.D + carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case E:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(*cpu.registers.A, *cpu.registers.E, carry);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, *cpu.registers.E, carry);
        *cpu.registers.A = *cpu.registers.A + *cpu.registers.E + carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case H:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(*cpu.registers.A, *cpu.registers.H, carry);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, *cpu.registers.H, carry);
        *cpu.registers.A = *cpu.registers.A + *cpu.registers.H + carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case L:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(*cpu.registers.A, *cpu.registers.L, carry);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, *cpu.registers.L, carry);
        *cpu.registers.A = *cpu.registers.A + *cpu.registers.L + carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case HLa:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(*cpu.registers.A, cpu.readMemory(cpu.registers.HL), carry);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, cpu.readMemory(cpu.registers.HL), carry);
        *cpu.registers.A = *cpu.registers.A + cpu.readMemory(cpu.registers.HL) + carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cycles = 8;
        break;
    case d8:
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | CarryOnAddition(*cpu.registers.A, cpu.readMemory(cpu.registers.PC + 1), carry);
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnAddition(*cpu.registers.A, cpu.readMemory(cpu.registers.PC + 1), carry);
        *cpu.registers.A = *cpu.registers.A + cpu.readMemory(cpu.registers.PC + 1) + carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cpu.registers.PC += 1;
        cycles = 8;
        break;
    default:
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Subtract register or value from accumulator
int Instr::SUB(CPU& cpu, Operand operand1)
{
    int cycles = 4;
    switch (operand1)
    {
    case A:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.A);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.A);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.A;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.B);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.B);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.B;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case C:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.C);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.C);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.C;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case D:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.D);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.D);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.D;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case E:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.E);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.E);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.E;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case H:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.H);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.H);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.H;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case L:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.L);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.L);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.L;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case HLa:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.HL));
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.HL));
        *cpu.registers.A = *cpu.registers.A - cpu.readMemory(cpu.registers.HL);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cycles = 8;
        break;
    case d8:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.PC + 1));
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.PC + 1));
        *cpu.registers.A = *cpu.registers.A - cpu.readMemory(cpu.registers.PC + 1);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cpu.registers.PC += 1;
        cycles = 8;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Subtract operand2 and carry flag from accumulator
int Instr::SBC(CPU& cpu, Operand operand1)
{
    int cycles = 4;
    uint8_t carry = (*cpu.registers.F >> 4) & 1;
    switch (operand1)
    {
    case A:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.A, carry);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.A, carry);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.A - carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.B, carry);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.B, carry);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.B - carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case C:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.C, carry);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.C, carry);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.C - carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case D:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.D, carry);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.D, carry);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.D - carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case E:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.E, carry);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.E, carry);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.E - carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case H:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.H, carry);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.H, carry);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.H - carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case L:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.L, carry);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.L, carry);
        *cpu.registers.A = *cpu.registers.A - *cpu.registers.L - carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case HLa:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.HL), carry);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.HL), carry);
        *cpu.registers.A = *cpu.registers.A - cpu.readMemory(cpu.registers.HL) - carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cycles = 8;
        break;
    case d8:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.PC + 1), carry);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.PC + 1), carry);
        *cpu.registers.A = *cpu.registers.A - cpu.readMemory(cpu.registers.PC + 1) - carry;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cpu.registers.PC += 1;
        cycles = 8;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// AND operand2 with accumulator and store result in accumulator
int Instr::AND(CPU& cpu, Operand operand1)
{
    int cycles = 4;
    switch (operand1)
    {
    case A:
        *cpu.registers.A = *cpu.registers.A & *cpu.registers.A;
        *cpu.registers.F = 0b00100000;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.A = *cpu.registers.A & *cpu.registers.B;
        *cpu.registers.F = 0b00100000;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case C:
        *cpu.registers.A = *cpu.registers.A & *cpu.registers.C;
        *cpu.registers.F = 0b00100000;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case D:
        *cpu.registers.A = *cpu.registers.A & *cpu.registers.D;
        *cpu.registers.F = 0b00100000;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case E:
        *cpu.registers.A = *cpu.registers.A & *cpu.registers.E;
        *cpu.registers.F = 0b00100000;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case H:
        *cpu.registers.A = *cpu.registers.A & *cpu.registers.H;
        *cpu.registers.F = 0b00100000;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case L:
        *cpu.registers.A = *cpu.registers.A & *cpu.registers.L;
        *cpu.registers.F = 0b00100000;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case HLa:
        *cpu.registers.A = *cpu.registers.A & cpu.readMemory(cpu.registers.HL);
        *cpu.registers.F = 0b00100000;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cycles = 8;
        break;
    case d8:
        *cpu.registers.A = *cpu.registers.A & cpu.readMemory(cpu.registers.PC + 1);
        *cpu.registers.F = 0b00100000;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cpu.registers.PC += 1;
        cycles = 8;
        break;
    default:
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// OR operand2 with accumulator and store result in accumulator
int Instr::OR(CPU& cpu, Operand operand1)
{
    int cycles = 4;
    switch (operand1)
    {
    case A:
        *cpu.registers.A = *cpu.registers.A | *cpu.registers.A;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.A = *cpu.registers.A | *cpu.registers.B;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case C:
        *cpu.registers.A = *cpu.registers.A | *cpu.registers.C;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case D:
        *cpu.registers.A = *cpu.registers.A | *cpu.registers.D;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case E:
        *cpu.registers.A = *cpu.registers.A | *cpu.registers.E;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case H:
        *cpu.registers.A = *cpu.registers.A | *cpu.registers.H;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case L:
        *cpu.registers.A = *cpu.registers.A | *cpu.registers.L;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case HLa:
        *cpu.registers.A = *cpu.registers.A | cpu.readMemory(cpu.registers.HL);
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cycles = 8;
        break;
    case d8:
        *cpu.registers.A = *cpu.registers.A | cpu.readMemory(cpu.registers.PC + 1);
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cpu.registers.PC += 1;
        cycles = 8;
        break;
    default:
        break;
    }
    cpu.registers.PC += 1;

    return cycles;

}

// XOR operand2 with accumulator and store result in accumulator
int Instr::XOR(CPU& cpu, Operand operand1)
{
    int cycles = 4;
    switch (operand1)
    {
    case A:
        *cpu.registers.A = *cpu.registers.A ^ *cpu.registers.A;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.A = *cpu.registers.A ^ *cpu.registers.B;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case C:
        *cpu.registers.A = *cpu.registers.A ^ *cpu.registers.C;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case D:
        *cpu.registers.A = *cpu.registers.A ^ *cpu.registers.D;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case E:
        *cpu.registers.A = *cpu.registers.A ^ *cpu.registers.E;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case H:
        *cpu.registers.A = *cpu.registers.A ^ *cpu.registers.H;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case L:
        *cpu.registers.A = *cpu.registers.A ^ *cpu.registers.L;
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        break;
    case HLa:
        *cpu.registers.A = *cpu.registers.A ^ cpu.readMemory(cpu.registers.HL);
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cycles = 8;
        break;
    case d8:
        *cpu.registers.A = *cpu.registers.A ^ cpu.readMemory(cpu.registers.PC + 1);
        *cpu.registers.F = 0;
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A);
        cpu.registers.PC += 1;
        cycles = 8;
        break;
    default:
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Subtract operand1 from accumulator, update flags, don't store result
int Instr::CP(CPU& cpu, Operand operand1)
{
    int cycles = 4;
    switch (operand1)
    {
    case A:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.A);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.A);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A - *cpu.registers.A);
        break;
    case B:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.B);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.B);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A - *cpu.registers.B);
        break;
    case C:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.C);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.C);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A - *cpu.registers.C);
        break;
    case D:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.D);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.D);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A - *cpu.registers.D);
        break;
    case E:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.E);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.E);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A - *cpu.registers.E);
        break;
    case H:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.H);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.H);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A - *cpu.registers.H);
        break;
    case L:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, *cpu.registers.L);
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, *cpu.registers.L);
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A - *cpu.registers.L);
        break;
    case HLa:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F = *cpu.registers.F | HalfCarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.HL));
        *cpu.registers.F = *cpu.registers.F | CarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.HL));
        *cpu.registers.F = *cpu.registers.F | ZeroFlag(*cpu.registers.A - cpu.readMemory(cpu.registers.HL));
        cycles = 8;
        break;
    case d8:
        *cpu.registers.F = 0b01000000;
        *cpu.registers.F |= HalfCarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.PC + 1));
        *cpu.registers.F |= CarryOnSubtraction(*cpu.registers.A, cpu.readMemory(cpu.registers.PC + 1));
        *cpu.registers.F |= ZeroFlag(*cpu.registers.A - cpu.readMemory(cpu.registers.PC + 1));
        cpu.registers.PC += 1;
        cycles = 8;
        break;
    }

    cpu.registers.PC += 1;
    return cycles;
}

// Relative jump to address
int Instr::JR(CPU& cpu, JumpCondition condition)
{
    switch (condition)
    {
    case jNONE:
        cpu.registers.PC += (int8_t)cpu.readMemory(cpu.registers.PC + 1) + 2;
        return 12;
    case jNZ:
        if (!(*cpu.registers.F & 0b10000000))
        {
            cpu.registers.PC += (int8_t)cpu.readMemory(cpu.registers.PC + 1) + 2;
            return 12;
        }
        break;
    case jZ:
        if (*cpu.registers.F & 0b10000000)
        {
            cpu.registers.PC += (int8_t)cpu.readMemory(cpu.registers.PC + 1) + 2;
            return 12;
        }
        break;
    case jNC:
        if (!(*cpu.registers.F & 0b00010000))
        {
            cpu.registers.PC += (int8_t)cpu.readMemory(cpu.registers.PC + 1) + 2;
            return 12;
        }
        break;
    case jC:
        if (*cpu.registers.F & 0b00010000)
        {
            cpu.registers.PC += (int8_t)cpu.readMemory(cpu.registers.PC + 1) + 2;
            return 12;
        }
        break;
    }


    cpu.registers.PC += 2;

    return 8;
}

// Jump to address
int Instr::JP(CPU& cpu, JumpCondition condition, Operand operand1)
{


    switch (condition)
    {
    case jNONE:
        if (operand1 == HLa)
        {
            cpu.registers.PC = cpu.registers.HL;
            return 4;
        }
        else
        {
            cpu.registers.PC = cpu.readMemory(cpu.registers.PC + 2) << 8 | cpu.readMemory(cpu.registers.PC + 1);
            return 16;
        }
    case jNZ:
        if (!(*cpu.registers.F & 0b10000000))
        {
            cpu.registers.PC = cpu.readMemory(cpu.registers.PC + 2) << 8 | cpu.readMemory(cpu.registers.PC + 1);
            return 16;
        }
        break;
    case jZ:
        if (*cpu.registers.F & 0b10000000)
        {
            cpu.registers.PC = cpu.readMemory(cpu.registers.PC + 2) << 8 | cpu.readMemory(cpu.registers.PC + 1);
            return 16;
        }
        break;
    case jNC:
        if (!(*cpu.registers.F & 0b00010000))
        {
            cpu.registers.PC = cpu.readMemory(cpu.registers.PC + 2) << 8 | cpu.readMemory(cpu.registers.PC + 1);
            return 16;
        }
        break;
    case jC:
        if (*cpu.registers.F & 0b00010000)
        {
            cpu.registers.PC = cpu.readMemory(cpu.registers.PC + 2) << 8 | cpu.readMemory(cpu.registers.PC + 1);
            return 16;
        }
        break;
    default:
        break;
    }
    cpu.registers.PC += 3;
    return 12;
}

// Call to address
int Instr::CALL(CPU& cpu, JumpCondition condition)
{

    switch (condition)
    {
    case jNONE:
        cpu.registers.SP -= 2;
        cpu.writeMemory(cpu.registers.SP, ((cpu.registers.PC + 3) & 0x00FF));
        cpu.writeMemory(cpu.registers.SP + 1, ((cpu.registers.PC + 3) & 0xFF00) >> 8);
        cpu.registers.PC = cpu.readMemory(cpu.registers.PC + 2) << 8 | cpu.readMemory(cpu.registers.PC + 1);
        return 24;
    case jNZ:
        if (!(*cpu.registers.F & 0b10000000))
        {
            cpu.registers.SP -= 2;
            cpu.writeMemory(cpu.registers.SP, ((cpu.registers.PC + 3) & 0x00FF));
            cpu.writeMemory(cpu.registers.SP + 1, ((cpu.registers.PC + 3) & 0xFF00) >> 8);
            cpu.registers.PC = cpu.readMemory(cpu.registers.PC + 2) << 8 | cpu.readMemory(cpu.registers.PC + 1);
            return 24;
        }
        break;
    case jZ:
        if (*cpu.registers.F & 0b10000000)
        {
            cpu.registers.SP -= 2;
            cpu.writeMemory(cpu.registers.SP, ((cpu.registers.PC + 3) & 0x00FF));
            cpu.writeMemory(cpu.registers.SP + 1, ((cpu.registers.PC + 3) & 0xFF00) >> 8);
            cpu.registers.PC = cpu.readMemory(cpu.registers.PC + 2) << 8 | cpu.readMemory(cpu.registers.PC + 1);
            return 24;
        }
        break;
    case jNC:
        if (!(*cpu.registers.F & 0b00010000))
        {
            cpu.registers.SP -= 2;
            cpu.writeMemory(cpu.registers.SP, ((cpu.registers.PC + 3) & 0x00FF));
            cpu.writeMemory(cpu.registers.SP + 1, ((cpu.registers.PC + 3) & 0xFF00) >> 8);
            cpu.registers.PC = cpu.readMemory(cpu.registers.PC + 2) << 8 | cpu.readMemory(cpu.registers.PC + 1);
            return 24;
        }
        break;
    case jC:
        if (*cpu.registers.F & 0b00010000)
        {
            cpu.registers.SP -= 2;
            cpu.writeMemory(cpu.registers.SP, ((cpu.registers.PC + 3) & 0x00FF));
            cpu.writeMemory(cpu.registers.SP + 1, ((cpu.registers.PC + 3) & 0xFF00) >> 8);
            cpu.registers.PC = cpu.readMemory(cpu.registers.PC + 2) << 8 | cpu.readMemory(cpu.registers.PC + 1);
            return 24;
        }
        break;
    }
    cpu.registers.PC += 3;
    return 12;
}

// Return from subroutine
int Instr::RET(CPU& cpu, JumpCondition condition)
{

    switch (condition)
    {
    case jNONE:
        cpu.registers.PC = cpu.readMemory(cpu.registers.SP + 1) << 8 | cpu.readMemory(cpu.registers.SP);
        cpu.registers.SP += 2;
        return 16;
    case jNZ:
        if (!(*cpu.registers.F & 0b10000000))
        {
            cpu.registers.PC = cpu.readMemory(cpu.registers.SP + 1) << 8 | cpu.readMemory(cpu.registers.SP);
            cpu.registers.SP += 2;
            return 20;
        }
        break;
    case jZ:
        if (*cpu.registers.F & 0b10000000)
        {
            cpu.registers.PC = cpu.readMemory(cpu.registers.SP + 1) << 8 | cpu.readMemory(cpu.registers.SP);
            cpu.registers.SP += 2;
            return 20;
        }
        break;
    case jNC:
        if (!(*cpu.registers.F & 0b00010000))
        {
            cpu.registers.PC = cpu.readMemory(cpu.registers.SP + 1) << 8 | cpu.readMemory(cpu.registers.SP);
            cpu.registers.SP += 2;
            return 20;
        }
        break;
    case jC:
        if (*cpu.registers.F & 0b00010000)
        {
            cpu.registers.PC = cpu.readMemory(cpu.registers.SP + 1) << 8 | cpu.readMemory(cpu.registers.SP);
            cpu.registers.SP += 2;
            return 20;
        }
        break;
    }
    cpu.registers.PC += 1;
    return 8;
}

// Return and enable interrupts
int Instr::RETI(CPU& cpu)
{
    cpu.registers.PC = cpu.readMemory(cpu.registers.SP + 1) << 8 | cpu.readMemory(cpu.registers.SP);
    cpu.registers.SP += 2;
    cpu.IME = true;

    return 16;
}


int Instr::RST(CPU& cpu, uint8_t opcode)
{

    uint8_t address = opcode & 0b00111000;

    cpu.registers.SP -= 2;
    cpu.writeMemory(cpu.registers.SP, ((cpu.registers.PC + 1) & 0x00FF));
    cpu.writeMemory(cpu.registers.SP + 1, ((cpu.registers.PC + 1) & 0xFF00) >> 8);
    cpu.registers.PC = address;

    return 16;
}

// Pop stack into register
int Instr::POP(CPU& cpu, Operand operand1)
{
    switch (operand1)
    {
    case BC:
        cpu.registers.BC = cpu.readMemory(cpu.registers.SP + 1) << 8 | cpu.readMemory(cpu.registers.SP);
        cpu.registers.SP += 2;
        break;
    case DE:
        cpu.registers.DE = cpu.readMemory(cpu.registers.SP + 1) << 8 | cpu.readMemory(cpu.registers.SP);
        cpu.registers.SP += 2;
        break;
    case HL:
        cpu.registers.HL = cpu.readMemory(cpu.registers.SP + 1) << 8 | cpu.readMemory(cpu.registers.SP);
        cpu.registers.SP += 2;
        break;
    case AF:
        cpu.registers.AF = cpu.readMemory(cpu.registers.SP + 1) << 8 | cpu.readMemory(cpu.registers.SP);
        cpu.registers.AF &= 0xFFF0;
        cpu.registers.SP += 2;
        break;
    default:
        break;
    }

    cpu.registers.PC += 1;
    return 12;
}

// Push register onto stack
int Instr::PUSH(CPU& cpu, Operand operand1)
{
    switch (operand1)
    {
    case BC:
        cpu.registers.SP -= 2;
        cpu.writeMemory(cpu.registers.SP, *cpu.registers.C);
        cpu.writeMemory(cpu.registers.SP + 1, *cpu.registers.B);
        break;
    case DE:
        cpu.registers.SP -= 2;
        cpu.writeMemory(cpu.registers.SP + 1, *cpu.registers.D);
        cpu.writeMemory(cpu.registers.SP, *cpu.registers.E);
        break;
    case HL:
        cpu.registers.SP -= 2;
        cpu.writeMemory(cpu.registers.SP, *cpu.registers.L);
        cpu.writeMemory(cpu.registers.SP + 1, *cpu.registers.H);
        break;
    case AF:
        cpu.registers.SP -= 2;
        cpu.writeMemory(cpu.registers.SP, *cpu.registers.F);
        cpu.writeMemory(cpu.registers.SP + 1, *cpu.registers.A);
        break;
    default:
        break;
    }
    cpu.registers.PC += 1;
    return 16;
}

// Rotate A register left
int Instr::RLCA(CPU& cpu)
{
    *cpu.registers.F = (*cpu.registers.A & 0b10000000) >> 3;
    *cpu.registers.A = *cpu.registers.A << 1 | ((*cpu.registers.A & 0b10000000) >> 7);
    cpu.registers.PC += 1;

    return 4;
}

// Rotate A register right
int Instr::RRCA(CPU& cpu)
{
    *cpu.registers.F = (*cpu.registers.A & 0b00000001) << 4;
    *cpu.registers.A = *cpu.registers.A >> 1 | ((*cpu.registers.A & 0b00000001) << 7);
    cpu.registers.PC += 1;

    return 4;
}

// Rotate A register right through carry
int Instr::RRA(CPU& cpu)
{
    uint8_t newCarry = (*cpu.registers.A & 0b00000001) << 4;
    *cpu.registers.A = *cpu.registers.A >> 1 | ((*cpu.registers.F & 0b00010000) << 3);
    *cpu.registers.F = newCarry;
    cpu.registers.PC += 1;

    return 4;
}

// Rotate A register left through carry
int Instr::RLA(CPU& cpu)
{
    uint8_t newCarry = (*cpu.registers.A & 0b10000000) >> 3;
    *cpu.registers.A = *cpu.registers.A << 1 | ((*cpu.registers.F & 0b00010000) >> 4);
    *cpu.registers.F = newCarry;
    cpu.registers.PC += 1;

    return 4;
}

// Set carry flag to 1
int Instr::SCF(CPU& cpu)
{
    *cpu.registers.F = (*cpu.registers.F & 0b10000000) | 0b00010000;

    cpu.registers.PC += 1;
    return 4;
}

// Switch carry flag
int Instr::CCF(CPU& cpu)
{
    *cpu.registers.F = (*cpu.registers.F ^ 0b00010000) & 0b10010000;

    cpu.registers.PC += 1;
    return 4;
}

// Complement A register
int Instr::CPL(CPU& cpu)
{
    *cpu.registers.F |= 0b01100000;
    *cpu.registers.A = ~*cpu.registers.A;

    cpu.registers.PC += 1;
    return 4;
}

// Decimal adjust after addition
int Instr::DAA(CPU& cpu)
{
    if (*cpu.registers.F & 0b01000000) { // If subtraction was performed
        if (*cpu.registers.F & 0b00010000)
            *cpu.registers.A -= 0x60;
        if (*cpu.registers.F & 0b00100000)
            *cpu.registers.A -= 0x6;
    }
    else
    { // If addition was performed
        if (*cpu.registers.F & 0b00010000 || (*cpu.registers.A > 0x99)) {
            *cpu.registers.A += 0x60;
            *cpu.registers.F |= 0b00010000;
        }
        if (*cpu.registers.F & 0b00100000 || ((*cpu.registers.A & 0xF) > 0x9))
            *cpu.registers.A += 0x6;
    }

    *cpu.registers.F &= 0b01010000; // Clear H and Z flags
    *cpu.registers.F |= ZeroFlag(*cpu.registers.A);
    cpu.registers.PC += 1;
    return 4;
}

// Halt CPU
int Instr::HALT(CPU& cpu)
{
    cpu.registers.PC += 1;
    if (cpu.IME)
    {
        cpu.haltState = 1;
    }
    else
    {
        if ((cpu.readMemory(cpu.IEaddr) & cpu.readMemory(cpu.IFaddr) & 0x1F) == 0) {
            cpu.haltState = 2; // Dont call interrupt
        }
        else
        {
            cpu.haltState = 0;
            cpu.haltBugPC = cpu.registers.PC;
        }
    }

    return 4;
}

// Stop CPU
int Instr::STOP(CPU& cpu)
{
    cpu.stopped = true;
    cpu.registers.PC += 1;

    return 4;
}

// Disable interrupts
int Instr::DI(CPU& cpu)
{
    cpu.IME = false;
    cpu.registers.PC += 1;

    return 4;
}

// Enable interrupts
int Instr::EI(CPU& cpu)
{
    cpu.IME = true;
    cpu.registers.PC += 1;

    return 4;
}

// Rotate register left
int Instr::RLC(CPU& cpu, Operand operand1)
{
    int cycles = 8;
    switch (operand1)
    {
    case A:
        *cpu.registers.F = (*cpu.registers.A & 0b10000000) >> 3;
        *cpu.registers.A = *cpu.registers.A << 1 | ((*cpu.registers.A & 0b10000000) >> 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.F = (*cpu.registers.B & 0b10000000) >> 3;
        *cpu.registers.B = *cpu.registers.B << 1 | ((*cpu.registers.B & 0b10000000) >> 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.B);
        break;
    case C:
        *cpu.registers.F = (*cpu.registers.C & 0b10000000) >> 3;
        *cpu.registers.C = *cpu.registers.C << 1 | ((*cpu.registers.C & 0b10000000) >> 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.C);
        break;
    case D:
        *cpu.registers.F = (*cpu.registers.D & 0b10000000) >> 3;
        *cpu.registers.D = *cpu.registers.D << 1 | ((*cpu.registers.D & 0b10000000) >> 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.D);
        break;
    case E:
        *cpu.registers.F = (*cpu.registers.E & 0b10000000) >> 3;
        *cpu.registers.E = *cpu.registers.E << 1 | ((*cpu.registers.E & 0b10000000) >> 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.E);
        break;
    case H:
        *cpu.registers.F = (*cpu.registers.H & 0b10000000) >> 3;
        *cpu.registers.H = *cpu.registers.H << 1 | ((*cpu.registers.H & 0b10000000) >> 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.H);
        break;
    case L:
        *cpu.registers.F = (*cpu.registers.L & 0b10000000) >> 3;
        *cpu.registers.L = *cpu.registers.L << 1 | ((*cpu.registers.L & 0b10000000) >> 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.L);
        break;
    case HLa:
        *cpu.registers.F = (cpu.readMemory(cpu.registers.HL) & 0b10000000) >> 3;
        cpu.writeMemory(cpu.registers.HL, (cpu.readMemory(cpu.registers.HL) << 1 | ((cpu.readMemory(cpu.registers.HL) & 0b10000000) >> 7)));
        *cpu.registers.F |= ZeroFlag(cpu.readMemory(cpu.registers.HL));
        cycles = 16;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Rotate register right
int Instr::RRC(CPU& cpu, Operand operand1)
{
    int cycles = 8;
    switch (operand1)
    {
    case A:
        *cpu.registers.F = (*cpu.registers.A & 0b00000001) << 4;
        *cpu.registers.A = *cpu.registers.A >> 1 | ((*cpu.registers.A & 0b00000001) << 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.F = (*cpu.registers.B & 0b00000001) << 4;
        *cpu.registers.B = *cpu.registers.B >> 1 | ((*cpu.registers.B & 0b00000001) << 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.B);
        break;
    case C:
        *cpu.registers.F = (*cpu.registers.C & 0b00000001) << 4;
        *cpu.registers.C = *cpu.registers.C >> 1 | ((*cpu.registers.C & 0b00000001) << 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.C);
        break;
    case D:
        *cpu.registers.F = (*cpu.registers.D & 0b00000001) << 4;
        *cpu.registers.D = *cpu.registers.D >> 1 | ((*cpu.registers.D & 0b00000001) << 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.D);
        break;
    case E:
        *cpu.registers.F = (*cpu.registers.E & 0b00000001) << 4;
        *cpu.registers.E = *cpu.registers.E >> 1 | ((*cpu.registers.E & 0b00000001) << 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.E);
        break;
    case H:
        *cpu.registers.F = (*cpu.registers.H & 0b00000001) << 4;
        *cpu.registers.H = *cpu.registers.H >> 1 | ((*cpu.registers.H & 0b00000001) << 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.H);
        break;
    case L:
        *cpu.registers.F = (*cpu.registers.L & 0b00000001) << 4;
        *cpu.registers.L = *cpu.registers.L >> 1 | ((*cpu.registers.L & 0b00000001) << 7);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.L);
        break;
    case HLa:
        *cpu.registers.F = (cpu.readMemory(cpu.registers.HL) & 0b00000001) << 4;
        cpu.writeMemory(cpu.registers.HL, (cpu.readMemory(cpu.registers.HL) >> 1 | ((cpu.readMemory(cpu.registers.HL) & 0b00000001) << 7)));
        *cpu.registers.F |= ZeroFlag(cpu.readMemory(cpu.registers.HL));
        cycles = 16;
        break;
    default:
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Rotate register left through carry
int Instr::RL(CPU& cpu, Operand operand1)
{
    int cycles = 8;
    uint8_t newCarry;
    switch (operand1)
    {
    case A:
        newCarry = (*cpu.registers.A & 0b10000000) >> 3;
        *cpu.registers.A = (*cpu.registers.A << 1) | ((*cpu.registers.F & 0b00010000) >> 4);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.A);
        break;
    case B:
        newCarry = (*cpu.registers.B & 0b10000000) >> 3;
        *cpu.registers.B = (*cpu.registers.B << 1) | ((*cpu.registers.F & 0b00010000) >> 4);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.B);
        break;
    case C:
        newCarry = (*cpu.registers.C & 0b10000000) >> 3;
        *cpu.registers.C = (*cpu.registers.C << 1) | ((*cpu.registers.F & 0b00010000) >> 4);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.C);
        break;
    case D:
        newCarry = (*cpu.registers.D & 0b10000000) >> 3;
        *cpu.registers.D = (*cpu.registers.D << 1) | ((*cpu.registers.F & 0b00010000) >> 4);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.D);
        break;
    case E:
        newCarry = (*cpu.registers.E & 0b10000000) >> 3;
        *cpu.registers.E = (*cpu.registers.E << 1) | ((*cpu.registers.F & 0b00010000) >> 4);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.E);
        break;
    case H:
        newCarry = (*cpu.registers.H & 0b10000000) >> 3;
        *cpu.registers.H = (*cpu.registers.H << 1) | ((*cpu.registers.F & 0b00010000) >> 4);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.H);
        break;
    case L:
        newCarry = (*cpu.registers.L & 0b10000000) >> 3;
        *cpu.registers.L = (*cpu.registers.L << 1) | ((*cpu.registers.F & 0b00010000) >> 4);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.L);
        break;
    case HLa:
        newCarry = (cpu.readMemory(cpu.registers.HL) & 0b10000000) >> 3;
        cpu.writeMemory(cpu.registers.HL, (cpu.readMemory(cpu.registers.HL) << 1) | ((*cpu.registers.F & 0b00010000) >> 4));
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(cpu.readMemory(cpu.registers.HL));
        cycles = 16;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Rotate register right through carry
int Instr::RR(CPU& cpu, Operand operand1)
{
    int cycles = 8;
    uint8_t newCarry;
    switch (operand1)
    {
    case A:
        newCarry = (*cpu.registers.A & 0b00000001) << 4;
        *cpu.registers.A = (*cpu.registers.A >> 1) | ((*cpu.registers.F & 0b00010000) << 3);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.A);
        break;
    case B:
        newCarry = (*cpu.registers.B & 0b00000001) << 4;
        *cpu.registers.B = (*cpu.registers.B >> 1) | ((*cpu.registers.F & 0b00010000) << 3);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.B);
        break;
    case C:
        newCarry = (*cpu.registers.C & 0b00000001) << 4;
        *cpu.registers.C = (*cpu.registers.C >> 1) | ((*cpu.registers.F & 0b00010000) << 3);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.C);
        break;
    case D:
        newCarry = (*cpu.registers.D & 0b00000001) << 4;
        *cpu.registers.D = (*cpu.registers.D >> 1) | ((*cpu.registers.F & 0b00010000) << 3);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.D);
        break;
    case E:
        newCarry = (*cpu.registers.E & 0b00000001) << 4;
        *cpu.registers.E = (*cpu.registers.E >> 1) | ((*cpu.registers.F & 0b00010000) << 3);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.E);
        break;
    case H:
        newCarry = (*cpu.registers.H & 0b00000001) << 4;
        *cpu.registers.H = (*cpu.registers.H >> 1) | ((*cpu.registers.F & 0b00010000) << 3);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.H);
        break;
    case L:
        newCarry = (*cpu.registers.L & 0b00000001) << 4;
        *cpu.registers.L = (*cpu.registers.L >> 1) | ((*cpu.registers.F & 0b00010000) << 3);
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.L);
        break;
    case HLa:
        newCarry = (cpu.readMemory(cpu.registers.HL) & 0b00000001) << 4;
        cpu.writeMemory(cpu.registers.HL, (cpu.readMemory(cpu.registers.HL) >> 1) | ((*cpu.registers.F & 0b00010000) << 3));
        *cpu.registers.F = newCarry;
        *cpu.registers.F |= ZeroFlag(cpu.readMemory(cpu.registers.HL));
        cycles = 16;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Shift left arithmetic
int Instr::SLA(CPU& cpu, Operand operand1)
{
    int cycles = 8;
    switch (operand1)
    {
    case A:
        *cpu.registers.F = (*cpu.registers.A & 0b10000000) >> 3;
        *cpu.registers.A = *cpu.registers.A << 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.A);
        //carry flag
        break;
    case B:
        *cpu.registers.F = (*cpu.registers.B & 0b10000000) >> 3;
        *cpu.registers.B = *cpu.registers.B << 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.B);
        break;
    case C:
        *cpu.registers.F = (*cpu.registers.C & 0b10000000) >> 3;
        *cpu.registers.C = *cpu.registers.C << 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.C);
        break;
    case D:
        *cpu.registers.F = (*cpu.registers.D & 0b10000000) >> 3;
        *cpu.registers.D = *cpu.registers.D << 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.D);
        break;
    case E:
        *cpu.registers.F = (*cpu.registers.E & 0b10000000) >> 3;
        *cpu.registers.E = *cpu.registers.E << 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.E);
        break;
    case H:
        *cpu.registers.F = (*cpu.registers.H & 0b10000000) >> 3;
        *cpu.registers.H = *cpu.registers.H << 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.H);
        break;
    case L:
        *cpu.registers.F = (*cpu.registers.L & 0b10000000) >> 3;
        *cpu.registers.L = *cpu.registers.L << 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.L);
        break;
    case HLa:
        *cpu.registers.F = (cpu.readMemory(cpu.registers.HL) & 0b10000000) >> 3;
        cpu.writeMemory(cpu.registers.HL, cpu.readMemory(cpu.registers.HL) << 1);
        *cpu.registers.F |= ZeroFlag(cpu.readMemory(cpu.registers.HL));
        cycles = 16;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Shift right arithmetic
int Instr::SRA(CPU& cpu, Operand operand1)
{
    int cycles = 8;
    switch (operand1)
    {
    case A:
        *cpu.registers.F = (*cpu.registers.A & 0b00000001) << 4;
        *cpu.registers.A = (*cpu.registers.A >> 1) | (*cpu.registers.A & 0b10000000);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.F = (*cpu.registers.B & 0b00000001) << 4;
        *cpu.registers.B = (*cpu.registers.B >> 1) | (*cpu.registers.B & 0b10000000);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.B);
        break;
    case C:
        *cpu.registers.F = (*cpu.registers.C & 0b00000001) << 4;
        *cpu.registers.C = (*cpu.registers.C >> 1) | (*cpu.registers.C & 0b10000000);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.C);
        break;
    case D:
        *cpu.registers.F = (*cpu.registers.D & 0b00000001) << 4;
        *cpu.registers.D = (*cpu.registers.D >> 1) | (*cpu.registers.D & 0b10000000);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.D);
        break;
    case E:
        *cpu.registers.F = (*cpu.registers.E & 0b00000001) << 4;
        *cpu.registers.E = (*cpu.registers.E >> 1) | (*cpu.registers.E & 0b10000000);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.E);
        break;
    case H:
        *cpu.registers.F = (*cpu.registers.H & 0b00000001) << 4;
        *cpu.registers.H = (*cpu.registers.H >> 1) | (*cpu.registers.H & 0b10000000);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.H);
        break;
    case L:
        *cpu.registers.F = (*cpu.registers.L & 0b00000001) << 4;
        *cpu.registers.L = (*cpu.registers.L >> 1) | (*cpu.registers.L & 0b10000000);
        *cpu.registers.F |= ZeroFlag(*cpu.registers.L);
        break;
    case HLa:
        *cpu.registers.F = (cpu.readMemory(cpu.registers.HL) & 0b00000001) << 4;
        cpu.writeMemory(cpu.registers.HL, (cpu.readMemory(cpu.registers.HL) >> 1) | (cpu.readMemory(cpu.registers.HL) & 0b10000000));
        *cpu.registers.F |= ZeroFlag(cpu.readMemory(cpu.registers.HL));
        cycles = 16;
        break;
    default:
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// SWAP nibbles
int Instr::SWAP(CPU& cpu, Operand operand1)
{
    int cycles = 8;
    switch (operand1)
    {
    case A:
        *cpu.registers.A = (*cpu.registers.A << 4) | (*cpu.registers.A >> 4);
        *cpu.registers.F = ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.B = (*cpu.registers.B << 4) | (*cpu.registers.B >> 4);
        *cpu.registers.F = ZeroFlag(*cpu.registers.B);
        break;
    case C:
        *cpu.registers.C = (*cpu.registers.C << 4) | (*cpu.registers.C >> 4);
        *cpu.registers.F = ZeroFlag(*cpu.registers.C);
        break;
    case D:
        *cpu.registers.D = (*cpu.registers.D << 4) | (*cpu.registers.D >> 4);
        *cpu.registers.F = ZeroFlag(*cpu.registers.D);
        break;
    case E:
        *cpu.registers.E = (*cpu.registers.E << 4) | (*cpu.registers.E >> 4);
        *cpu.registers.F = ZeroFlag(*cpu.registers.E);
        break;
    case H:
        *cpu.registers.H = (*cpu.registers.H << 4) | (*cpu.registers.H >> 4);
        *cpu.registers.F = ZeroFlag(*cpu.registers.H);
        break;
    case L:
        *cpu.registers.L = (*cpu.registers.L << 4) | (*cpu.registers.L >> 4);
        *cpu.registers.F = ZeroFlag(*cpu.registers.L);
        break;
    case HLa:
        cpu.writeMemory(cpu.registers.HL, (cpu.readMemory(cpu.registers.HL) << 4) | (cpu.readMemory(cpu.registers.HL) >> 4));
        *cpu.registers.F = ZeroFlag(cpu.readMemory(cpu.registers.HL));
        cycles = 16;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Shift right logical
int Instr::SRL(CPU& cpu, Operand operand1)
{
    int cycles = 8;
    switch (operand1)
    {
    case A:
        *cpu.registers.F = (*cpu.registers.A & 0b00000001) << 4;
        *cpu.registers.A = *cpu.registers.A >> 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.A);
        break;
    case B:
        *cpu.registers.F = (*cpu.registers.B & 0b00000001) << 4;
        *cpu.registers.B = *cpu.registers.B >> 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.B);
        break;
    case C:
        *cpu.registers.F = (*cpu.registers.C & 0b00000001) << 4;
        *cpu.registers.C = *cpu.registers.C >> 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.C);
        break;
    case D:
        *cpu.registers.F = (*cpu.registers.D & 0b00000001) << 4;
        *cpu.registers.D = *cpu.registers.D >> 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.D);
        break;
    case E:
        *cpu.registers.F = (*cpu.registers.E & 0b00000001) << 4;
        *cpu.registers.E = *cpu.registers.E >> 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.E);
        break;
    case H:
        *cpu.registers.F = (*cpu.registers.H & 0b00000001) << 4;
        *cpu.registers.H = *cpu.registers.H >> 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.H);
        break;
    case L:
        *cpu.registers.F = (*cpu.registers.L & 0b00000001) << 4;
        *cpu.registers.L = *cpu.registers.L >> 1;
        *cpu.registers.F |= ZeroFlag(*cpu.registers.L);
        break;
    case HLa:
        *cpu.registers.F = (cpu.readMemory(cpu.registers.HL) & 0b00000001) << 4;
        cpu.writeMemory(cpu.registers.HL, cpu.readMemory(cpu.registers.HL) >> 1);
        *cpu.registers.F |= ZeroFlag(cpu.readMemory(cpu.registers.HL));
        cycles = 16;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Test bit
int Instr::BIT(CPU& cpu, Operand operand1, uint8_t bit)
{
    int cycles = 8;
    *cpu.registers.F = (*cpu.registers.F & 0b00010000) | 0b00100000;
    switch (operand1)
    {
    case A:
        *cpu.registers.F |= ZeroFlag(*cpu.registers.A & bit);
        break;
    case B:
        *cpu.registers.F |= ZeroFlag(*cpu.registers.B & bit);
        break;
    case C:
        *cpu.registers.F |= ZeroFlag(*cpu.registers.C & bit);
        break;
    case D:
        *cpu.registers.F |= ZeroFlag(*cpu.registers.D & bit);
        break;
    case E:
        *cpu.registers.F |= ZeroFlag(*cpu.registers.E & bit);
        break;
    case H:
        *cpu.registers.F |= ZeroFlag(*cpu.registers.H & bit);
        break;
    case L:
        *cpu.registers.F |= ZeroFlag(*cpu.registers.L & bit);
        break;
    case HLa:
        *cpu.registers.F |= ZeroFlag(cpu.readMemory(cpu.registers.HL) & bit);
        cycles = 16;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Set bit
int Instr::SET(CPU& cpu, Operand operand1, uint8_t bit)
{
    int cycles = 8;
    switch (operand1)
    {
    case A:
        *cpu.registers.A |= bit;
        break;
    case B:
        *cpu.registers.B |= bit;
        break;
    case C:
        *cpu.registers.C |= bit;
        break;
    case D:
        *cpu.registers.D |= bit;
        break;
    case E:
        *cpu.registers.E |= bit;
        break;
    case H:
        *cpu.registers.H |= bit;
        break;
    case L:
        *cpu.registers.L |= bit;
        break;
    case HLa:
        cpu.writeMemory(cpu.registers.HL, cpu.readMemory(cpu.registers.HL) | bit);
        cycles = 16;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}

// Reset bit
int Instr::RES(CPU& cpu, Operand operand1, uint8_t bit)
{
    int cycles = 8;
    switch (operand1)
    {
    case A:
        *cpu.registers.A &= ~bit;
        break;
    case B:
        *cpu.registers.B &= ~bit;
        break;
    case C:
        *cpu.registers.C &= ~bit;
        break;
    case D:
        *cpu.registers.D &= ~bit;
        break;
    case E:
        *cpu.registers.E &= ~bit;
        break;
    case H:
        *cpu.registers.H &= ~bit;
        break;
    case L:
        *cpu.registers.L &= ~bit;
        break;
    case HLa:
        cpu.writeMemory(cpu.registers.HL, cpu.readMemory(cpu.registers.HL) & (~bit));
        cycles = 16;
        break;
    }
    cpu.registers.PC += 1;

    return cycles;
}
