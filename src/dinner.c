#include "../inc/philo.h"

static void thinking(t_philo *philo)
{
    write_status("is thinking", philo);
    usleep(1000);
}


static void eating(t_philo *philo)
{
    if (simulation_finished(philo->table))
        error_exit("PROBLEME DE FAIM");

    pthread_mutex_lock(&philo->first_fork->fork);
    write_status("has taken the first fork", philo);
    pthread_mutex_lock(&philo->second_fork->fork);
    write_status("has taken the second fork", philo);

    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_milli());
    philo->meal_counter++;

    write_status("is eating", philo);

    usleep(philo->table->time_to_eat);

    if (philo->table->number_limit_meals > 0 
        && philo->meal_counter == philo->table->number_limit_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
        
    pthread_mutex_unlock(&philo->first_fork->fork);
    pthread_mutex_unlock(&philo->second_fork->fork);
}

void    *dinner_simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->table);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_milli()); //a verifier
    increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
    if(philo->id % 2 == 0)
        usleep(1500);
    while (!simulation_finished(philo->table))
    {
        if (get_bool(&philo->philo_mutex, &philo->full))
            break;
        eating(philo);
     
        write_status("is sleeping", philo);
        usleep(philo->table->time_to_sleep);

        thinking(philo);
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
    pthread_create(&table->monitor, NULL, check_death, table);
    table->start_simulation = get_time_milli();
    set_bool(&table->table_mutex, &table->threads_ready, true);
    i = -1;
    while (++i < table->philo_nbr)
        pthread_join(table->philos[i].thread_id, NULL);
    pthread_join(table->monitor, NULL);
}