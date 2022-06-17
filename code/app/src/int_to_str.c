#include "int_to_str.h"

const char* int_to_str(uint16_t integer)
{
    char str_inverted[16];
    char str_final[16];

    int pocet_cifer = 0;

    while (integer > 0)
    {
        if (!(integer % 10))
        {
            str_inverted[pocet_cifer] = '0';
        }
        else
        {
            str_inverted[pocet_cifer] = (integer % 10) + '0';
        }
        integer /= 10;
        ++pocet_cifer;
    }

    str_inverted[pocet_cifer] = '/0';

    for (int i=0; i < pocet_cifer; i++)
    {
        int index = pocet_cifer - i - 1;
        str_final[i] = str_inverted[index];
    }
    str_final[pocet_cifer] = '\0';

    return (str_final);
}