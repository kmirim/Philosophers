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
//	data.start_time = gettime(MILLISECOND);
//	init_time();
	if (5 == count || 6 == count)
	{
		parse_input(&data, value);
		data_init(&data);
		dinner_start(&data);
	}
	else
	{
		error_exit("falta argumento ai !");
		// se entrou aqui eh porque a quantidade de argumentos esta errada.
		// inclusao de funcao para erro de entrada -> utils.c 
	}
	printf("chegou no fim da main!\n");
}
