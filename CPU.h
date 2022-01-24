#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <TXlib.h>
#include <string.h>

#include "enum.h"

#define MAX_SIZE_OF_FILE 200
#define MAX_CODE 100


typedef int T;
typedef double data_t;
typedef short cannary_t;


typedef struct Stack_tag_ {
    unsigned int stcannaryL;
    data_t *data;
    size_t size;
    size_t capacity;
    unsigned int stcannaryR;
} stack;




stack* StackCtor(); //создание стека
void StackDctor (stack *stk); //удаление стека
void push (stack *stk, double value); //добавить элемент в стек
data_t pop (stack *stk); //убрать элемент из стека
data_t peek (stack *stk);//вернуть верхний элемент стека, не удал€€ его
void StackResize (stack *stk);
void StackDump (stack* stk);

void printstk (stack* stk);
void PrintInt (int val);
void PrintLongInt (long int val);
void PrintDouble (double val);
void PrintChar (char val);
void stackdump (int statusOfVerification, stack* stk);
int verificator (stack* stk);
int is_Equal (double x, double xref);
void fileprintstk (stack* stk);

struct CPU_struct {
    stack *stk = StackCtor();
    long size_of_file = 0;
    int cmd_arr[MAX_SIZE_OF_FILE] = {};
    int reg[5] = {};
    int ip = 0;
};


double mul (stack* stk);
void sub (stack* stk);
void div (stack* stk);
void sqrt (stack *stk);
void add(stack *stk);
void in (stack *stk);
//data_t out (stack *stk);
data_t out (CPU_struct* CPU);




struct label
{
    int name = 0;
    int addr = 0;
};

int CPU_Ctor (CPU_struct* CPU, int len);
int Execute (FILE* TEXT, FILE* CODE, FILE* CODE_BIN);
int ReadnDo_bin(FILE* CODE_BIN, stack* stk);
int from_file_to_ip_arr(int* code, FILE* CODE, int ip);
int Load_Bin (FILE* code_bin, CPU_struct* CPU);

void rmov (CPU_struct* CPU);
void rpop (CPU_struct* CPU);
void rpush (CPU_struct* CPU);
int jmp (CPU_struct* CPU);
int jne (CPU_struct* CPU);
int je (CPU_struct* CPU);
int jae (CPU_struct* CPU);
int jb (CPU_struct* CPU);
int jbe (CPU_struct* CPU);
void Dump (CPU_struct* CPU);
int Do_bin (CPU_struct* CPU);
long Bin_Size (FILE* code_bin);
int ja (CPU_struct* CPU);

#include "FunctionsForStack.cpp"
