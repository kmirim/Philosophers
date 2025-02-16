#include "philo.h"

//Aguarda a sincronizacao das threads. vamos verificar se todas estao ok.
void	wait_all_threads(t_data *data)
{
	while(!get_bool(&data->table_mtx, &data->all_threads_ready))
	{
		continue ;
	}
	return ;		
}

bool    all_threads_running(t_mtx *mtx, long *threads, long philo_nbr)
{
    bool   threads_ready;
    
    threads_ready = false;
	pthread_mutex_lock(mtx);
	//printf("Verificando threads: threads = %ld, philo_nbr = %ld\n", *threads, philo_nbr); // Mensagem de depuração
    if (*threads == philo_nbr)
        threads_ready = true;
	pthread_mutex_unlock(mtx);

    return (threads_ready);
}


