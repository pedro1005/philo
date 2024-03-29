#include "../includes/philos.h"

time_t	ft_current_time_ms(t_rules *rules)
{
    struct timeval	tv;
	time_t			current_time;

    gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (current_time - rules->time_init);
}

void	ft_check_numbers(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
			{
				write(2, "Invalid args\n", 14);
				exit(1);
			}
			j++;
		}
		i++;
		j = 0;
	}
}

void	ft_parse_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || argv == NULL)
	{
		write(2, "Invalid args\n", 14);
		exit(1);
	}
	ft_check_numbers(argv);
}

void	ft_get_forks(t_philo *philo, t_rules *rules)
{
	while (!philo->forks_own && !rules->philo_dead)
	{
		if (philo->id < rules->n_philos)
		{
			pthread_mutex_lock(rules->mutex);
			if (ft_check_fork(rules->forks, philo->id) && ft_check_fork(rules->forks, (philo->id) + 1))
			{
				philo->forks_own = 1;
				ft_set_fork(rules->forks, philo->id, 0);
				pthread_mutex_lock(rules->mutex_print);
				printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
				ft_set_fork(rules->forks, philo->id + 1, 0);
				printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
				pthread_mutex_unlock(rules->mutex_print);
			}
			pthread_mutex_unlock(rules->mutex);
			pthread_mutex_lock(rules->mutex);
			if ((philo->death_time <= ft_current_time_ms(rules)) && !rules->philo_dead)
			{
				pthread_mutex_lock(rules->mutex_print);
				printf("%ld %d died\n",ft_current_time_ms(rules), philo->id);
				pthread_mutex_unlock(rules->mutex_print);
				pthread_mutex_lock(&rules->mutex_dead);
				rules->philo_dead = 1;
				pthread_mutex_unlock(&rules->mutex_dead);
				pthread_mutex_unlock(rules->mutex);
				return ;
			}
			pthread_mutex_unlock(rules->mutex);
		}
		if (philo->id == rules->n_philos)
		{
			pthread_mutex_lock(rules->mutex);
			if (ft_check_fork(rules->forks, philo->id) && ft_check_fork(rules->forks, 1))
			{
				philo->forks_own = 1;
				ft_set_fork(rules->forks, philo->id, 0);
				pthread_mutex_lock(rules->mutex_print);
				printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
				ft_set_fork(rules->forks, 1, 0);
				printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
				pthread_mutex_unlock(rules->mutex_print);
			}
			pthread_mutex_unlock(rules->mutex);
			pthread_mutex_lock(rules->mutex);
			if ((philo->death_time <= ft_current_time_ms(rules)) && !rules->philo_dead)
			{
				printf("%ld %d died\n",ft_current_time_ms(rules), philo->id);
				pthread_mutex_lock(&rules->mutex_dead);
				rules->philo_dead = 1;
				pthread_mutex_unlock(&rules->mutex_dead);
				pthread_mutex_unlock(rules->mutex);
				return ;
			}
			pthread_mutex_unlock(rules->mutex);
		}
	}
}
