#ifndef PHILOS_H
# define PHILOS_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct t_philo
{
    int			id;         // philo's number [1, ..., n_philos]; 
    time_t	death_time;   // time(ms) philo die if not eat;
    int     forks_own;
    int     eating;     // if 1 -> is eating others states seted to zero;
    int     sleeping;   // if 1 -> is sleeping others states seted to zero;
    int     thinking;   // while not eating, they are thinking. if 1 -> is thinking others states seted to zero;
    int     n_meals;      // number of times they have eaten
    int     philo_dead; //if time_die == 0; philo_dead set to 1;
} t_philo;

typedef struct t_rules
{
	int		        n_philos;
	time_t          death_time;
	time_t		    time_to_eat;
	time_t		    time_to_sleep;
	time_t		    n_meals;
	long            philo_id;
	long            *forks;
    pthread_t	    **philos;
    pthread_mutex_t *mutex;
} t_rules;

void		ft_set_forks(long *forks, int pos);
void		ft_set_rules(char **argv, t_rules *rules);
time_t      ft_current_time_ms();
void		ft_create_philos(t_rules *rules);
void		*ft_routine(t_rules *data);
void	    ft_philo_think(t_philo *philo);
void        ft_get_forks(t_philo *philo, t_rules *rules);
int         ft_get_bit(long number, int pos);
void        ft_clear_bit(long *num, int pos);
void	    ft_eat(t_rules *rules, t_philo * philo);
void	    *ft_routine(t_rules *data);
void        ft_open_bit(long *num, int pos);
void	    ft_parse_args(int argc, char **argv);

#endif