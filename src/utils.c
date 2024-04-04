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
				write(2, "Invalid args\n", 13);
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
		write(2, "Invalid args\n", 13);
		exit(1);
	}
	ft_check_numbers(argv);
}

int	ft_check_philo_dead(t_philo *philo, t_rules *rules)
{
	if (ft_current_time_ms(rules) >= philo->death_time)
	{
		if(!ft_check_end(rules))
		{
			ft_print_message("died", &rules->mutex_print, philo, rules);
			pthread_mutex_lock(&rules->mutex);
			rules->stop_demo = 1;
			pthread_mutex_unlock(&rules->mutex);
			return (1);
		}
	}
	return (0);
}

void	ft_get_forks(t_philo *philo, t_rules *rules)
{
	while (!philo->forks_own && !ft_check_end(rules) && !ft_check_philo_dead(philo, rules))
	{
		//if (philo->id % 2)			//avoid data race
		//	usleep();
		if (pthread_mutex_lock(&rules->mutex_forks[philo->fork_l_pos]) == 0 && rules->forks[philo->fork_l_pos])
		{
			rules->forks[philo->fork_l_pos] = 0;
			ft_print_message("has taken a fork", &rules->mutex_print, philo, rules);
			if (pthread_mutex_lock(&rules->mutex_forks[philo->fork_r_pos]) == 0 && rules->forks[philo->fork_r_pos])
			{
				rules->forks[philo->fork_r_pos] = 0;
				ft_print_message("has taken a fork", &rules->mutex_print, philo, rules);
				philo->forks_own = 1;
			}
			pthread_mutex_unlock(&rules->mutex_forks[philo->fork_r_pos]);
		}
		pthread_mutex_unlock(&rules->mutex_forks[philo->fork_l_pos]);
		/*
		pthread_mutex_lock(&rules->mutex_forks[philo->fork_l_pos]);
		if (rules->forks[philo->fork_l_pos])
		{
			rules->forks[philo->fork_l_pos] = 0;
			pthread_mutex_lock(&rules->mutex_print);
			if (!rules->stop_demo)
				printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
			pthread_mutex_unlock(&rules->mutex_print);
			pthread_mutex_unlock(&rules->mutex_forks[philo->fork_l_pos]);
			while (!philo->forks_own && !ft_check_end(rules) && !ft_check_philo_dead(philo, rules))
			{
				pthread_mutex_lock(&rules->mutex_forks[philo->fork_r_pos]);
				if (rules->forks[philo->fork_r_pos])
				{
					rules->forks[philo->fork_r_pos] = 0;
					pthread_mutex_lock(&rules->mutex_print);
					if (!rules->stop_demo)
						printf("%ld %d has taken a fork\n", ft_current_time_ms(rules), philo->id);
					pthread_mutex_unlock(&rules->mutex_print);
					pthread_mutex_unlock(&rules->mutex_forks[philo->fork_r_pos]);
					philo->forks_own = 1;
				}
				else
					pthread_mutex_unlock(&rules->mutex_forks[philo->fork_r_pos]);
			}
		}
		else
			pthread_mutex_unlock(&rules->mutex_forks[philo->fork_l_pos]);*/
	}
}

void		ft_check_meals(t_rules *rules)
{
	if (!rules || !rules->t_philos || ft_check_end(rules) || rules->no_count_meal)
		return ;
	int	i;
	int	j;

	i = rules->n_philos - 1;
	j = 0;
	while (i >= 0)
	{
		pthread_mutex_lock(&rules->mutex);
		if (rules->t_philos[i] && rules->t_philos[i]->n_meals >= rules->n_meals)
			j++;
		pthread_mutex_unlock(&rules->mutex);
		i--;
	}
	if (j == rules->n_philos)
	{
		if (!ft_check_end(rules))
		{
			pthread_mutex_lock(&rules->mutex);
			rules->stop_demo = 1;
			pthread_mutex_unlock(&rules->mutex);	
		}
	}
}