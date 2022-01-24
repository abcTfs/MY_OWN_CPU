int CPU_Ctor (CPU_struct* CPU, int len)
{
    assert (CPU != 0);
    CPU->stk = StackCtor();
    CPU->size_of_file = len;

    return 0;
}

#define GET_VAL double a = pop(CPU->stk);\
                double b = pop(CPU->stk);

double mul (stack* stk) //умножение
{
   $r printf(">>> mul START <<<\n"); $d

   double a = pop (stk);
   $r printf(">>> 1st POP - %lf <<<", a ); $d
   double b = pop (stk);

   push(stk, a*b);
   $r printf(">>> mul END <<<\n"); $d
   return a*b;
}

void sub (stack* stk) // разность
{
    data_t a = pop(stk);
    data_t b = pop(stk);
    push(stk, a - b);
}

void div (stack* stk) // деление
{
    data_t a = pop(stk);
    data_t b = pop(stk);
    push(stk, a/b);
}

void sqrt (stack *stk)
{
    double a = pop(stk);
    push(stk, sqrt(a));
}

void add(stack *stk)
{
    double a = pop(stk);
    double b = pop(stk);
    push(stk, a+b);
}

void in (stack *stk)
{
    int tmp;
    scanf("%d", &tmp);
    push(stk, tmp);
}

data_t out (CPU_struct* CPU)
{
    $y printf (">>> OUT IS WORKING\n"); $d
    double tmp = pop (CPU->stk);

    printf ("out work");

    return tmp;
}

void rmov (CPU_struct* CPU)
{
    printf ("ip = %d, ", CPU->ip);

    $(CPU->reg[$(CPU->cmd_arr[$(CPU->ip + 1)])]) = $(CPU->cmd_arr[$(CPU->ip + 2)]);

    printf("reg - %d\n",CPU->reg[CPU->cmd_arr[CPU->ip + 1]]);
    CPU->ip += 2;
}

void rpop (CPU_struct* CPU)
{
    printf("%d",CPU->reg[CPU->cmd_arr[CPU->ip + 1]] = (int)pop(CPU->stk));
    CPU->ip++;
}

void rpush (CPU_struct* CPU)
{
    push(CPU->stk, CPU->reg[CPU->cmd_arr[CPU->ip + 1]]);
    printf("stk - %lf", pop(CPU->stk));
}

/*void hlt (stack *stk)
{

} */

int jmp (CPU_struct* CPU)
{
    CPU->ip = CPU->cmd_arr[CPU->ip + 1];

    printf ("CPU JMP: new ip = %d\n", CPU->ip);

    return CPU->ip /*+ 2*/;
}

int jne (CPU_struct* CPU)
{
    GET_VAL

    if (!is_Equal(a,b) /*a != b*/)
        return CPU->ip = CPU->cmd_arr[CPU->ip + 1];
    else
        return CPU->ip + 2;
}

int je (CPU_struct* CPU)
{
    GET_VAL

    if (is_Equal (a, b))
        return CPU->ip = CPU->cmd_arr[CPU->ip + 1];
    else
        return CPU->ip + 2;
}

int ja (CPU_struct* CPU)
{
    GET_VAL

    printf ("a = %lf, b = %lf\n", a, b);


    if (a > b)
        return CPU->ip = CPU->cmd_arr[CPU->ip + 1];
    else
        return CPU->ip + 2;
}

int jae (CPU_struct* CPU)
{
    GET_VAL

    if (a >= b)
        return CPU->ip = CPU->cmd_arr[CPU->ip + 1];
    else
        return CPU->ip + 2;
}

int jb (CPU_struct* CPU)
{
    GET_VAL

    if (a < b)
        return CPU->ip = CPU->cmd_arr[CPU->ip + 1];
    else
        return CPU->ip + 2;
}

int jbe (CPU_struct* CPU)
{
    GET_VAL

    if (a <= b)
        return CPU->ip = CPU->cmd_arr[CPU->ip + 1];
    else
        return CPU->ip + 2;
}

int Load_Bin (FILE* code_bin, CPU_struct* CPU )
{

    printf ("file size = %ld\n", CPU->size_of_file);

    fread (CPU->cmd_arr, sizeof (int), CPU->size_of_file, code_bin);

    return CPU->size_of_file;
}

void Dump (CPU_struct* CPU)
{
    printf("-----------------------------\n");
    printf ("CPU: executing ip = %d, ", CPU->ip);
    printf ("cmd = %d\n", CPU->cmd_arr[CPU->ip]);
    for (int i = 0; i < 20; i++) printf ("%03d ", i);
    printf ("\n");
    for (int i = 0; i < 20; i++) printf ("%03d ", CPU->cmd_arr[i]);
    printf("\n");
    printf("%*s\n", 4*CPU->ip + 3, "^^^");
    printf("-----------------------------\n");
}

int Do_bin (CPU_struct* CPU)
{
    for (CPU->ip = 0; CPU->ip < CPU->size_of_file; CPU->ip++)
    {
        Dump(CPU);

        $g printf(">>> IP - %d, SIZE_OF_FILE - %ld, CMD_ARR[IP] - %d <<<\n", CPU->ip, CPU->size_of_file, CPU->cmd_arr[CPU->ip]);   $d

        switch (CPU->cmd_arr[CPU->ip])
        {
            case CMD_PUSH:
            {
                CPU->ip++;
                push (CPU->stk, CPU->cmd_arr[CPU->ip]);

                printf ("STACK: %lf\n", CPU->stk->data[CPU->stk->size - 1]);

                break;


            }

            case CMD_POP:
                pop (CPU->stk);
                break;

            case CMD_OUT:
            {
                $r printf("CMD_OUT\n"); $d

                double value = out(CPU);

                printf ("out: %lf\n", value);
            }
                break;

            case CMD_ADD:
                add (CPU->stk);
                break;

            case CMD_SUB:
                sub (CPU->stk);
                break;

            case CMD_MUL:
            {
                $r printf ("CMD_MUL\n"); $d

                double value = mul (CPU->stk);

                $g printf (">>> CMD_MUL: %lf <<<\n", value); $d
            }
                break;

            case CMD_DIV:
                div (CPU->stk);

            case CMD_SQRT:
                sqrt (CPU->stk);
                break;

            case CMD_IN:
                /*Vitka_is_a_koshachja_morda_DO_*/in(CPU->stk);
                break;

            case CMD_RPUSH:
                rpush(CPU);

           case CMD_RMOV:
                rmov (CPU);
                break;

            case CMD_RPOP:
                rpop (CPU);
                break;

            /*case CMD_HLT:
                hlt (CPU->stk);
                break;*/

            case CMD_JMP:
                CPU->ip = jmp (CPU) - 1;
                printf(">>> JMP DONE <<<");
                break;

            case CMD_JNE:
                CPU->ip = jne (CPU) - 1;
                break;

            case CMD_JA:
                CPU->ip = ja (CPU) - 1;
                break;

            case CMD_JAE:
                CPU->ip = jae (CPU) - 1;
                break;

            case CMD_JB:
                CPU->ip = jb (CPU) - 1;
                break;

            case CMD_JBE:
                CPU->ip = jbe (CPU) - 1;
                break;

            case CMD_JE:
                CPU->ip = je (CPU) - 1;
                break;

            default:
                printf ("smth went wrong, your bank accout is zeroed, sorry;)))\n");
        }
        //fread(&cmd, sizeof(int), 1, CODE_BIN);
    }

    return 0;
}

long Bin_Size (FILE* code_bin)
{
    fseek (code_bin, 0, SEEK_END);
    long size_of_file = ftell (code_bin) / sizeof (int); //считаем количеcтво шагов по 4 байта
    fseek (code_bin, 0, SEEK_SET);

    return size_of_file;
}


