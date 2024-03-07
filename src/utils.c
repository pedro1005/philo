#include "../includes/philos.h"

time_t ft_current_time_ms()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void	ft_get_forks(t_philo *philo, t_rules *rules)
{
	while (!philo->forks_own)
	{
		if (philo->id < rules->n_philos)
		{
			pthread_mutex_lock(rules->mutex);
			if (ft_get_bit(*rules->forks, philo->id) && ft_get_bit(*rules->forks, (philo->id) + 1))
			{
				philo->forks_own = 1;
				ft_clear_bit(rules->forks, philo->id);
				printf("%ld %d has taken a fork\n", ft_current_time_ms(), philo->id);
				ft_clear_bit(rules->forks, (philo->id) + 1);
				printf("%ld %d has taken a fork\n", ft_current_time_ms(), philo->id);
			}
			pthread_mutex_unlock(rules->mutex);
			if (philo->death_time <= ft_current_time_ms())
			{
				printf("%d died waiting\n", philo->id);
				exit(1);
			}
		}
		else if (philo->id == rules->n_philos)
		{
			pthread_mutex_lock(rules->mutex);
			if (ft_get_bit(*rules->forks, philo->id) && ft_get_bit(*rules->forks, 1))
			{
				philo->forks_own = 1;
				ft_clear_bit(rules->forks, philo->id);
				printf("%ld %d has taken a fork\n", ft_current_time_ms(), philo->id);
				ft_clear_bit(rules->forks, 1);
				printf("%ld %d has taken a fork\n", ft_current_time_ms(), philo->id);
			}
			pthread_mutex_unlock(rules->mutex);
			if (philo->death_time <= ft_current_time_ms())
			{
				printf("%d died waiting\n", philo->id);
				exit(1);
			}
		}
	}
}