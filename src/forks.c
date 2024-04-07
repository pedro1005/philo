/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:40:42 by pedmonte          #+#    #+#             */
/*   Updated: 2024/04/07 18:40:47 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	ft_even_wait(t_philo *philo, t_rules *rules)
{
	if ((ft_current_time_ms(rules) + rules->time_to_eat) < philo->death_time)
		usleep(rules->time_to_eat * 100);
	pthread_mutex_lock(&rules->mutex_forks[philo->fork_l_pos]);
	if (!ft_check_philo_dead(philo, rules))
		ft_print_message("has taken a fork", philo, rules);
	pthread_mutex_lock(&rules->mutex_forks[philo->fork_r_pos]);
	if (!ft_check_philo_dead(philo, rules))
		ft_print_message("has taken a fork", philo, rules);
	philo->forks_own = 1;
}

void	ft_odd_wait(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex_forks[philo->fork_r_pos]);
	if (!ft_check_philo_dead(philo, rules))
		ft_print_message("has taken a fork", philo, rules);
	pthread_mutex_lock(&rules->mutex_forks[philo->fork_l_pos]);
	if (!ft_check_philo_dead(philo, rules))
		ft_print_message("has taken a fork", philo, rules);
	philo->forks_own = 1;
}

void	ft_get_forks(t_philo *philo, t_rules *rules)
{
	while (!philo->forks_own && !ft_check_end(rules)
		&& !ft_check_philo_dead(philo, rules))
	{
		if (philo->id % 2 == 0)
			ft_even_wait(philo, rules);
		else
			ft_odd_wait(philo, rules);
	}
}
