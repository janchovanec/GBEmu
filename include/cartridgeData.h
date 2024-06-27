    
    #pragma once
    
    struct CartridgeData
    {
        char intro[4];
        char logo[48];
        char title[16];
        char CGB;
        char newLicense[2];
        char SGB;
        char cartType;
        char ROMSize;
        char RAMSize;
        char destCode;
        char oldLicense;
        char maskRomVer;
        char headerChecksum;
        char globalChecksum[2];
    };
