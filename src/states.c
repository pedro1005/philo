#include "../includes/philos.h"

void	ft_philo_sleep(t_philo *philo, t_rules *rules)
{
	if (!philo || !rules || rules->philo_dead || rules->philos_eaten)
		return ;
	pthread_mutex_lock(rules->mutex_print);
	printf("%ld %d is sleeping\n", ft_current_time_ms(rules), philo->id);
	pthread_mutex_unlock(rules->mutex_print);
	usleep(rules->time_to_sleep * 1000);
}

void	ft_philo_think(t_philo *philo, t_rules *rules)
{
	if (!philo || !rules || rules->philo_dead || rules->philos_eaten)
		return ;
	pthread_mutex_lock(rules->mutex_print);
	printf("%ld %d is thinking\n",ft_current_time_ms(rules), philo->id);
	pthread_mutex_unlock(rules->mutex_print);
	return ;
}

void	ft_eat(t_rules *rules, t_philo * philo)
{
	time_t	eating;

	if (!rules || !philo || rules->philo_dead || rules->philos_eaten)
		return ;
	philo->death_time = ft_current_time_ms(rules) + rules->death_time;
	eating = ft_current_time_ms(rules) + rules->time_to_eat;
	pthread_mutex_lock(rules->mutex_print);
	printf("%ld %d is eating\n", ft_current_time_ms(rules), philo->id);
	pthread_mutex_unlock(rules->mutex_print);
	while (!ft_check_end(rules) && ft_current_time_ms(rules) < eating)
	{
		usleep(10);
		if (ft_check_philo_dead(philo, rules))
		{
			pthread_mutex_lock(rules->mutex);
			rules->stop_demo = 1;
			pthread_mutex_unlock(rules->mutex);
			pthread_mutex_lock(rules->mutex_print);
			printf("%ld %d is dead\n", ft_current_time_ms(rules), philo->id);
			pthread_mutex_unlock(rules->mutex_print);
			return ;
		}
	}
	pthread_mutex_lock(rules->mutex);
	philo->n_meals++;
	pthread_mutex_unlock(rules->mutex);
	pthread_mutex_lock(&rules->mutex_forks[philo->fork_l_pos]);
	rules->forks[philo->fork_l_pos] = 1;
	pthread_mutex_unlock(&rules->mutex_forks[philo->fork_l_pos]);
	pthread_mutex_lock(&rules->mutex_forks[philo->fork_r_pos]);
	rules->forks[philo->fork_r_pos] = 1;
	pthread_mutex_unlock(&rules->mutex_forks[philo->fork_r_pos]);
	philo->forks_own = 0;
}