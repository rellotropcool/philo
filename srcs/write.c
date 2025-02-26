/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aule-bre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:01:19 by aule-bre          #+#    #+#             */
/*   Updated: 2025/02/26 11:01:21 by aule-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	write_status(char *str, t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	elapsed = get_time_milli() - philo->table->start_simulation;
	pthread_mutex_lock(&philo->table->write_mutex);
	{
		if (!simulation_finished(philo->table))
			printf("%ld %d %s\n", elapsed, philo->id, str);
	}
	pthread_mutex_unlock(&philo->table->write_mutex);
}
