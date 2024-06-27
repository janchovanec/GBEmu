    enum Color
    {
        WHITE,
        LIGHT_GRAY,
        DARK_GRAY,
        BLACK,
        TRANSPARENT
    };
    enum Operand { BC, B, C, DE, D, E, HL, H, L, SP, A, F, AF, Z, NZ, CARRY, NCARRY, d8, d16, a8, a16, r8, r16, NONE, HLa, BCa, DEa, HLi, HLd, Ca, SPr8 };
    enum JumpCondition { jZ, jNZ, jC, jNC, jNONE, jInterrupt };