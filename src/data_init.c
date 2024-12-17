#include "../inc/philo.h"

void    *safe_malloc(size_t bytes)
{
    void    *output;

    output = malloc(bytes);
    if (!output)
        error_exit("Malloc error !\n");
    return (output);
}

void    assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
    int philo_nbr;

    philo_nbr = philo->table->philo_nbr;
    if (philo->id % 2 == 0)
    {
        philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
        philo->first_fork = &forks[philo_position];
    }
    else
    {
        philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
        philo->second_fork = &forks[philo_position];
    }
}

void    philo_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = -1;
    while(++i < table->philo_nbr)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meal_counter = 0;
        philo->table = table;
        assign_forks(philo, table->forks, i);
    }
}

void    data_init(t_table *table)
{
    int i;

    i = -1;
    table->end_simulation = false;
    table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
    table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
    while (++i < table->philo_nbr)
    {
        pthread_mutex_init(&table->forks[i].fork, NULL);
        table->forks[i].fork_id = i;
    }
    philo_init(table);
}