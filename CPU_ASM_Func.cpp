
#define WRITE_CODE(cmd)            \
{                                   \
    fprintf (code, "ip = %d, cmd = %d, buf = /%s/\n", ip, cmd, buf2);     \
    code_arr[ip++] = cmd;             \
}

int ASM_Func (FILE* text, FILE* code, int code_arr[], struct label label_arr[])
{
    int ip1 = 0;
    int ip = 0;

    while (true)
    {
        char buf1[100] = "  ";
        int label = 0;

        if (fscanf (text, "%s", buf1) == EOF)
            break;

        if (buf1[0] == ':')
        {
            int ret = sscanf (buf1, ":%d", &label);
            printf ("LABEL: buf1 - /%s/, label - %d, sscanf = %d\n", buf1, label, ret);

            label_arr[label].name =  label;
            label_arr[label].addr  = ip1;
            printf ("label name - %d, label adr - %d\n", label_arr[label].name, label_arr[label].addr);

            getchar();

            continue;
        }

        if (strcmp (buf1, "/") == 0)
            break;

        ip1++;
    }

    $r printf(">>> FIRST WHILE <<<"); $d

    fseek(text, SEEK_SET, 0);

    while (true)
    {
        $g printf (">>> SECOND WHILE <<<"); $d
        char buf2[100] = "  ";
        int label = 0;

        if (fscanf (text, "%s", buf2) == EOF)
            break;

        if (strcmp (buf2, "/") == 0)
            break;

        if (buf2[0] == ':')
        {
            int ret = sscanf (buf2, ":%d", &label);
           // printf ("LABEL: buf - /%s/, label - %d, sscanf = %d\n", buf, label, ret);

           // label_arr[label].name =  label;
            //label_arr[label].addr  = ip;
           // printf ("label name - %d, label adr - %d\n", label_arr[label].name, label_arr[label].addr);

            getchar();

            continue;
        }

        printf ("cmd - /%s/\n", buf2);

        if (strcmp (buf2, "push") == 0)
        {
            WRITE_CODE (CMD_PUSH);

            int val = 0;
            fscanf (text, "%d", &val);

            WRITE_CODE (val);
        }

        else if (strcmp (buf2, "rmov") == 0)
        {
            WRITE_CODE (CMD_RMOV);

            int reg_num = 0;
            fscanf (text, "%d", &reg_num);

            WRITE_CODE (reg_num);


            int val = 0;
            fscanf (text, "%d", &val);

            WRITE_CODE (val);
        }

        else if (strcmp (buf2, "rpush") == 0)
        {
            WRITE_CODE (CMD_RPUSH);

            int reg_num = 0;
            fscanf (text, "%d", &reg_num);

            WRITE_CODE (reg_num);
        }

        else if (strcmp (buf2, "rpop") == 0)
        {
            WRITE_CODE (CMD_RPOP);

            int reg = 0;
            fscanf (text, "%d", &reg);

            WRITE_CODE (reg);
        }

        else if (strcmp (buf2, "mul") == 0)
        {
            WRITE_CODE (CMD_MUL);
        }

        else if (strcmp (buf2, "sub") == 0)
        {
            WRITE_CODE (CMD_SUB);
        }

        else if (strcmp (buf2, "div") == 0)
        {
            WRITE_CODE (CMD_DIV);
        }

        else if (strcmp (buf2, "sqrt") == 0)
        {
            WRITE_CODE (CMD_SQRT);
        }

        else if (strcmp (buf2, "in") == 0)
        {
            WRITE_CODE (CMD_IN);
        }

        else if (strcmp (buf2, "out") == 0)
        {
            WRITE_CODE (CMD_OUT);
        }

        else if (strcmp (buf2, "jmp") == 0)
        {
            WRITE_CODE (CMD_JMP);

            int val = 0;
            fscanf (text, "%d", &val);

            WRITE_CODE (label_arr[label_arr[val].name].addr);
        }

        else if (strcmp (buf2, "jne") == 0)
        {
            WRITE_CODE (CMD_JNE);

            int val = 0;
            fscanf (text, ":%d", &val);

            WRITE_CODE (val);
        }

        else if (strcmp (buf2, "ja") == 0)
        {
            WRITE_CODE (CMD_JA);

            int label_number = 0;
            fscanf (text, " :%d", &label_number);
            printf ("label number - %d, label_arr[label_number].addr = %d\n", label_number, label_arr[label_number].addr);
            WRITE_CODE (label_arr[label_number].addr);
        }

        else if (strcmp (buf2, "jae") == 0)
        {
            WRITE_CODE (CMD_JAE);

            int val = 0;
            fscanf (text, "%d", &val);

            WRITE_CODE (val);
        }

        else if (strcmp (buf2, "jb") == 0)
        {
            WRITE_CODE (CMD_JB);

            int val = 0;
            fscanf (text, "%d", &val);

            WRITE_CODE (val);
        }

        else if (strcmp (buf2, "jbe") == 0)
        {
            WRITE_CODE (CMD_JBE);

            int val = 0;
            fscanf (text, "%d", &val);

            WRITE_CODE (val);
        }

        else if (strcmp (buf2, "je") == 0)
        {
            WRITE_CODE (CMD_JE);

            int val = 0;
            fscanf (text, "%d", &val);

            WRITE_CODE (val);
        }

        txDump (code_arr);

    }

    return ip;
}

int WriteCodeToBin (int cmd_arr[], int ip, FILE* code_bin)
{
    int ret = fwrite (cmd_arr, sizeof (int), ip, code_bin);

    return ret;
}
