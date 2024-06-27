#pragma once
#include <string>
#include <fstream>
#include <cstdint>
#include "renderer.h"
#include "tools.h"
#include "registers.h"
#include "cartridgeData.h"
#include "enums.h"


class CPU
{

private:
    std::ifstream inputFile;
    CartridgeData cart;
    uint8_t memory[0x10000];
    uint8_t RAM[0x8000];
    uint8_t* ROMBanks;
    const uint16_t DIVaddr;
    const uint16_t TIMAaddr;
    const uint16_t TMAaddr;
    const uint16_t TMCaddr;
    const int maxCycles;
    const int clockSpeed;
    int frequency;
    int timerCounter;
    int dividerCounter;
    int scanlineCounter;
    uint32_t screenData[160 * 144];

    uint8_t MBC;
    uint8_t selectedROMBank;
    uint8_t selectedRAMBank;
    bool enableRAM;
    bool ROMBanking;

    uint8_t joypadState;

    int loadROM(std::string filename);
    void loadCartHeader();
    int runNextOpcode();
    void handleInterrupts();
    void interruptCall(uint8_t interrupt);
    void updateTimers(int cycles);
    void setInterrupt(int interrupt);
    bool isClockEnabled();
    uint8_t getClockFrequency();
    void setClockFrequency();
    void DoDividerRegister(int cycles);
    void updateGraphics(int cycles);
    void setLCDStatus();
    bool isLCDOn();
    void drawScanline();
    void DMATransfer(uint8_t source);
    void drawBackground();
    void drawSprites();
    Color getColor(uint8_t colorNum, uint16_t address);
    void handleBanking(uint16_t address, uint8_t value);
    uint8_t getJoypadState();
    void printRegisters();
    Color getColorSprite(uint8_t colorNum, uint16_t address);
    Color getColorBG(uint8_t colorNum);
public:
    Registers registers;
    const uint16_t IEaddr;
    const uint16_t IFaddr;
    bool IME;
    uint8_t haltState;
    uint16_t haltBugPC;
    bool stopped;

    CPU(std::string filename);
    ~CPU();
    void keyPressed(uint8_t keyMask);
    void keyReleased(uint8_t keyMask);
    void update();
    uint8_t readMemory(uint16_t address);
    void writeMemory(uint16_t address, uint8_t value);

    void loop();
    Renderer renderer;
};