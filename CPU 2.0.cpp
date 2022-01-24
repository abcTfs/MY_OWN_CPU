#include "CPU.h"

int main()
{
    FILE* TEXT     = fopen("text.txt", "r");
    FILE* CODE     = fopen("code.txt", "w+");
    FILE* CODE_BIN = fopen("code.bin", "w+b");

    double reg[4] = {0};

    int code[MAX_CODE] = {0};
    int ip = 0;

    stack *stk = StackCtor();

    Execute(TEXT, CODE, CODE_BIN);
    //ReadnDo_bin(CODE_BIN, stk);

    //from_file_to_ip_arr(code, CODE, ip);

    fclose(TEXT); fclose(CODE); fclose(CODE_BIN);

    printf ("%lf", reg[0]);

    return 0;
}






