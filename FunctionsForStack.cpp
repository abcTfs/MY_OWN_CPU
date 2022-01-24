#define INIT_SIZE 10
#define MULTIPLIER 2
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102
#define CANNARYBIT 3
#define STCANARY 0xC0FFEE
#define DATACANARY -9223372036854775808.0
#define eps 10e-7

#include "StackVerificator.cpp"

typedef int T;
typedef double data_t;
typedef short cannary_t;


void StackResize (stack *stk)
{

    //verificator(stk);

    assert((stk->data =(data_t*)realloc(stk->data, sizeof(data_t)*MULTIPLIER*(stk -> capacity + 2))) != NULL);
    (stk -> capacity) *= MULTIPLIER;
    stk->data[stk->capacity + 1] = DATACANARY;

    if (stk -> data == NULL)
        exit(STACK_OVERFLOW);

    //printf("Resize\n");

    //verificator(stk);
}

void push (stack *stk, double value)
{
    //verificator(stk);

    if(stk->size >= stk->capacity)
        StackResize(stk);

    stk->data[stk->size] = value;
    stk -> size++;

    printf("push work\n");

    //verificator(stk);
}

/*void push (CPU_struct* CPU, double value)
{
    //verificator(stk);

    if(CPU->stk->size >= CPU->stk->capacity)
        StackResize(CPU->stk);

    CPU->stk->data[CPU->stk->size] = value;
    CPU->stk -> size++;

    printf("push work\n");
}*/

data_t pop (stack *stk)
{
    //verificator (stk);

    printf ("pop is working\n");

    if(stk->size <= 1)
    {
        $r printf("STACK_UNDERFLOW\n");$d
        exit (STACK_UNDERFLOW);
    }

    printf ("2nd pop is working\n");

    stk->size--;

    //verificator (stk);

    printf("pop work\n");

    return stk->data[stk->size];
}

data_t peek (stack *stk)
{
    //verificator(stk);

    if (stk->size <= 1)
        exit(STACK_UNDERFLOW);

    //verificator(stk);

    return stk->data[stk->size - 1];
}

void StackDctor(stack *stk)
{
    //verificator(stk);

    free(stk->data), stk->data = NULL;
    free(stk), stk = NULL;

    //printf("Dctor ok\n");

}

stack* StackCtor()
{
    stack *stk = NULL;
    stk =(stack*)calloc(INIT_SIZE, sizeof(data_t)); //+ sizeof(cannary_t)*CANNARYBIT);
    if (stk == NULL)
        exit(OUT_OF_MEMORY);
    stk -> capacity = INIT_SIZE;
    stk -> data = (data_t*)calloc(stk->capacity + 2, sizeof(data_t));
    if (stk -> data == NULL)
        exit(OUT_OF_MEMORY);



    stk -> size = 1;

    stk -> data[0] = DATACANARY;
    stk -> data[stk->capacity + 1] = DATACANARY;

    stk -> stcannaryL = STCANARY;
    stk -> stcannaryR = STCANARY;

    return stk;
}

void fileprintstk(stack* stk)
{
    verificator(stk);

    printf("DATA: ");

    for (size_t num = 1; num < stk->size; num++)
     fprintf(LOGFILE, "Data[%d] = %lf\n", num, stk->data[num]);

    printf("\n");
}

int is_Equal(double x, double xref)
{
    return (fabs (xref - x) < eps) ? 1 : 0;
}


