/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarcelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 04:45:46 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/17 04:45:49 by lbarcelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->first_fork->fork_mtx);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork_mtx);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	time = gettime(MILLISECOND) - philo->data->init_s;
	if (!philo->max_meals)
	{
		pthread_mutex_lock(&philo->data->write_mtx);
		if (!sim_end(philo->data))
			printf(BLUE "%-6ld" " %d is eating\n" RESET,
				time, philo->id_philo);
		pthread_mutex_unlock(&philo->data->write_mtx);
	}
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->nbr_max_meals > 0
		&& philo->meals_counter == philo->data->nbr_max_meals)
		set_bool(&philo->philo_mtx, &philo->max_meals, true);
	pthread_mutex_unlock(&philo->second_fork->fork_mtx);
	pthread_mutex_unlock(&philo->first_fork->fork_mtx);
}

void	thinking(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;
	long	time;

	time = gettime(MILLISECOND) - philo->data->init_s;
	if (!philo->max_meals)
	{
		pthread_mutex_lock(&philo->data->write_mtx);
		if (!sim_end(philo->data))
			printf(MAG "%-6ld" " %d is thinking\n" RESET,
				time, philo->id_philo);
		pthread_mutex_unlock(&philo->data->write_mtx);
	}
	if (philo->data->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->data);
}

void	handle_sleeping(t_philo *philo)
{
	long	time;

	time = gettime(MILLISECOND) - philo->data->init_s;
	if (!philo->max_meals)
	{
		pthread_mutex_lock(&philo->data->write_mtx);
		if (!sim_end(philo->data))
			printf(CYAN "%-6ld" " %d is sleeping\n" RESET,
				time, philo->id_philo);
		pthread_mutex_unlock(&philo->data->write_mtx);
	}
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	desynch_philo(philo);
	while (!sim_end(philo->data))
	{
		pthread_mutex_lock(&philo->philo_mtx);
		if (philo->max_meals)
		{
			pthread_mutex_unlock(&philo->philo_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->philo_mtx);
		eat(philo);
		handle_sleeping(philo);
	}
	precise_usleep(philo->data->time_to_sleep, philo->data);
	thinking(philo);
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	data->init_s = gettime(MILLISECOND);
	pthread_create(&data->monitor_thread, NULL, monitor_dinner, (void *)data);
	if (data->nbr_max_meals == 0)
		return ;
	else if (data->philo_nbr == 1)
		pthread_create(&data->philos[0].thread_id, NULL, lone_philo,
			&data->philos[0]);
	else
	{
		while (data->philo_nbr > ++i)
		{
			pthread_create(&data->philos[i].thread_id, NULL, dinner_simulation,
				&data->philos[i]);
			add_long(&data->table_mtx, &data->philos_ready);
		}
	}
	set_bool(&data->table_mtx, &data->all_threads_ready, true);
	i = -1;
	while (data->philo_nbr > ++i)
		pthread_join(data->philos[i].thread_id, NULL);
	pthread_join(data->monitor_thread, NULL);
}
