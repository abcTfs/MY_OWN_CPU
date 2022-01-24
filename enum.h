enum actions
{
    CMD_PUSH  = 1,
    CMD_POP   = 2,
    CMD_OUT   = 3,
    CMD_ADD   = 4,
    CMD_SUB   = 5,
    CMD_MUL   = 6,
    CMD_DIV   = 7,
    CMD_SQRT  = 8,
    CMD_IN    = 9,
    CMD_HLT   = -1,

    CMD_RPUSH = 41,
    CMD_RPOP  = 42,
    CMD_RMOV  = 43,

    CMD_JMP   = 100,
    CMD_JNE   = 101,
    CMD_JA    = 102,
    CMD_JAE   = 103,
    CMD_JB    = 104,
    CMD_JBE   = 105,
    CMD_JE    = 106
};

enum registers
{
    REG_AX = 1,
    REG_BX = 2,
    REG_CX = 3,
    REG_DX = 4
};

