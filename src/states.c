#include "../includes/philos.h"

void	ft_philo_sleep(t_philo *philo, t_rules *rules)
{
	time_t	sleeping;

	if (!philo || !rules || ft_check_end(rules))
		return ;
	sleeping = ft_current_time_ms(rules) + rules->time_to_sleep;
	if (!ft_check_end(rules))
	{
		pthread_mutex_lock(&rules->mutex_print);
		printf("%ld %d is sleeping\n", ft_current_time_ms(rules), philo->id);
		pthread_mutex_unlock(&rules->mutex_print);
	}
	while (!ft_check_end(rules) && ft_current_time_ms(rules) < sleeping)
	{
		usleep(10);
		ft_check_philo_dead(philo, rules);
	}
}

void	ft_philo_think(t_philo *philo, t_rules *rules)
{
	if (!philo)
		return ;
	ft_print_message("is thinking", &rules->mutex_print, philo, rules);
}

void	ft_print_message(char *str, pthread_mutex_t *mutex, t_philo *philo, t_rules *rules)
{
	if (!ft_check_end(rules))
	{
		pthread_mutex_lock(mutex);
		printf("%ld %d %s\n", ft_current_time_ms(rules), philo->id, str);
		pthread_mutex_unlock(mutex);
	}
}

void	ft_eat(t_rules *rules, t_philo * philo)
{
	time_t	eating;

	if (!rules || !philo || ft_check_end(rules))
		return ;
	philo->death_time = ft_current_time_ms(rules) + rules->death_time;
	eating = ft_current_time_ms(rules) + rules->time_to_eat;
	ft_print_message("is eating", &rules->mutex_print, philo, rules);
	while (!ft_check_end(rules) && ft_current_time_ms(rules) < eating)
	{
		usleep(10);
		if (ft_check_end(rules) || ft_check_philo_dead(philo, rules))
			return ;
	}
	pthread_mutex_lock(&rules->mutex_forks[philo->fork_l_pos]);
	rules->forks[philo->fork_l_pos] = 1;
	pthread_mutex_unlock(&rules->mutex_forks[philo->fork_l_pos]);
	pthread_mutex_lock(&rules->mutex_forks[philo->fork_r_pos]);
	rules->forks[philo->fork_r_pos] = 1;
	pthread_mutex_unlock(&rules->mutex_forks[philo->fork_r_pos]);
	pthread_mutex_lock(&rules->mutex_meals);
	philo->n_meals++;
	pthread_mutex_unlock(&rules->mutex_meals);
	ft_check_meals(rules);
	philo->forks_own = 0;
}