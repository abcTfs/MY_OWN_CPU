#include "CPU.h"
#include "CPU_ASM_Func.cpp"

#define MAX_LABEL 20


int main()
{
    int cmd_arr[MAX_CODE] = {};

    label label_arr[MAX_LABEL] = {};


    FILE* code     = fopen ("code.txt", "w");
    FILE* text     = fopen ("text.txt", "r");
    FILE* code_bin = fopen ("code.bin", "w");

    int ip = ASM_Func (text, code, cmd_arr, label_arr);

    WriteCodeToBin (cmd_arr, ip, code_bin);

    fclose (text);
    fclose (code);
    fclose (code_bin);

    txDump (cmd_arr);
    return 0;
}
