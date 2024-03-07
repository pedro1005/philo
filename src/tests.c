#include <stdio.h>

int ft_get_bit(long number, int pos)
{
    int mask;
    int result;

    mask = 1 << (pos - 1);
    result = number & mask;
    if (result != 0)
        return (1);
    else   
        return (0);
}

int main(void)
{
    int num = 60;
    int pos = 5;
    printf("number %d has bit %d in position %d\n", num, ft_get_bit(num, pos), pos);

    return (0);
}