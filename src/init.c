#include "../includes/philos.h"

void	ft_set_rules(char **argv, t_rules *rules)
{
	rules->n_philos = atoi(argv[1]);
	rules->death_time = (time_t)atoi(argv[2]);
	rules->time_to_eat = (time_t)atoi(argv[3]);
	rules->time_to_sleep = (time_t)atoi(argv[4]);
	if (argv[5])
		rules->n_meals = atoi(argv[5]);
	rules->forks = malloc(sizeof(long));
    ft_set_forks(rules->forks, rules->n_philos);
	rules->philo_id = 1;
    rules->mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(rules->mutex, NULL);
}

void	ft_set_forks(long *forks, int pos) // fill *forks with 1
{
	long	mask;

	mask = (1 << pos) - 1;
	*forks |= mask;
}

void	ft_create_philos(t_rules *rules)
{
    int				n_philos;
    int				i;
	pthread_t	**philos;

    n_philos = rules->n_philos;
    i = 0;
    philos = malloc(sizeof(pthread_t *) * n_philos);
    while (i < n_philos)
    {
        philos[i] = malloc(sizeof(pthread_t));
        if (pthread_create(philos[i], NULL, (void *)ft_routine, rules) != 0)
            return ;
        i++;
    }
    rules->philos = philos;
    i = 0;
    while (i < n_philos)
    {
        if (pthread_join(*philos[i], NULL) != 0)
            return ;
        free(philos[i]);
        i++;
    }
    free(philos);
}