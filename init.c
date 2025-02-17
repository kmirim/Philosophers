/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarcelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 04:46:09 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/17 04:46:12 by lbarcelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
	philo->second_fork = &forks[philo_pos];
	if (philo->id_philo % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (data->philo_nbr > ++i)
	{
		philo = data->philos + i;
		philo->id_philo = i + 1;
		philo->max_meals = false;
		philo->meals_counter = 0;
		philo->data = data;
		philo->last_meal_time = gettime(MILLISECOND);
		pthread_mutex_init(&philo->philo_mtx, NULL);
		assign_forks(philo, data->forks, i);
	}
}

void	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->finish_s = false;
	data->all_threads_ready = false;
	data->philos_ready = 0;
	data->philos = safe_malloc(sizeof(t_philo) * data->philo_nbr);
	pthread_mutex_init(&data->table_mtx, NULL);
	pthread_mutex_init(&data->write_mtx, NULL);
	data->forks = safe_malloc(sizeof(t_fork) * data->philo_nbr);
	while (++i < data->philo_nbr)
	{
		pthread_mutex_init(&data->forks[i].fork_mtx, NULL);
		data->forks[i].fork_id = i;
	}
	philo_init(data);
}
