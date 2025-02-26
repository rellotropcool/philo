/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aule-bre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:18:47 by aule-bre          #+#    #+#             */
/*   Updated: 2025/02/26 16:18:51 by aule-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
INCLUDES -----------------------------------------------------------
*/

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*
STRUCTURES ---------------------------------------------------------
*/

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

/*FORKS*/

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

/*PHILOSOPHERS*/

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	t_fork				*first_fork;
	t_fork				*second_fork;
	long				meal_counter;
	long				last_meal_time;
	bool				full;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

/*TABLE OF PHILOSOPHERS*/

struct					s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_limit_meals;
	long				start_simulation;
	bool				end_simulation;
	bool				threads_ready;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	t_fork				*forks;
	t_philo				*philos;
};

/*
PROTOTYPES ---------------------------------------------------------
*/

void					data_init(t_table *table);
void					dinner_start(t_table *table);

/*
UTILS
*/

void					error_exit(const char *error, t_table *table);

bool					get_bool(t_mtx *mutex, bool *value);
long					get_long(t_mtx *mutex, long *value);
void					set_bool(t_mtx *mutex, bool *dest, bool value);
void					set_long(t_mtx *mutex, long *dest, long value);
bool					simulation_finished(t_table *table);

void					wait_all_threads(t_table *table);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
void					increase_long(t_mtx *mutex, long *value);

void					*check_death(void *data);

long					get_time_milli(void);
void					ft_usleep(long int time_in_ms);

void					write_status(char *str, t_philo *philo);

/*
PARSING
*/

void					parse_input(t_table *table, char **av);

#endif
