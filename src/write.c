#include "../inc/philo.h"

void    write_status(char *str, t_philo *philo)
{
    long elapsed;

    if (get_bool(&philo->philo_mutex, &philo->full))
        return;
    elapsed = get_time_milli();
    pthread_mutex_lock(&philo->table->write_mutex);
    {
        if (!simulation_finished(philo->table))
            printf("%ld %d %s\n", elapsed, philo->id, str);
    }
    pthread_mutex_unlock(&philo->table->write_mutex); 
}