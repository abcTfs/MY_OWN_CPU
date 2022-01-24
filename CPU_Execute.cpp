#include "CPU.h"
#include "CPU_Func.cpp"

int main()
{
    FILE* code_bin = fopen ("code.bin", "r");
    int size_of_file = Bin_Size (code_bin);

    CPU_struct CPU = {};
    CPU_Ctor(&CPU, size_of_file);

    Load_Bin (code_bin, &CPU);
    fclose (code_bin);

    Do_bin (&CPU);

    //out(&CPU);

    //printf ("register - %lf", reg[0]);

    return 0;
}
