/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aule-bre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:59:31 by aule-bre          #+#    #+#             */
/*   Updated: 2025/02/26 10:59:33 by aule-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	thinking(t_philo *philo)
{
	write_status("is thinking", philo);
	usleep(1000);
}

static bool	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status("has taken a fork", philo);
	if (simulation_finished(philo->table) || philo->table->philo_nbr == 1)
	{
		ft_usleep(philo->table->time_to_die + 100);
		return (false);
	}
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status("has taken a fork", philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_milli());
	philo->meal_counter++;
	write_status("is eating", philo);
	usleep(philo->table->time_to_eat);
	if (philo->table->number_limit_meals > 0
		&& philo->meal_counter == philo->table->number_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->second_fork->fork);
	pthread_mutex_unlock(&philo->first_fork->fork);
	return (true);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_milli());
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	if (philo->id % 2 == 0)
		usleep(1500);
	while (!simulation_finished(philo->table))
	{
		if (simulation_finished(philo->table) || get_bool(&philo->philo_mutex,
				&philo->full))
			break ;
		if (simulation_finished(philo->table) || !eating(philo))
			break ;
		write_status("is sleeping", philo);
		usleep(philo->table->time_to_sleep);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->number_limit_meals == 0)
		return ;
	else
	{
		while (++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, NULL, dinner_simulation,
				&table->philos[i]);
	}
	pthread_create(&table->monitor, NULL, check_death, table);
	table->start_simulation = get_time_milli();
	set_bool(&table->table_mutex, &table->threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	pthread_join(table->monitor, NULL);
}
