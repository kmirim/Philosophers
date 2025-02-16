/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarcelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:18:46 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/12 17:10:40 by lbarcelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	ft_isdigit(char c)
{
	return (c >= 48 && c <= 57);
}

static inline bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*ret;

	len = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Feed me only positive valuse u suck!");
	if (!ft_isdigit(*str))
		error_exit("The input is not a correct digit!");
	ret = str;
	while (ft_isdigit(*str++))
		len++;
	if (len > 10)
		error_exit("The value is too big! Limit: nbr <= INT_MAX.");
	return (ret);
}

static long	ft_atol(const char *str)
{
	long	ret;

	ret = 0;
	str = valid_input(str);
	while (ft_isdigit(*str))
		ret = ret * 10 + (*str++ - 48);
	if (ret > INT_MAX)
		error_exit("The value is too big! Limit: nbr <= INT_MAX.");
	return (ret);
}

void	parse_input(t_data *data, char **value)
{
	data->philo_nbr = ft_atol(value[1]);
	data->time_to_die = ft_atol(value[2])*1000;
	data->time_to_eat = ft_atol(value[3]) * 1000;
	data->time_to_sleep = ft_atol(value[4]) * 1000;
	if (data->time_to_die < 60000
		|| data->time_to_eat < 60000
		|| data->time_to_sleep < 60000)
		error_exit("Use timestamps major than 60ms!");
	if(data->philo_nbr == 0 || data->time_to_die == -1000 || data->time_to_eat == -1000 || data->time_to_sleep == -1000)
		exit(1);
	if (data->philo_nbr == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0)
		exit(1);
	if (value[5])
		data->nbr_max_meals = ft_atol(value[5]);
	else
		data->nbr_max_meals = -1;
}
