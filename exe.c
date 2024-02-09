#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

#define NTHREADS 10

pthread_mutex_t counter_mutex;

typedef struct t_philo
{
    int     id;         // philo's number [1, ..., n_philos]; 
    double  time_die;   // time left since last meal (milliseconds);
    double  time_eat;   // time it takes to eat;
    double  time_sleep; // time will spend sleeping;

    int     fork_own;       // innitially set to 1 (available);
    int     fork_right;     // innitially set to 0 (unavailable);

    int     eating;     // if 1 -> is eating others states seted to zero;
    int     sleeping;   // if 1 -> is sleeping others states seted to zero;
    int     thinking;   // while not eating, they are thinking. if 1 -> is thinking others states seted to zero;
    int     n_eat;      // number of times they have eaten

    int     philo_dead; //if time_die == 0; philo_dead set to 1;

    struct t_philo *right;

} t_philo;


// Function executed by each thread
void *func1(int data)
{
    int x = data;

    printf("%d is thinking...\n", x);

    pthread_mutex_lock(&counter_mutex);
    printf("%d is eating...\n", x);
    pthread_mutex_unlock(&counter_mutex);

    printf("%d is sleeping...\n", x);

    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t thread_id[argc];
    char **names;

    names = argv;

    // Create threads
    for (int i = 1; i < argc; i++)
    {
        // Create thread and pass the address of names[i] as argument
        if (pthread_create(&thread_id[i], NULL, func1, thread_id[i]) != 0)
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int j = 1; j < argc; j++)
    {
        if (pthread_join(thread_id[j], NULL) != 0)
        {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // Return 0 to indicate successful completion
    return 0;
}
