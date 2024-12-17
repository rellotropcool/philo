#include "../inc/philo.h"

void    wait_all_threads(t_table *table)
{
    while(!get_bool(&table->table_mutex, &table->threads_ready))
        ;
}