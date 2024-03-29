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

int	ft_check_philo_dead(t_philo *philo, t_rules *rules)
{
	if (ft_current_time_ms(rules) >= philo->death_time)
	{
		pthread_mutex_lock(rules->mutex);
		rules->philo_dead = 1;
		printf("%ld %d died\n", ft_current_time_ms(rules), philo->id);
		pthread_mutex_unlock(rules->mutex);
		return (1);
	}
	return (0);
}

void	ft_get_forks(t_philo *philo, t_rules *rules)
{
	while (!philo->forks_own && !ft_check_end(rules) && !ft_check_philo_dead(philo, rules))
	{
		if (philo->id < rules->n_philos)
		{
			pthread_mutex_lock(&rules->mutex_forks[philo->id - 1]);
			if (rules->forks[philo->id - 1])
			{
				//rules->forks[philo->id - 1] = 0;
				//pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);
				pthread_mutex_lock(&rules->mutex_forks[philo->id]);
				if (rules->forks[philo->id])
					{
						rules->forks[philo->id] = 0;
						rules->forks[philo->id - 1] = 0;  // remove
						pthread_mutex_unlock(&rules->mutex_forks[philo->id]);
						pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]); //remove
						philo->forks_own = 1;
						printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
						printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
					}
				else
				{
					pthread_mutex_unlock(&rules->mutex_forks[philo->id]);
					//pthread_mutex_lock(&rules->mutex_forks[philo->id - 1]);
					//rules->forks[philo->id - 1] = 1;
					pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);
				}
			}
			else
				pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);

		}
		else if (philo->id == rules->n_philos)
		{
			pthread_mutex_lock(&rules->mutex_forks[philo->id - 1]);
			if (rules->forks[philo->id - 1])
			{
				//rules->forks[philo->id - 1] = 0;
				//pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);
				pthread_mutex_lock(&rules->mutex_forks[0]);
				if (rules->forks[0])
					{
						rules->forks[0] = 0;
						rules->forks[philo->id - 1] = 0; //remove
						pthread_mutex_unlock(&rules->mutex_forks[0]);
						pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);  // remove
						philo->forks_own = 1;
						printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
						printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
					}
				else
				{
					pthread_mutex_unlock(&rules->mutex_forks[0]);
					//pthread_mutex_lock(&rules->mutex_forks[philo->id - 1]);
					//rules->forks[philo->id - 1] = 1;
					pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);
				}
			}
			else
				pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);
		}
	}
	/*
	while (!philo->forks_own && !rules->philo_dead && !rules->philos_eaten)
	{
		if (philo->id < rules->n_philos)
		{
			pthread_mutex_lock(&rules->mutex_forks[philo->id]);
			pthread_mutex_lock(&rules->mutex_forks[philo->id - 1]);
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
			if ((philo->death_time <= ft_current_time_ms(rules)) && !rules->philo_dead)
			{
				pthread_mutex_lock(rules->mutex_print);
				printf("%ld %d died\n",ft_current_time_ms(rules), philo->id);
				pthread_mutex_unlock(rules->mutex_print);
				pthread_mutex_lock(&rules->mutex_dead);
				rules->philo_dead = 1;
				pthread_mutex_unlock(&rules->mutex_dead);
				pthread_mutex_unlock(&rules->mutex_forks[philo->id]);
				pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);
				return ;
			}
			pthread_mutex_unlock(&rules->mutex_forks[philo->id]);
			pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);
		}
		if (philo->id == rules->n_philos)
		{
			pthread_mutex_lock(&rules->mutex_forks[0]);
			pthread_mutex_lock(&rules->mutex_forks[philo->id - 1]);
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
			if ((philo->death_time <= ft_current_time_ms(rules)) && !rules->philo_dead)
			{
				printf("%ld %d died\n",ft_current_time_ms(rules), philo->id);
				pthread_mutex_lock(&rules->mutex_dead);
				rules->philo_dead = 1;
				pthread_mutex_unlock(&rules->mutex_dead);
				pthread_mutex_unlock(&rules->mutex_forks[0]);
				pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);
				return ;
			}
			pthread_mutex_unlock(&rules->mutex_forks[0]);
			pthread_mutex_unlock(&rules->mutex_forks[philo->id - 1]);
		}
	}*/
}

int		ft_check_meals(t_rules *rules)
{
	if (!rules)
		return (1);
	int	i;
	int	j;

	i = rules->n_philos - 1;
	j = 0;
	while (i >= 0)
	{
		if (rules->t_philos[i]->n_meals >= rules->n_meals)
			j++;
		i--;
	}
	if (j == rules->n_philos)
	{
		printf("all philos eaten %ld times!\n", rules->n_meals);
		return (1);
	}
	return (0);
}
