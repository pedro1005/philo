/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:46:23 by pedmonte          #+#    #+#             */
/*   Updated: 2024/04/07 18:46:27 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!rules)
		return (1);
	pthread_mutex_lock(&rules->mutex);
	if (rules->stop_demo == 1)
	{
		pthread_mutex_unlock(&rules->mutex);
		return (1);
	}
	pthread_mutex_unlock(&rules->mutex);
	return (0);
}

void	ft_sync_philos(t_rules *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		if (data->philo_created >= data->n_philos)
		{
			pthread_mutex_unlock(&data->mutex);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&data->mutex);
			usleep(10);
		}
	}
}

void	*ft_routine(t_rules *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	ft_init_philo(philo, data);
	ft_sync_philos(data);
	if (data->n_philos == 1)
	{
		pthread_mutex_lock(&data->mutex_forks[philo->fork_l_pos]);
		ft_print_message("has taken a fork", philo, data);
		pthread_mutex_unlock(&data->mutex_forks[philo->fork_l_pos]);
		while (!ft_check_philo_dead(philo, data))
			usleep(100);
		free(philo);
		return (NULL);
	}
	while (!ft_check_end(data) && !ft_check_philo_dead(philo, data))
	{
		ft_get_forks(philo, data);
		ft_eat(data, philo);
		ft_philo_sleep(philo, data);
		ft_philo_think(philo, data);
	}
	free(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (!ft_parse_args(argc, argv))
		return (0);
	rules = malloc(sizeof(t_rules));
	memset(rules, 0, sizeof(t_rules));
	ft_set_rules(argv, rules);
	ft_create_philos(rules);
	pthread_mutex_destroy(&rules->mutex);
	pthread_mutex_destroy(&rules->mutex_print);
	pthread_mutex_destroy(&rules->mutex_meals);
	free(rules->t_philos);
	free(rules->philos);
	free(rules->mutex_forks);
	free(rules);
	return (0);
}
