#ifndef PHILOS_H
# define PHILOS_H

typedef struct t_philo
{
    int			id;         // philo's number [1, ..., n_philos]; 
    long long	time_left;   // time left since last meal (milliseconds);
    //double  time_eat;   // time it takes to eat;
    //double  time_sleep; // time will spend sleeping;
    //int     fork_own;       // innitially set to 1 (available);
    //int     fork_right;     // innitially set to 0 (unavailable);
    int     eating;     // if 1 -> is eating others states seted to zero;
    int     sleeping;   // if 1 -> is sleeping others states seted to zero;
    int     thinking;   // while not eating, they are thinking. if 1 -> is thinking others states seted to zero;
    int     n_eat;      // number of times they have eaten
    int     philo_dead; //if time_die == 0; philo_dead set to 1;
} t_philo;

typedef struct t_rules
{
	int		n_philos;
	int		time_left;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_meals;
	long	philo_id;

	long	*forks;
} t_rules;

void		ft_set_forks(long *forks, int philos);
void		ft_set_rules(char **argv, t_rules *rules, long *forks);
long long	ft_current_time_ms();
void		ft_create_philos(t_rules *rules);
void		ft_routine(t_rules *data);

#endif