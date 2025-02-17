/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarcelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:18:31 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/12 18:18:32 by lbarcelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int count, char **value)
{
	t_data data;
	if (5 == count || 6 == count)
	{
		parse_input(&data, value);
		data_init(&data);
		dinner_start(&data);
		cleaning_table(&data);
	}
	else
		error_exit("Usage: ./philo number_of_philosophers time_to_die time to \
				eat time to sleep [number_of_meals]");
	return (0);
}
