#include "../includes/philos.h"

int ft_check_fork(int *number, int id)
{
    return (number[id - 1]);
}

void ft_set_fork(int *forks,int id, int state)
{
    forks[id - 1] = state;
}