#include "../includes/philos.h"

time_t	ft_current_time_ms(t_rules *rules)
{
    struct timeval	tv;
	time_t			current_time;
	time_t			result;

    gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	result = current_time - rules->time_init;
    return (result);
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

int	ft_check_philo_dead(t_philo *philo, t_rules *rules)
{
	if (!philo || !rules)
		return (1);
	pthread_mutex_lock(rules->mutex);
	if (ft_current_time_ms(rules) >= philo->death_time)
	{
		if (rules->stop_demo)
		{
			pthread_mutex_unlock(rules->mutex);
			return (1);
		}
		rules->stop_demo = 1;
		pthread_mutex_unlock(rules->mutex);
		pthread_mutex_lock(rules->mutex_print);
		printf("%ld %d died\n", ft_current_time_ms(rules), philo->id);
		pthread_mutex_unlock(rules->mutex_print);
		return (1);
	}
	pthread_mutex_unlock(rules->mutex);
	return (0);
}

void	ft_get_forks(t_philo *philo, t_rules *rules)
{
	if (!rules || !philo)
		return ;
	while (!philo->forks_own && !ft_check_end(rules) && !ft_check_philo_dead(philo, rules))
	{
		if (philo->id % 2 == 0)
			usleep(5000);
		pthread_mutex_lock(&rules->mutex_forks[philo->fork_l_pos]);
		if (rules->forks[philo->fork_l_pos])
		{
			rules->forks[philo->fork_l_pos] = 0;
			pthread_mutex_lock(rules->mutex_print);
			if (!ft_check_end(rules))
				printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
			pthread_mutex_unlock(rules->mutex_print);
			pthread_mutex_unlock(&rules->mutex_forks[philo->fork_l_pos]);
			while (!philo->forks_own && !ft_check_end(rules) && !ft_check_philo_dead(philo, rules))
			{
				pthread_mutex_lock(&rules->mutex_forks[philo->fork_r_pos]);
				if (rules->forks[philo->fork_r_pos])
				{
					rules->forks[philo->fork_r_pos] = 0;
					pthread_mutex_lock(rules->mutex_print);
					if (!ft_check_end(rules))
						printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
					pthread_mutex_unlock(rules->mutex_print);
					pthread_mutex_unlock(&rules->mutex_forks[philo->fork_r_pos]);
					philo->forks_own = 1;
				}
				else
					pthread_mutex_unlock(&rules->mutex_forks[philo->fork_r_pos]);
			}
		}
		else
			pthread_mutex_unlock(&rules->mutex_forks[philo->fork_l_pos]);
	}
}

int		ft_check_meals(t_rules *rules)
{
	if (!rules || !rules->t_philos || rules->stop_demo)
		return (1);
	else if (!rules->n_meals)
		return (0);
	int	i;
	int	j;

	i = rules->n_philos - 1;
	j = 0;
	while (i >= 0)
	{
		if (rules->t_philos[i] && rules->t_philos[i]->n_meals >= rules->n_meals)
			j++;
		i--;
	}
	if (j == rules->n_philos)
	{
		//pthread_mutex_lock(rules->mutex);
		if (rules->stop_demo == 0)
		{
			pthread_mutex_lock(rules->mutex_print);
			printf("all philos eaten %ld times!\n", rules->n_meals);
			pthread_mutex_unlock(rules->mutex_print);
		}
		rules->stop_demo = 1;
		//pthread_mutex_unlock(rules->mutex);
		return (1);
	}
	return (0);
}
