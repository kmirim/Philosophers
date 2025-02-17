/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarcelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 04:46:37 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/17 04:46:39 by lbarcelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->table_mtx, &data->all_threads_ready))
		continue ;
	return ;
}

bool	all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
	bool	threads_ready;

	threads_ready = false;
	pthread_mutex_lock(mtx);
	if (*threads == philo_nbr)
	{
		threads_ready = true;
	}
	pthread_mutex_unlock(mtx);
	return (threads_ready);
}

void	add_long(t_mtx *mtx, long *var)
{
	pthread_mutex_lock(mtx);
	*var += 1;
	pthread_mutex_unlock(mtx);
}

void	*lone_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECOND));
	get_long(&philo->data->table_mtx, &philo->data->philos_ready);
	write_status(TAKE_FIRST_FORK, philo);
	while (!sim_end(philo->data))
		usleep(200);
	return (NULL);
}
