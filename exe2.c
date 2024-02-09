#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/*                  ***RULES***
* n_forks = n_philos;
* eat->sleep->think (repeat);
* each philo use 2 forks (left and right);
*
* Your(s) program(s) should take the following arguments:
* number_of_philosophers time_to_die time_to_eat time_to_sleep
* [number_of_times_each_philosopher_must_eat]
*
* About the logs of your program:
*  .Any state change of a philosopher must be formatted as follows:
*  .timestamp_in_ms X has taken a fork
*  .timestamp_in_ms X is eating
*  .timestamp_in_ms X is sleeping
*  .timestamp_in_ms X is thinking
*  .timestamp_in_ms X died
*/

typedef struct t_philo
{
    int     id;         // philo's number [1, ..., n_philos]; 
    long long  time_die;   // time left since last meal (milliseconds);
    //double  time_eat;   // time it takes to eat;
    //double  time_sleep; // time will spend sleeping;

    //int     fork_own;       // innitially set to 1 (available);
    //int     fork_right;     // innitially set to 0 (unavailable);

    int     eating;     // if 1 -> is eating others states seted to zero;
    int     sleeping;   // if 1 -> is sleeping others states seted to zero;
    int     thinking;   // while not eating, they are thinking. if 1 -> is thinking others states seted to zero;
    int     n_eat;      // number of times they have eaten

    int     philo_dead; //if time_die == 0; philo_dead set to 1;

    struct t_philo *right;

} t_philo;

typedef struct t_rules
{
	int		n_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_meals;
} t_rules;

void	set_rules(char **argv, t_rules *rules)
{
	rules->n_philos = atoi(argv[1]);
	rules->time_to_die = atoi(argv[2]);
	rules->time_to_eat = atoi(argv[3]);
	rules->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		rules->n_meals = atoi(argv[5]);
}

void	print_rules(t_rules rules)
{
	printf("n_philos: %d\ntime_die: %d\ntime_eat: %d\ntime_sleep: %d\nn_meals: %d\n", rules.n_philos, rules.time_to_die, rules.time_to_eat, rules.time_to_sleep, rules.n_meals);
}

long long current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long) tv.tv_sec * 1000 + (long long) tv.tv_usec / 1000;
}

int main(int argc, char **argv)
{
    t_rules	rules;
	t_philo philo;

	memset(&rules, 0, sizeof(rules));
	memset(&philo, 0, sizeof(t_philo));
	set_rules(argv, &rules);

	long long time = current_time_ms();

	philo.time_die = time + 5000;
	while (current_time_ms() < philo.time_die)
	{
		printf("philo alive at: %lld\n", current_time_ms());
	}
	printf("\nphilo died :(\n");
	


    return 0;
}