#include <myprintf.h>
static int primitive_printf(const char* format_p, ...)
{
    if (format_p == NULL)
    {
        perror("length == NULL");
        return -1;
    }

    const size_t length = strlen(format_p);

    if (length == 0)
    {   
        perror("length == 0");
        return -1;
    }

    va_list va_list;
    va_start(va_list, format_p);

    for (size_t i = 0; i < length; ++i)
    {
        if (format_p[i] == '%')
        {
            i += 1;

            switch (format_p[i])
            {
                case 'c':
                    printf("%c", (char)va_arg(va_list, int));
                    break;

                case 'd':
                    printf("%d", (int)va_arg(va_list, int));
                    break;
                
                default:
                    perror("Unsupported type!");
                    break;
            }
        }
        else
        {
            printf("%c", format_p[i]);
        }
    }

    va_end(va_list);

    return (int)length;
}

int main(void)
{
    primitive_printf("%carsztaty Embedded w roku %d!\n", 'W', 2021);
    return 0;
}

