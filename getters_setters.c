/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarcelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 04:46:01 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/17 04:46:04 by lbarcelo         ###   ########.fr       */
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
