/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aule-bre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:01:08 by aule-bre          #+#    #+#             */
/*   Updated: 2025/02/26 11:01:09 by aule-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error_exit(const char *error, t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	free(table->forks);
	free(table->philos);
	printf("%s", error);
	return ;
}

long	get_time_milli(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

void	ft_usleep(long int time_in_ms)
{
	long	start_time;

	start_time = 0;
	start_time = get_time_milli();
	while ((get_time_milli() - start_time) < time_in_ms / 1e3)
		usleep(time_in_ms / 10);
}
