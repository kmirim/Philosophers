/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarcelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:18:56 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/13 01:48:02 by lbarcelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//----------MALLOC-------------//
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("Error with the malloc!");
	return (ret);
}

//----------------MUTEX---------------//

//***ERROR***//
/*incluir static depois do teste*/
void	mtx_error(int status)
{
	if (status == 0)
		return ;
	else
		error_exit("erro mtx");
}
//**MUTEX**//
void	safe_mtx(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
	{
		mtx_error(pthread_mutex_lock(mutex));
	}
	else if (opcode == UNLOCK)
		mtx_error(pthread_mutex_unlock(mutex));
	else if (opcode == INIT)
		mtx_error(pthread_mutex_init(mutex, NULL));
	else if (opcode == DESTROY)
		mtx_error(pthread_mutex_destroy(mutex));
	else
		error_exit("Wrong opcode for mutex handle!");
}

//----------------THREAD---------------//

//***ERROR***//
void	thread_error(int status)
{
	if (status == 0)
		return ;
	else
		error_exit("erro thread!");
}
//**THREAD**//
void	safe_pthread(pthread_t *thread, void *(*foo)(void *),
	void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		thread_error(pthread_create(thread, NULL, foo, data));
	else if (opcode == JOIN)
		thread_error(pthread_join(*thread, NULL));
	else if (opcode == DETACH)
		thread_error(pthread_detach(*thread));
	else
		error_exit("mensagem de error pq alguma porra de deu merda.");
}
