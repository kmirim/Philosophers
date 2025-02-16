#include "philo.h"

//reescrever esas merda pq nao faz o menor sentido!!!!
static bool philo_died(t_philo *philo)
{
    long    duration;
    long    t_to_die;

    if (get_bool(&philo->philo_mtx, &philo->max_meals))
        return (false);

    duration = gettime(MILLISECOND) - get_long(&philo->philo_mtx, &philo->last_meal_time);
    t_to_die = philo->data->time_to_die / 1000;

    if (duration > t_to_die)
        return (true);
    return (false);
}

void    *monitor_dinner(void *info)
{
    printf("Thread de monitoramento iniciada\n"); //debug
    t_data *data;
    int     i;

    data = (t_data *)info;
    printf("Esperando todos os filósofos estarem prontos...\n");

    while (!all_threads_running(&data->table_mtx, &data->philos_ready, data->philo_nbr))
    {   
        //printf("Ainda esperando... philos_ready: %d, philo_nbr: %d\n", data->philos_ready, data->philo_nbr); // Mensagem de depuração
        continue ;
    }
    printf("Todos os filosofos estão prontos\n"); //debug    
    
    while (!sim_end(data))
    {
        printf("Looping principal do monitoramento\n"); //debug
        i = -1;
        while (++i < data->philo_nbr && !sim_end(data))
        {
            if (philo_died(data->philos + i))
            {
                t_philo *philo;
                //write_status(DEAD, data->philos + i);
                long time = gettime(MILLISECOND) - philo->data->init_s;
                if (!philo->max_meals)
                { 
                    pthread_mutex_lock(&philo->data->write_mtx);
                    if (!sim_end(philo->data)) 
                        printf(RED"%-6ld"RESET" %d died\n", time, philo->id_philo);
                    pthread_mutex_unlock(&philo->data->write_mtx);
                }
                set_bool(&data->table_mtx, &data->finish_s, true);
            }
        }
    }
    return (NULL);
}
