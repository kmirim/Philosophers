/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarcelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:19:03 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/17 04:14:28 by lbarcelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error)
{
	printf(RED "⛔️ %s ⛔️\n" RESET, error);
	exit(EXIT_FAILURE);
}

void	desynch_philo(t_philo *philo)
{
	if (philo->data->philo_nbr % 2 == 0)
	{
		if (philo->id_philo % 2 == 0)
			precise_usleep(30000, philo->data);
	}
	else
	{
		if (philo->id_philo % 2 != 0)
			thinking(philo);
	}
}

long	gettime(t_time_code time_code)
{
	struct timeval	tv;
	static long		start_time = 0;
	long			current_time;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed!");
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (start_time == 0)
		start_time = current_time;
	if (time_code == SECOND)
		return ((current_time - start_time) / 1000);
	else if (time_code == MILLISECOND)
		return (current_time - start_time);
	else if (time_code == MICROSECOND)
		return ((current_time - start_time) * 1000);
	else
		error_exit("Wrong input to gettime!");
	return (42);
}

void	precise_usleep(long usec, t_data *data)
{
	long	start_time;
	long	passed;
	long	remaining;

	start_time = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start_time < usec)
	{
		if (sim_end(data))
			break ;
		passed = gettime(MICROSECOND) - start_time;
		remaining = usec - passed;
		if (remaining > 1000)
			usleep(remaining / 2);
		else
		{
			while (gettime(MICROSECOND) - start_time < usec)
				continue ;
		}
	}
}

void	cleaning_table(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philos + i;
		pthread_mutex_destroy(&philo->philo_mtx);
	}
	pthread_mutex_destroy(&data->write_mtx);
	pthread_mutex_destroy(&data->table_mtx);
	free(data->philos);
	free(data->forks);
}
