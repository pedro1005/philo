#include "../includes/philos.h"

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

void	ft_clear_bit(long *num, int pos)
{
	int	mask;

	mask = ~(1 << (pos - 1));
	*num = *num & mask;
}

void    ft_open_bit(long *num, int pos) // set bit to 1
{
    int mask;

    mask = (1 << (pos - 1));
    *num = *num | mask;
}
