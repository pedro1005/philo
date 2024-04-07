/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:56:47 by pedmonte          #+#    #+#             */
/*   Updated: 2024/04/07 18:56:51 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	ft_check_philo_dead(t_philo *philo, t_rules *rules)
{
	if (ft_current_time_ms(rules) > philo->death_time)
	{
		pthread_mutex_lock(&rules->mutex);
		if (rules->stop_demo == 0)
		{
			rules->stop_demo = 1;
			pthread_mutex_lock(&rules->mutex_print);
			printf("%ld %d died\n", ft_current_time_ms(rules), philo->id);
			pthread_mutex_unlock(&rules->mutex_print);
			pthread_mutex_unlock(&rules->mutex);
			return (1);
		}
		pthread_mutex_unlock(&rules->mutex);
		return (1);
	}
	return (0);
}

void	ft_update_meal_stat(t_rules *rules, t_philo *philo)
{
	if (!ft_check_end(rules))
	{
		pthread_mutex_lock(&rules->mutex);
		rules->stop_demo = 1;
		pthread_mutex_unlock(&rules->mutex);
		pthread_mutex_lock(&rules->mutex_print);
		printf("%ld %d is thinking\n",
			ft_current_time_ms(rules), philo->id);
		pthread_mutex_unlock(&rules->mutex_print);
	}
}

void	ft_check_meals(t_rules *rules, t_philo *philo)
{
	int	i;
	int	j;

	if (!rules || !rules->t_philos
		|| ft_check_end(rules) || rules->no_count_meal)
		return ;
	i = rules->n_philos - 1;
	j = 0;
	while (i >= 0)
	{
		pthread_mutex_lock(&rules->mutex_meals);
		if (rules->t_philos[i] && rules->t_philos[i]->n_meals >= rules->n_meals)
			j++;
		pthread_mutex_unlock(&rules->mutex_meals);
		i--;
	}
	if (j == rules->n_philos)
		ft_update_meal_stat(rules, philo);
}

void	ft_print_message(char *str, t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex);
	if (rules->stop_demo == 0)
	{
		pthread_mutex_lock(&rules->mutex_print);
		printf("%ld %d %s\n", ft_current_time_ms(rules), philo->id, str);
		pthread_mutex_unlock(&rules->mutex_print);
		pthread_mutex_unlock(&rules->mutex);
	}
	else
		pthread_mutex_unlock(&rules->mutex);
}
