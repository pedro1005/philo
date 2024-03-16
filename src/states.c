#include "../includes/philos.h"

void	ft_philo_sleep(t_philo *philo, t_rules *rules)
{
	if (!philo || !rules || rules->philo_dead)
		return ;
	pthread_mutex_lock(rules->mutex_print);
	printf("%ld %d is sleeping\n", ft_current_time_ms(rules), philo->id);
	pthread_mutex_unlock(rules->mutex_print);
	usleep(rules->time_to_sleep * 1000);
}

void	ft_philo_think(t_philo *philo, t_rules *rules)
{
	if (!philo || !rules || rules->philo_dead)
		return ;
	pthread_mutex_lock(rules->mutex_print);
	printf("%ld %d is thinking\n",ft_current_time_ms(rules), philo->id);
	pthread_mutex_unlock(rules->mutex_print);
	return ;
}

void	ft_eat(t_rules *rules, t_philo * philo)
{
	if (!rules || !philo || rules->philo_dead)
		return ;
	philo->death_time = ft_current_time_ms(rules) + rules->death_time;
	pthread_mutex_lock(rules->mutex_print);
	printf("%ld %d is eating\n", ft_current_time_ms(rules), philo->id);
	pthread_mutex_unlock(rules->mutex_print);
	usleep(rules->time_to_eat * 1000);
	if (philo->id != rules->n_philos)
	{
		pthread_mutex_lock(rules->mutex);
		ft_set_fork(rules->forks, philo->id, 1);
		ft_set_fork(rules->forks, philo->id + 1, 1);
		pthread_mutex_unlock(rules->mutex);
	}
	else if (philo->id == rules->n_philos)
	{
		pthread_mutex_lock(rules->mutex);
		ft_set_fork(rules->forks, philo->id, 1);
		ft_set_fork(rules->forks, 1, 1);
		pthread_mutex_unlock(rules->mutex);	
	}
	philo->forks_own = 0;
	philo->n_meals++;
}