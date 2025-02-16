/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:17:47 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/15 22:15:18 by lbarcelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** 1. Maximo de refeições não pode ser zero. ✅
** Criar função! ⭕
** 2. Nº de filosofos é 1. ✅
** 3. Criar threads de todos os philos. ✅
** 4. Criar monitor das threads.
** 5. Sincronizar o inicio da simulação.
*/

/*TESTAR O PRINT DO TEMPO TO DESESPERADO*/

/*

size_t	current_ms(void)
{
	struct timeval	time;

	if(gettimeofday(&time, NULL) ==  -1)
		write(2, "gettimeofday() error\n", 22);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}


int	ft_usleep(size_t milliseconds)
{
	size_t	start;
	
	start = current_ms();
	while ((current_ms() - start < milliseconds)
			usleep(50));
	return (0);
}
*/

static void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork_mtx);
	//write_status(TAKE_FIRST_FORK, philo);
	//printf("Philo %d picked up first fork\n", philo->id_philo); // Log de depuração
	
	/*colocando write no scopo para verificar*/
	long time = gettime(MILLISECOND) - philo->data->init_s; 
	
	if (!philo->max_meals) {
		pthread_mutex_lock(&philo->data->write_mtx);
		if (!sim_end(philo->data)) {
			printf("%-6ld"" %d has taken a fork\n", time, philo->id_philo);
		}
		pthread_mutex_unlock(&philo->data->write_mtx);
	}

	pthread_mutex_lock(&philo->second_fork->fork_mtx);
	//write_status(TAKE_SECOND_FORK, philo);
	//printf("Philo %d picked up second fork\n", philo->id_philo); // Log de depuração
	
	/*colocando write no scopo para verificar*/

	time = gettime(MILLISECOND) - philo->data->init_s; //!!!!verificar
	if (!philo->max_meals) 
	{
    	pthread_mutex_lock(&philo->data->write_mtx);
    	if (!sim_end(philo->data)) 
		{
        	printf("%-6ld"" %d has taken a fork\n", time, philo->id_philo);
    	}
    	pthread_mutex_unlock(&philo->data->write_mtx);
	}

	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECOND)); //modifica(mtx do philo para não ser acessado, ultimo momento que foi feita refeição, tempo atual);
	philo->meals_counter++; //incrementa a quantidade de refeições feitas pelo filosofo;
	//write_status(EATING,philo);
	//printf("Philo %d is eating\n", philo->id_philo); // Log de depuração
	time = gettime(MILLISECOND) - philo->data->init_s;
	if (!philo->max_meals) 
	{
		pthread_mutex_lock(&philo->data->write_mtx);
		if (!sim_end(philo->data)) 
		{
			printf(BLUE"%-6ld"" %d is eating\n"RESET, time, philo->id_philo);
		}
		pthread_mutex_unlock(&philo->data->write_mtx);
	}	
	precise_usleep(philo->data->time_to_eat, philo->data);
	
	if (philo->data->nbr_max_meals > 0 
		&& philo->meals_counter == philo->data->nbr_max_meals)
		set_bool(&philo->philo_mtx, &philo->max_meals, true); // Verifica se a refeição atual é igual ao número máximo de refeições.	
	
	pthread_mutex_unlock(&philo->second_fork->fork_mtx);
	pthread_mutex_unlock(&philo->first_fork->fork_mtx);
	//printf("Philo %d released forks\n", philo->id_philo); // Log de depuração
}

void thinking(t_philo *philo)
{
	long    t_eat;
    long    t_sleep;
    long    t_think;

    //write_status(THINKING, philo);
	long time = gettime(MILLISECOND) - philo->data->init_s;
	if (!philo->max_meals) {
		pthread_mutex_lock(&philo->data->write_mtx);
		if (!sim_end(philo->data)) {
			printf(MAG"%-6ld"" %d is thinking\n"RESET, time, philo->id_philo);
		}
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

void    *lone_philo(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    wait_all_threads(philo->data);

    set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILLISECOND));

    get_long(&philo->data->table_mtx, &philo->data->philos_ready);

    write_status(TAKE_FIRST_FORK, philo);
    
    while (!sim_end(philo->data))
        usleep(200);

    return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data; // casting para ter acesso a struct do filosofo 
	wait_all_threads(philo->data); // fazer ainda⭕

	desynch_philo(philo);

	while(!sim_end(philo->data))
	{
	// 1.verificar se filosofo comeu o max de refeições
		if (philo->max_meals)
			break ;
	// 2.comer
		eat(philo);
	// 3.dormir
		//write_status(SLEEPING, philo);
		long time = gettime(MILLISECOND) - philo->data->init_s;
		if (!philo->max_meals) {
			pthread_mutex_lock(&philo->data->write_mtx);
			if (!sim_end(philo->data)) {
				printf(CYAN"%-6ld"" %d is sleeping\n"RESET, time, philo->id_philo);
			}
			pthread_mutex_unlock(&philo->data->write_mtx);
		}	
		precise_usleep(philo->data->time_to_sleep, philo->data);	
	// 4.pensar
		thinking(philo);
	}	
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	data->init_s = gettime(MILLISECOND);
	printf("data->init_s : %i\n", data->init_s);
	pthread_create(&data->monitor_thread, NULL, monitor_dinner, (void *)data);
	if (data->nbr_max_meals == 0)
		return ;
	else if (data->philo_nbr == 1)
		pthread_create(&data->philos[0].thread_id, NULL, lone_philo, &data->philos[0]);
	else
	{
		while (data->philo_nbr > ++i)
			pthread_create(&data->philos[i].thread_id, NULL, dinner_simulation, &data->philos[i]);
	}
	

	set_bool(&data->table_mtx, &data->all_threads_ready, true);

	i = -1;
	while (data->philo_nbr > ++i)
		pthread_join(data->philos[i].thread_id, NULL);
	pthread_join(data->monitor_thread, NULL);
	pthread_mutex_lock(&data->write_mtx);
	data->finish_s = true;
	pthread_mutex_unlock(&data->write_mtx);
}
