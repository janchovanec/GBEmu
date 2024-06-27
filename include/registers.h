    #pragma once
    #include <cstdint>    
    
    class Registers
    {
    public:
        uint16_t AF;
        uint16_t BC;
        uint16_t DE;
        uint16_t HL;
        uint16_t SP;
        uint16_t PC;
        uint8_t* A;
        uint8_t* F;
        uint8_t* B;
        uint8_t* C;
        uint8_t* D;
        uint8_t* E;
        uint8_t* H;
        uint8_t* L;
        Registers();
    };