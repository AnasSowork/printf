#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @fms: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flgs: Calculates active flags
 * @wdt: get width.
 * @prcn: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fms, int *ind, va_list list, char buffer[],
    int flgs, int wdt, int prcn, int size)
{
    int i, ukn_len = 0, prntd_chars = -1;
    Nou_t Nou_types[] = {
        {'c', print_char}, {'s', print_string}, {'%', print_percent},
        {'i', print_int}, {'d', print_int}, {'b', print_binary},
        {'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
        {'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
        {'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
    };
    for (i = 0; Nou_types[i].fmt != '\0'; i++)
        if (fms[*ind] == Nou_types[i].fmt)
            return (Nou_types[i].fn(list, buffer, flgs, wdt, prcn, size));

    if (Nou_types[i].fmt == '\0')
    {
        if (fms[*ind] == '\0')
            return (-1);
        ukn_len += write(1, "%%", 1);
        if (fms[*ind - 1] == ' ')
            ukn_len += write(1, " ", 1);
        else if (wdt)
        {
            --(*ind);
            while (fms[*ind] != ' ' && fms[*ind] != '%')
                --(*ind);
            if (fms[*ind] == ' ')
                --(*ind);
            return (1);
        }
        ukn_len += write(1, &fms[*ind], 1);
        return (ukn_len);
    }
    return (prntd_chars);
}

