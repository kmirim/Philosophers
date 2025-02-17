/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarcelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 04:46:17 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/17 04:46:19 by lbarcelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	duration;
	long	t_to_die;

	if (get_bool(&philo->philo_mtx, &philo->max_meals))
		return (false);
	duration = gettime(MILLISECOND) - get_long(&philo->philo_mtx,
			&philo->last_meal_time);
	t_to_die = philo->data->time_to_die / 1000;
	if (duration >= t_to_die)
		return (true);
	return (false);
}

void	handle_philo_death(t_philo *philo, t_data *data)
{
	long	time;

	time = gettime(MILLISECOND) - philo->data->init_s;
	pthread_mutex_lock(&philo->data->write_mtx);
	if (!sim_end(philo->data))
		printf("%-6ld %d died\n", time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->write_mtx);
	set_bool(&data->table_mtx, &data->finish_s, true);
}

void	check_max_meals(t_data *data, int *max_eat)
{
	if (data->philos[*max_eat].max_meals)
	{
		(*max_eat)++;
		if (*max_eat == data->philo_nbr)
			set_bool(&data->table_mtx, &data->finish_s, true);
	}
}

void	*monitor_dinner(void *info)
{
	t_data		*data;
	int			i;
	int			max_eat;

	max_eat = 0;
	data = (t_data *)info;
	while (!all_threads_running(&data->table_mtx, &data->philos_ready,
			data->philo_nbr))
		continue ;
	while (!sim_end(data))
	{
		i = -1;
		while (++i < data->philo_nbr && !sim_end(data))
		{
			if (philo_died(data->philos + i))
				handle_philo_death(data->philos + i, data);
			else
				check_max_meals(data, &max_eat);
		}
	}
	return (NULL);
}
