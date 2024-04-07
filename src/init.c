/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:41:35 by pedmonte          #+#    #+#             */
/*   Updated: 2024/04/07 18:41:38 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	ft_set_rules(char **argv, t_rules *rules)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	rules->time_init = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	rules->n_philos = atoi(argv[1]);
	rules->death_time = (time_t)ft_long_atoi(argv[2]);
	rules->time_to_eat = (time_t)ft_long_atoi(argv[3]);
	rules->time_to_sleep = (time_t)ft_long_atoi(argv[4]);
	if (argv[5])
	{
		rules->n_meals = ft_long_atoi(argv[5]);
		if (rules->n_meals <= 0)
			rules->stop_demo = 1;
	}
	else
		rules->no_count_meal = 1;
	rules->philos = (pthread_t **)malloc(sizeof(pthread_t *) * rules->n_philos);
	rules->t_philos = (t_philo **)malloc(sizeof(t_philo *) * rules->n_philos);
	rules->mutex_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* rules->n_philos);
	ft_init_mutaxes(rules);
}

void	ft_init_mutaxes(t_rules *rules)
{
	int	n_philos;

	n_philos = rules->n_philos;
	pthread_mutex_init(&rules->mutex, NULL);
	pthread_mutex_init(&rules->mutex_print, NULL);
	pthread_mutex_init(&rules->mutex_meals, NULL);
	while (--n_philos >= 0)
		pthread_mutex_init(&rules->mutex_forks[n_philos], NULL);
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
		if (pthread_create(rules->philos[i], NULL,
				(void *)ft_routine, rules) != 0)
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

void	ft_init_philo(t_philo *philo, t_rules *data)
{
	philo->death_time = ft_current_time_ms(data) + data->death_time;
	pthread_mutex_lock(&data->mutex);
	data->philo_created++;
	philo->id = data->philo_created;
	data->t_philos[philo->id - 1] = philo;
	pthread_mutex_unlock(&data->mutex);
	philo->fork_l_pos = philo->id - 1;
	if (philo->id != data->n_philos)
		philo->fork_r_pos = philo->id;
}

void	ft_parse_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || argv == NULL)
	{
		write(2, "Invalid args\n", 13);
		exit(1);
	}
	ft_check_numbers(argv);
}
