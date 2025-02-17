#include "philo.h"

void	wait_all_threads(t_data *data)
{
	while(!get_bool(&data->table_mtx, &data->all_threads_ready))
		continue ;
	return ;		
}

bool    all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
    bool   threads_ready;
    
    threads_ready = false;
	pthread_mutex_lock(mtx);
    if (*threads == philo_nbr)
	{
        threads_ready = true;
	}
	pthread_mutex_unlock(mtx);
    return (threads_ready);
}
