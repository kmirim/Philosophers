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

/**
 * Define o valor de uma variável booleana de forma segura (thread-safe).
 * 
 * @param mtx    Ponteiro para o mutex que protege a variável.
 * @param target Ponteiro para a variável booleana que será modificada.
 * @param value  Valor booleano a ser atribuído à variável.
 */

void	set_bool(t_mtx *mtx, bool *target, bool value)
{
	safe_mtx(mtx, LOCK);
	*target = value;
	safe_mtx(mtx, UNLOCK);
}

/**
 * Obtém o valor de uma variável booleana de forma segura (thread-safe).
 * 
 * @param mtx   Ponteiro para o mutex que protege a variável.
 * @param value Ponteiro para a variável booleana que será lida.
 * @return      O valor atual da variável booleana.
 */

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	safe_mtx(mtx, LOCK);
	ret = *value;
	safe_mtx(mtx, UNLOCK);
	return (ret);
}

/**
 * Obtém o valor de uma variável longa de forma segura (thread-safe).
 * 
 * @param mtx   Ponteiro para o mutex que protege a variável.
 * @param value Ponteiro para a variável longa que será lida.
 * @return      O valor atual da variável longa.
 */

long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	safe_mtx(mtx, LOCK);
	ret = *value;
	safe_mtx(mtx, UNLOCK);
	return (ret);
}

/**
 * Define o valor de uma variável longa de forma segura (thread-safe).
 * 
 * @param mtx    Ponteiro para o mutex que protege a variável.
 * @param target Ponteiro para a variável longa que será modificada.
 * @param value  Valor longo a ser atribuído à variável.
 */

void	set_long(t_mtx *mtx, long *target, long value)
{
	safe_mtx(mtx, LOCK);
	*target = value;
	safe_mtx(mtx, UNLOCK);
}

/**
 * Verifica se a simulação do Jantar dos Filósofos foi finalizada.
 * 
 * @param data Ponteiro para a estrutura que contém os dados compartilhados da simulação.
 * @return     true se a simulação foi finalizada, false caso contrário.
 */

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
