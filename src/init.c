#include "../includes/philos.h"

void	ft_set_rules(char **argv, t_rules *rules)
{
    struct timeval	tv;
    int             n_philos;

    gettimeofday(&tv, NULL);
    rules->time_init = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	rules->n_philos = atoi(argv[1]);
    n_philos = rules->n_philos;
	rules->death_time = (time_t)atoi(argv[2]);
	rules->time_to_eat = (time_t)atoi(argv[3]);
	rules->time_to_sleep = (time_t)atoi(argv[4]);
	if (argv[5])
		rules->n_meals = (long)atoi(argv[5]);
	rules->forks = malloc(sizeof(int) * rules->n_philos);
    rules->philos = malloc(sizeof(pthread_t *) * rules->n_philos);
    rules->t_philos = malloc(sizeof(t_philo *) * rules->n_philos);
    ft_init_forks(rules->forks, rules->n_philos);
	rules->philo_created = 1;
    rules->mutex = malloc(sizeof(pthread_mutex_t));
    rules->mutex_print = malloc(sizeof(pthread_mutex_t));
    rules->mutex_forks = malloc(sizeof(pthread_mutex_t) * rules->n_philos);
    pthread_mutex_init(rules->mutex, NULL);
    pthread_mutex_init(rules->mutex_print, NULL);
    while (--n_philos >= 0)
        pthread_mutex_init(&rules->mutex_forks[n_philos], NULL);
}

void	ft_init_forks(int *forks, long n_philos) // fill *forks with 1
{
	long    i;

    i = n_philos - 1;
    while (i >= 0)
    {
        forks[i] = 1;
        i--;
    }
}

void	ft_create_philos(t_rules *rules)
{
    int				n_philos;
    int				i;

    n_philos = rules->n_philos;
    i = 0;
    while (i < n_philos)
    {
        rules->philos[i] = malloc(sizeof(pthread_t));
        if (pthread_create(rules->philos[i], NULL, (void *)ft_routine, rules) != 0)
            return ;
        i++;
    }
    i = 0;
    while (i < n_philos)
    {
        if (pthread_join(*rules->philos[i], NULL) != 0)
            return ;
        i++;
    }
    i = 0;
    while (i < n_philos)
        free(rules->philos[i++]);
}