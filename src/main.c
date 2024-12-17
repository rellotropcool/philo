#include "../inc/philo.h"

int main(int ac, char **av)
{
    t_table table;

    if (ac == 5 || ac == 6)
    {
        parse_input(&table, av);
        data_init(&table);
        dinner_start(&table);/*TODO*/
        clean_table(&table);/*TODO (philos full || one philo died)*/
    }
    else 
        error_exit("Wrong number of inputs !\n");
}