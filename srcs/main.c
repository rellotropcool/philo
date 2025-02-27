/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aule-bre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:59:55 by aule-bre          #+#    #+#             */
/*   Updated: 2025/02/26 10:59:58 by aule-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (!parse_input(&table, av))
			return (1);
		if (!data_init(&table))
			return (1);
		dinner_start(&table);
		error_exit("", &table);
	}
	else
	{
		printf("Wrong number of inputs !\n");
		return (1);
	}
	return (0);
}
