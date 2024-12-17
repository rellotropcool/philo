#include "../inc/philo.h"

static void eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->first_fork->fork);
    write_status("has taken the first fork", philo);
    pthread_mutex_lock(&philo->second_fork->fork);
    write_status("has taken the second fork", philo);

}

void    *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->table);
    while (!simulation_finished(philo->table))
    {
        if (get_bool(&philo->philo_mutex, &philo->full))
            break;
        eating(philo);//TODO
        sleeping(philo);//TODO
        thinking(philo);//TODO
    }
    return (NULL);
}

void    dinner_start(t_table *table)
{
    int i;

    i = -1;
    if (table->number_limit_meals == 0)
        return;
    else if (table->philo_nbr == 1)
        ; // TODO
    else
    {
        while (++i < table->philo_nbr)
            pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation, &table->philos[i]);
    }
    set_bool(&table->table_mutex, &table->threads_ready, true);
}