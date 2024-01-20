#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int print_char(char c)
{
    return write(1, &c, 1);
}

int print_str(char *str)
{
    int count;

    count = 0;
    while (*str)
    {
        print_char((int)*str);
        ++count;
        ++str;
    }
    return count;
}

int print_digit(long n, int base)
{
    int count;
    char *symbols = "0123456789abcdef";

    if (n < 0)
    {
        write(1, "-", 1);
        return print_digit(-n, base) + 1;
    }
    else if (n < base)
    {
        return print_char(symbols[n]);
    }
    else
    {
        count = print_digit(n / base, base);
        return count + print_digit(n % base, base);
    }
}

int print_format(char specifier, va_list ap)
{

    int count;
    count = 0;
    if (specifier == 'c')
    {
        count += print_char(va_arg(ap, int));
    }
    else if (specifier == 's')
    {
        count += print_str(va_arg(ap, char *));
    }
    else if (specifier == 'd')
    {
        count += print_digit((long)(va_arg(ap, int)), 10);
    }
    else if (specifier == 'x')
    {
        count += print_digit((long)(va_arg(ap, unsigned int)), 16);
    }
    else
    {
        count += write(1, &specifier, 1);
    }
    return count;
}

int myprintf(const char *format, ...)
{
    va_list ap;
    int count;
    va_start(ap, format);
    count = 0;
    while (*format != '\0')
    {
        if (*format == '%')
        {
            count += print_format(*++format, ap);
        }
        else
        {
            count += write(1, format, 1);
        }
        ++format;
    }
    va_end(ap);
    return count;
}

int main()
{
    int count;
    // count = myprintf("Hello %s \n", "mohamed");

    // myprintf("The chars written are %d\n", count);
    /*
    count = myprintf("%x\n", 42);
    myprintf("the chars writen are :%d\n", count);
    count = printf("%x\n", 42);
    printf("the chars writen are :%d", count);
    */

    myprintf("hello %s,today is %d, in hex %x, char -> %c\n", "mohamed", 27, 27, 'z');

    return 0;
}
