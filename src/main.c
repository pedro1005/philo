#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "../includes/philos.h"

/*                  ***RULES***
* n_forks = n_philos;
* eat->sleep->think (repeat);
* each philo use 2 forks (left and right);
*
* Your(s) program(s) should take the following arguments:
* 	number_of_philosophers
	time_to_die
	time_to_eat
	time_to_sleep
* 	[number_of_times_each_philosopher_must_eat]
*
* About the logs of your program:
*  .Any state change of a philosopher must be formatted as follows:
*  .timestamp_in_ms X has taken a fork
*  .timestamp_in_ms X is eating
*  .timestamp_in_ms X is sleeping
*  .timestamp_in_ms X is thinking
*  .timestamp_in_ms X died
*/



void	ft_set_rules(char **argv, t_rules *rules, long *forks)
{
	rules->n_philos = atoi(argv[1]);
	ft_set_forks(forks, rules->n_philos);
	rules->time_left = atoi(argv[2]);
	rules->time_to_eat = atoi(argv[3]);
	rules->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		rules->n_meals = atoi(argv[5]);
	rules->forks = forks;
	rules->philo_id = 1;
}

long long ft_current_time_ms()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
}

void	ft_set_forks(long *forks, int philos) // fill *forks with 1
{
	long	mask;

	mask = (1 << philos) - 1;
	*forks |= mask;
}

void	*ft_routine(t_rules *data)
{
	long	id;
	pthread_mutex_t	mutex;
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	id = data->philo_id++;
	pthread_mutex_unlock(&mutex);
	philo->death_time = ft_current_time_ms() + data->time_left;

	while (ft_current_time_ms() < philo->death_time)
	{
		printf("philo alive at: %lld\n", ft_current_time_ms());
	}

    printf("Philo with id ´%ld´ died!\n", id);
	free(philo);

	return (NULL);
}

void	ft_create_philos(t_rules *rules)
{
    int				n_philos;
    int				i;
    pthread_mutex_t	mutex;
	pthread_t	**philos;

    pthread_mutex_init(&mutex, NULL);
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

int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	    return (0);
    t_rules	*rules;
	long	*forks;
	//t_philo *philo;
	rules = malloc(sizeof(t_rules));
	forks = malloc(sizeof(long));
	*forks = 0;
	//ft_set_forks(forks, atoi(argv[1]));

	//philo = malloc(sizeof(t_philo));

	memset(rules, 0, sizeof(t_rules));
	//memset(philo, 0, sizeof(t_philo));
	ft_set_rules(argv, rules, forks);
	ft_create_philos(rules);

	//long long time = current_time_ms();

	/*philo->time_left = time + rules->time_left;
	while (current_time_ms() < philo->time_left)
	{
		printf("philo alive at: %lld\n", current_time_ms());
	}
	printf("\nphilo died at: %lld\n", current_time_ms());*/

	free(rules);
	free(forks);
	//free(philo);
	


    return 0;
}