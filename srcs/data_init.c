/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aule-bre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:59:11 by aule-bre          #+#    #+#             */
/*   Updated: 2025/02/26 10:59:20 by aule-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*output;

	output = malloc(bytes);
	if (!output)
		return (printf("Malloc error !\n"), NULL);
	return (output);
}

void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

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

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meal_counter = 0;
		philo->table = table;
		pthread_mutex_init(&philo->philo_mutex, NULL);
		assign_forks(philo, table->forks, i);
	}
}

bool	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->threads_ready = false;
	table->threads_running_nbr = false;
	pthread_mutex_init(&table->table_mutex, NULL);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	if (!table->forks)
		return (false);
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
	{
		free(table->forks);
		return (false);
	}
	while (++i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	pthread_mutex_init(&table->write_mutex, NULL);
	return (true);
}
