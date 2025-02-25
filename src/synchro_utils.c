#include "../inc/philo.h"

void    wait_all_threads(t_table *table)
{
    while(!get_bool(&table->table_mutex, &table->threads_ready))
        ;
}

bool    all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool    ret;

    ret = false;
    pthread_mutex_lock(mutex);
    if (*threads == philo_nbr)
        ret = true;
    pthread_mutex_unlock(mutex);
    return(ret);
}

void    increase_long(t_mtx *mutex, long *value)
{
    pthread_mutex_lock(mutex);
    (*value)++;
    pthread_mutex_unlock(mutex);
}