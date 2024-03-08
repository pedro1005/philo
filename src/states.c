#include "../includes/philos.h"

void	ft_philo_think(t_philo *philo, t_rules *rules)
{
	printf("%ld %d is thinking\n",ft_current_time_ms(rules), philo->id);
}

void	ft_eat(t_rules *rules, t_philo * philo)
{
	philo->death_time = ft_current_time_ms(rules) + rules->death_time;
	printf("%ld %d is eating\n", ft_current_time_ms(rules), philo->id);
	usleep(rules->time_to_eat * 1000);
	if (philo->id != rules->n_philos)
	{
		pthread_mutex_lock(rules->mutex);
		ft_open_bit(rules->forks, philo->id);
		ft_open_bit(rules->forks, (philo->id) + 1);
		pthread_mutex_unlock(rules->mutex);
	}
	else if (philo->id == rules->n_philos)
	{
		pthread_mutex_lock(rules->mutex);
		ft_open_bit(rules->forks, philo->id);
		ft_open_bit(rules->forks, 1);
		pthread_mutex_unlock(rules->mutex);	
	}
	philo->forks_own = 0;
	philo->n_meals++;
}