#include "../inc/philo.h"

void    set_bool(t_mtx *mutex, bool *dest, bool value)
{
    pthread_mutex_lock(mutex);
    *dest = value;
    pthread_mutex_unlock(mutex);
}

bool    get_bool(t_mtx *mutex, bool *value)
{
    bool    ret;

    pthread_mutex_lock(mutex);
    ret = *value;
    pthread_mutex_unlock(mutex);
    return(ret);
}

void    set_long(t_mtx *mutex, long *dest, long value)
{
    pthread_mutex_lock(mutex);
    *dest = value;
    pthread_mutex_unlock(mutex);
}

long    get_long(t_mtx *mutex, long *value)
{
    long    ret;
    
    pthread_mutex_lock(mutex);
    ret = *value;
    pthread_mutex_unlock(mutex);
    return(ret);
}

bool    simulation_finished(t_table *table)
{
    return(get_bool(&table->table_mutex, &table->end_simulation));
}