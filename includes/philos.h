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
    int		id;         // philo's number [1, ..., n_philos]; 
    time_t	death_time;   // time(ms) philo die if not eat;
    int     forks_own;
    int     eating;     // if 1 -> is eating others states seted to zero;
    int     sleeping;   // if 1 -> is sleeping others states seted to zero;
    int     thinking;   // while not eating, they are thinking. if 1 -> is thinking others states seted to zero;
    long    n_meals;      // number of times they have eaten
    int     philo_dead; //if time_die == 0; philo_dead set to 1;
    int     fork_l_pos;
    int     fork_r_pos;
} t_philo;
typedef struct t_rules
{
	int             n_philos;
    int             philo_dead;
    int             philos_eaten;
    int             stop_demo;
	time_t          death_time;
	time_t		    time_to_eat;
	time_t		    time_to_sleep;
    time_t          time_init;
	long		    n_meals;
	int             philo_created;
	int             *forks;
    pthread_t	    **philos;
    pthread_mutex_t mutex;
    pthread_mutex_t mutex_print;
    pthread_mutex_t *mutex_forks;
    pthread_mutex_t mutex_dead;
    t_philo         **t_philos;
} t_rules;
void        ft_init_forks(int *forks, long n_philos);
void		ft_set_rules(char **argv, t_rules *rules);
time_t      ft_current_time_ms(t_rules *rules);
void		ft_create_philos(t_rules *rules);
void		*ft_routine(t_rules *data);
void	    ft_philo_think(t_philo *philo, t_rules *rules);
void        ft_get_forks(t_philo *philo, t_rules *rules);
int         ft_get_bit(long number, int pos);
void	    ft_eat(t_rules *rules, t_philo * philo);
void	    ft_parse_args(int argc, char **argv);
void	    ft_check_numbers(char **argv);
int         ft_check_fork(int *number, int pos);
void        ft_set_fork(int *forks,int pos, int state);
void	    ft_philo_sleep(t_philo *philo, t_rules *rules);
int		    ft_check_meals(t_rules *rules);
int         ft_check_end(t_rules *rules);
int	        ft_check_philo_dead(t_philo *philo, t_rules *rules);
#endif