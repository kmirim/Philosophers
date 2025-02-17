/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:16:54 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/14 02:28:22 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mtx, bool *target, bool value)
{
	safe_mtx(mtx, LOCK);
	*target = value;
	safe_mtx(mtx, UNLOCK);
}

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	safe_mtx(mtx, LOCK);
	ret = *value;
	safe_mtx(mtx, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	safe_mtx(mtx, LOCK);
	ret = *value;
	safe_mtx(mtx, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mtx, long *target, long value)
{
	safe_mtx(mtx, LOCK);
	*target = value;
	safe_mtx(mtx, UNLOCK);
}

bool	sim_end(t_data *data)
{
	return (get_bool(&data->table_mtx, &data->finish_s));
}

void add_long(t_mtx *mtx, long *var)
{
    pthread_mutex_lock(mtx);
    *var += 1;
    pthread_mutex_unlock(mtx);
}
