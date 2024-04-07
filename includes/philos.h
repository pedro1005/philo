/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedmonte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:15:28 by pedmonte          #+#    #+#             */
/*   Updated: 2024/04/07 18:15:40 by pedmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct t_philo
{
	int		id;
	time_t	death_time;
	int		forks_own;
	long	n_meals;
	int		fork_l_pos;
	int		fork_r_pos;
}	t_philo;

typedef struct t_rules
{
	int				n_philos;
	int				no_count_meal;
	int				stop_demo;
	time_t			death_time;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_init;
	long			n_meals;
	int				philo_created;
	pthread_t		**philos;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	mutex_meals;
	t_philo			**t_philos;
}	t_rules;

void		ft_set_rules(char **argv, t_rules *rules);
time_t		ft_current_time_ms(t_rules *rules);
void		ft_create_philos(t_rules *rules);
void		*ft_routine(t_rules *data);
void		ft_philo_think(t_philo *philo, t_rules *rules);
void		ft_get_forks(t_philo *philo, t_rules *rules);
void		ft_eat(t_rules *rules, t_philo *philo);
void		ft_parse_args(int argc, char **argv);
void		ft_check_numbers(char **argv);
void		ft_philo_sleep(t_philo *philo, t_rules *rules);
void		ft_check_meals(t_rules *rules, t_philo *philo);
int			ft_check_end(t_rules *rules);
int			ft_check_philo_dead(t_philo *philo, t_rules *rules);
void		ft_print_message(char *str, t_philo *philo, t_rules *rules);
void		ft_init_philo(t_philo *philo, t_rules *data);
void		ft_init_mutaxes(t_rules *rules);
long long	ft_long_atoi(const char *nptr);

#endif
