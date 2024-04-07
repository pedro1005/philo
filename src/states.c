/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:49:52 by pedmonte          #+#    #+#             */
/*   Updated: 2024/04/07 18:49:55 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	ft_philo_sleep(t_philo *philo, t_rules *rules)
{
	time_t	sleeping;

	if (!philo || !rules || ft_check_end(rules))
		return ;
	sleeping = ft_current_time_ms(rules) + rules->time_to_sleep;
	pthread_mutex_lock(&rules->mutex);
	if (rules->stop_demo == 0)
	{
		pthread_mutex_lock(&rules->mutex_print);
		printf("%ld %d is sleeping\n", ft_current_time_ms(rules), philo->id);
		pthread_mutex_unlock(&rules->mutex_print);
	}
	pthread_mutex_unlock(&rules->mutex);
	while (!ft_check_end(rules) && ft_current_time_ms(rules) <= sleeping)
	{
		usleep(1000);
		ft_check_philo_dead(philo, rules);
	}
}

void	ft_philo_think(t_philo *philo, t_rules *rules)
{
	if (!philo)
		return ;
	ft_print_message("is thinking", philo, rules);
}

void	ft_unlock_forks(t_philo *philo, t_rules *rules)
{
	pthread_mutex_unlock(&rules->mutex_forks[philo->fork_l_pos]);
	pthread_mutex_unlock(&rules->mutex_forks[philo->fork_r_pos]);
}

void	ft_eat(t_rules *rules, t_philo *philo)
{
	time_t	eating;

	if (!rules || !philo || ft_check_philo_dead(philo, rules))
	{
		ft_unlock_forks(philo, rules);
		return ;
	}
	philo->death_time = ft_current_time_ms(rules) + rules->death_time;
	eating = ft_current_time_ms(rules) + rules->time_to_eat;
	ft_print_message("is eating", philo, rules);
	while (!ft_check_end(rules) && ft_current_time_ms(rules) <= eating)
	{
		usleep(100);
		if (ft_check_end(rules) || ft_check_philo_dead(philo, rules))
		{
			ft_unlock_forks(philo, rules);
			return ;
		}
	}
	ft_unlock_forks(philo, rules);
	pthread_mutex_lock(&rules->mutex_meals);
	philo->n_meals++;
	pthread_mutex_unlock(&rules->mutex_meals);
	ft_check_meals(rules, philo);
	philo->forks_own = 0;
}
