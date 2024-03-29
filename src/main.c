
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

int	ft_check_end(t_rules *rules)
{
	pthread_mutex_lock(rules->mutex);
	if (rules->philo_dead || rules->philos_eaten)
	{
		pthread_mutex_unlock(rules->mutex);
		return (1);
	}
	pthread_mutex_unlock(rules->mutex);
	return (0);
}

void	*ft_routine(t_rules *data)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	pthread_mutex_lock(data->mutex);
	philo->id = data->philo_id++;
	data->t_philos[philo->id - 1] = philo;
	pthread_mutex_unlock(data->mutex);
	while (data->philo_id < data->n_philos)							//sync threads
		usleep(10);
	philo->death_time = ft_current_time_ms(data) + data->death_time;
	while (1)
	{
		ft_get_forks(philo, data);
		ft_eat(data, philo);
		ft_philo_sleep(philo, data);
		ft_philo_think(philo, data);
		if (ft_check_end(data))
			break ;
	}
	free(philo);
	return (NULL);
}

int main(int argc, char **argv)
{
    t_rules	*rules;

	ft_parse_args(argc, argv);
	rules = malloc(sizeof(t_rules));
	memset(rules, 0, sizeof(t_rules));
	ft_set_rules(argv, rules);
	//printf("n_meals = %ld\n", rules->n_meals);
	ft_create_philos(rules);
	free(rules->forks);
	pthread_mutex_destroy(rules->mutex);
	pthread_mutex_destroy(rules->mutex_print);
	free(rules->mutex);
	free(rules->mutex_print);
	free(rules->t_philos);
	free(rules->philos);
	free(rules->mutex_forks);
	free(rules);
    return (0);
}