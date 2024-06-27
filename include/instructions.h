
#pragma once
#include "tools.h"
#include "cpu.h"

namespace Instr {

using namespace Tools;
    
// Increment register or memory
int INC(CPU& cpu, Operand operand1);

// Decrement register or memory
int DEC(CPU& cpu, Operand operand1);

// No operation
int NOP(CPU& cpu);

// Load register or memory
int LD(CPU& cpu, Operand operand1, Operand operand2, int type);

// Add operand2 to operand1
int ADD(CPU& cpu, Operand operand1, Operand operand2);

// Add operand2 and carry flag to accumulator
int ADC(CPU& cpu, Operand operand2);


int INC(CPU& cpu, Operand operand1);
// Decrement register or memory
int DEC(CPU& cpu, Operand operand1);
// No operation
int NOP(CPU& cpu);

// Load register or memory
int LD(CPU& cpu, Operand operand1, Operand operand2, int type);
// Add operand2 to operand1
int ADD(CPU& cpu, Operand operand1, Operand operand2);
// Add operand2 and carry flag to accumulator
int ADC(CPU& cpu, Operand operand2);
// Subtract register or value from accumulator
int SUB(CPU& cpu, Operand operand1);
// Subtract operand2 and carry flag from accumulator
int SBC(CPU& cpu, Operand operand1);
// AND operand2 with accumulator and store result in accumulator
int AND(CPU& cpu, Operand operand1);
// OR operand2 with accumulator and store result in accumulator
int OR(CPU& cpu, Operand operand1);
// XOR operand2 with accumulator and store result in accumulator
int XOR(CPU& cpu, Operand operand1);
// Subtract operand1 from accumulator, update flags, don't store result
int CP(CPU& cpu, Operand operand1);
// Relative jump to address
int JR(CPU& cpu, JumpCondition condition);
// Jump to address
int JP(CPU& cpu, JumpCondition condition, Operand operand1);
// Call to address
int CALL(CPU& cpu, JumpCondition condition);
// Return from subroutine
int RET(CPU& cpu, JumpCondition condition);
// Return and enable interrupts
int RETI(CPU& cpu);

int RST(CPU& cpu, uint8_t opcode);
// Pop stack into register
int POP(CPU& cpu, Operand operand1);
// Push register onto stack
int PUSH(CPU& cpu, Operand operand1);
// Rotate A register left
int RLCA(CPU& cpu);
// Rotate A register right
int RRCA(CPU& cpu);
// Rotate A register right through carry
int RRA(CPU& cpu);

// Rotate A register left through carry
int RLA(CPU& cpu);
// Set carry flag to 1
int SCF(CPU& cpu);
// Switch carry flag
int CCF(CPU& cpu);
// Complement A register
int CPL(CPU& cpu);
// Decimal adjust after addition
int DAA(CPU& cpu);
// Halt CPU
int HALT(CPU& cpu);
// Stop CPU
int STOP(CPU& cpu);
// Disable interrupts
int DI(CPU& cpu);
// Enable interrupts
int EI(CPU& cpu);
// Rotate register left
int RLC(CPU& cpu, Operand operand1);
// Rotate register right
int RRC(CPU& cpu, Operand operand1);
// Rotate register left through carry
int RL(CPU& cpu, Operand operand1);
// Rotate register right through carry
int RR(CPU& cpu, Operand operand1);
// Shift left arithmetic
int SLA(CPU& cpu, Operand operand1);
// Shift right arithmetic
int SRA(CPU& cpu, Operand operand1);
// SWAP nibbles
int SWAP(CPU& cpu, Operand operand1);
// Shift right logical
int SRL(CPU& cpu, Operand operand1);
// Test bit
int BIT(CPU& cpu, Operand operand1, uint8_t bit);
// Set bit
int SET(CPU& cpu, Operand operand1, uint8_t bit);
// Reset bit
int RES(CPU& cpu, Operand operand1, uint8_t bit);

// Subtract register or value from accumulator
int SUB(CPU& cpu, Operand operand1);
// Subtract operand2 and carry flag from accumulator
int SBC(CPU& cpu, Operand operand1);
// AND operand2 with accumulator and store result in accumulator
int AND(CPU& cpu, Operand operand1);
// OR operand2 with accumulator and store result in accumulator
int OR(CPU& cpu, Operand operand1);
// XOR operand2 with accumulator and store result in accumulator
int XOR(CPU& cpu, Operand operand1);
// Subtract operand1 from accumulator, update flags, don't store result
int CP(CPU& cpu, Operand operand1);
// Relative jump to address
int JR(CPU& cpu, JumpCondition condition);
// Jump to address
int JP(CPU& cpu, JumpCondition condition, Operand operand1);
// Call to address
int CALL(CPU& cpu, JumpCondition condition);
// Return from subroutine
int RET(CPU& cpu, JumpCondition condition);
// Return and enable interrupts
int RETI(CPU& cpu);

int RST(CPU& cpu, uint8_t opcode);
// Pop stack into register
int POP(CPU& cpu, Operand operand1);
// Push register onto stack
int PUSH(CPU& cpu, Operand operand1);
// Rotate A register left
int RLCA(CPU& cpu);
// Rotate A register right
int RRCA(CPU& cpu);
// Rotate A register right through carry
int RRA(CPU& cpu);
// Rotate A register left through carry
int RLA(CPU& cpu);
// Set carry flag to 1
int SCF(CPU& cpu);
// Switch carry flag
int CCF(CPU& cpu);
// Complement A register
int CPL(CPU& cpu);
// Decimal adjust after addition
int DAA(CPU& cpu);
// Halt CPU
int HALT(CPU& cpu);
// Stop CPU
int STOP(CPU& cpu);
// Disable interrupts
int DI(CPU& cpu);
// Enable interrupts
int EI(CPU& cpu);
// Rotate register left
int RLC(CPU& cpu, Operand operand1);
// Rotate register right
int RRC(CPU& cpu, Operand operand1);
// Rotate register left through carry
int RL(CPU& cpu, Operand operand1);
// Rotate register right through carry
int RR(CPU& cpu, Operand operand1);
// Shift left arithmetic
int SLA(CPU& cpu, Operand operand1);
// Shift right arithmetic
int SRA(CPU& cpu, Operand operand1);
// SWAP nibbles
int SWAP(CPU& cpu, Operand operand1);
// Shift right logical
int SRL(CPU& cpu, Operand operand1);
// Test bit
int BIT(CPU& cpu, Operand operand1, uint8_t bit);
// Set bit
int SET(CPU& cpu, Operand operand1, uint8_t bit);
// Reset bit
int RES(CPU& cpu, Operand operand1, uint8_t bit);
}