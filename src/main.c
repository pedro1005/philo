
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

void	*ft_routine(t_rules *data)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	pthread_mutex_lock(data->mutex);
	philo->id = data->philo_id++;
	pthread_mutex_unlock(data->mutex);
	philo->death_time = ft_current_time_ms() + data->death_time;
	while (1)
	{
		ft_philo_think(philo);
		ft_get_forks(philo, data);
		ft_eat(data, philo);
	}
    printf("%ld %d died\n", ft_current_time_ms(), philo->id);
	free(philo);
	pthread_mutex_destroy(data->mutex);
	free(data->mutex);
	return (NULL);
}

void	ft_parse_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || argv == NULL)
	{
		write(2, "Invalid args\n", 14);
		exit(0);
	}
}

int main(int argc, char **argv)
{
    t_rules	*rules;

	ft_parse_args(argc, argv);
	rules = malloc(sizeof(t_rules));
	memset(rules, 0, sizeof(t_rules));
	ft_set_rules(argv, rules);
	ft_create_philos(rules);
	free(rules->forks);
	free(rules);
    return (0);
}