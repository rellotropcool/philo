#include "../inc/philo.h"

void    error_exit(const char *error, t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_nbr)
        pthread_mutex_destroy(&table->philos[i].philo_mutex);
    pthread_mutex_destroy(&table->table_mutex);
    pthread_mutex_destroy(&table->write_mutex);
    free(table->forks);
    free(table->philos);
    printf("%s", error);
    exit(1);
}

long    get_time_milli(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        return(0);
    return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}