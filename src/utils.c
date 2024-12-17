#include "../inc/philo.h"

void    error_exit(const char *error)
{
    printf("%s", error);
    
    exit(1);
}

long    get_time_milli(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        error_exit("Error with gettimeofday\n");
    return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

long    get_time_micro(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        error_exit("Error with gettimeofday\n");
    return (tv.tv_sec * 1e6 + tv.tv_usec);
}