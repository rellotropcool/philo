/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aule-bre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:00:44 by aule-bre          #+#    #+#             */
/*   Updated: 2025/02/26 11:00:46 by aule-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	is_space(char c)
{
	return ((c >= '\t' && c <= '\n') || c == ' ');
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

char	*valid_input(char *str)
{
	int		len;
	char	*number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (printf("Negative numbers not allowed !\n"), NULL);
	number = str;
	if (!is_digit(*str))
		return (printf("Don't fool me this aint a number !\n"), NULL);
	while (is_digit(*str++))
		len++;
	if (len > 10)
		return (printf("Numbers above INT_MAX not allowed !\n"), NULL);
	return (number);
}

long	ft_atol(char *str)
{
	long	nb;

	nb = 0;
	if (!valid_input(str))
		return (-1);
	str = valid_input(str);
	while (is_digit(*str))
		nb = (nb * 10) + (*str++ - '0');
	if (nb > INT_MAX)
		return (printf("Numbers above INT_MAX not allowed !\n"), -1);
	return (nb);
}

bool	parse_input(t_table *table, char **av)
{
	if (ft_atol(av[1]) < 0 || ft_atol(av[2]) < 0 || ft_atol(av[3]) < 0
		|| ft_atol(av[4]) < 0)
		return (false);
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		return (printf("Timestamps must be above 60ms !"), false);
	if (av[5])
	{
		if (ft_atol(av[5]) < 0)
			return (false);
		table->number_limit_meals = ft_atol(av[5]);
	}
	else
		table->number_limit_meals = -1;
	return (true);
}
