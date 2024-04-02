#include "../includes/philos.h"

void	ft_philo_sleep(t_philo *philo, t_rules *rules)
{
	time_t	sleeping;

	if (!philo || !rules || rules->stop_demo)
		return ;
	sleeping = ft_current_time_ms(rules) + rules->time_to_sleep;
	pthread_mutex_lock(rules->mutex_print);
	if (!ft_check_end(rules))
		printf("%ld %d is sleeping\n", ft_current_time_ms(rules), philo->id);
	pthread_mutex_unlock(rules->mutex_print);
	while (!ft_check_end(rules) && ft_current_time_ms(rules) < sleeping)
	{
		usleep(10);
		ft_check_philo_dead(philo, rules);
	}
}

void	ft_philo_think(t_philo *philo, t_rules *rules)
{
	if (!philo || !rules || ft_check_end(rules))
		return ;
	pthread_mutex_lock(rules->mutex_print);
	if (!ft_check_end(rules))
		printf("%ld %d is thinking\n",ft_current_time_ms(rules), philo->id);
	pthread_mutex_unlock(rules->mutex_print);
	return ;
}

void	ft_eat(t_rules *rules, t_philo * philo)
{
	time_t	eating;

	if (!rules || !philo || rules->stop_demo)
		return ;
	pthread_mutex_lock(rules->mutex);
	philo->death_time = ft_current_time_ms(rules) + rules->death_time;
	eating = ft_current_time_ms(rules) + rules->time_to_eat;
	pthread_mutex_unlock(rules->mutex);
	pthread_mutex_lock(rules->mutex_print);
	if (!rules->stop_demo)
		printf("%ld %d is eating\n", ft_current_time_ms(rules), philo->id);
	pthread_mutex_unlock(rules->mutex_print);
	while (!ft_check_end(rules) && ft_current_time_ms(rules) < eating)
	{
		usleep(10);
		if (ft_check_end(rules) || ft_check_philo_dead(philo, rules))
			return ;
	}
	pthread_mutex_lock(rules->mutex);
	philo->n_meals++;
	ft_check_meals(rules);
	pthread_mutex_unlock(rules->mutex);
	pthread_mutex_lock(&rules->mutex_forks[philo->fork_l_pos]);
	rules->forks[philo->fork_l_pos] = 1;
	pthread_mutex_unlock(&rules->mutex_forks[philo->fork_l_pos]);
	pthread_mutex_lock(&rules->mutex_forks[philo->fork_r_pos]);
	rules->forks[philo->fork_r_pos] = 1;
	pthread_mutex_unlock(&rules->mutex_forks[philo->fork_r_pos]);
	philo->forks_own = 0;
}