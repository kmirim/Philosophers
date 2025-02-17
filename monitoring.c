#include "philo.h"

static bool philo_died(t_philo *philo)
{
    long    duration;
    long    t_to_die;

    if (get_bool(&philo->philo_mtx, &philo->max_meals))
        return (false);

    duration = gettime(MILLISECOND) - get_long(&philo->philo_mtx, &philo->last_meal_time);
    t_to_die = philo->data->time_to_die / 1000;

    if (duration >= t_to_die)
        return (true);
    return (false);
}

void    *monitor_dinner(void *info)
{
    t_data *data;
    int     i;
    int     max_eat = 0;

    data = (t_data *)info;

    while (!all_threads_running(&data->table_mtx, &data->philos_ready, data->philo_nbr))
        continue ;    
    while (!sim_end(data))
    {
        i = -1;
        while (++i < data->philo_nbr && !sim_end(data))
        {
            if (philo_died(data->philos + i))
            {
                t_philo *philo;
		        philo = data->philos + i;
                long time = gettime(MILLISECOND) - philo->data->init_s;
                pthread_mutex_lock(&philo->data->write_mtx);
                if (!sim_end(philo->data)) 
                    printf(RED"%-6ld"RESET" %d died\n", time, philo->id_philo);
                pthread_mutex_unlock(&philo->data->write_mtx);
                set_bool(&data->table_mtx, &data->finish_s, true);
            }
            else if (data->philos[i].max_meals)
            {
                max_eat++;
                if (max_eat == data->philo_nbr)
                {
                    set_bool(&data->table_mtx, &data->finish_s, true);
                    break ;
                }
            }
        }
        if (data->philos[i].max_meals)
            break;
    }
    return (NULL);
}
