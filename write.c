#include "philo.h"
void	write_status(t_philo_status st, t_philo *philo)
{
	long	time;

	time = gettime(MILLISECOND) - philo->data->init_s;
	if(philo->max_meals)
		return ;
	pthread_mutex_lock(&philo->data->write_mtx);
	if (((st == TAKE_FIRST_FORK) || (st == TAKE_SECOND_FORK))
		&& !(sim_end(philo->data)))	
		printf(YELLOW"%-6ld"RESET" %d has taken a fork\n", 
		time, philo->id_philo);
	else if ((st = EATING) && !(sim_end(philo->data)))
		printf(BLUE"%-6ld"RESET" %d is eating\n", time, philo->id_philo);
	else if ((st == SLEEPING) && !(sim_end(philo->data)))
		printf(CYAN"%-6ld"RESET" %d is sleeping\n", time, philo->id_philo);
	else if ((st == THINKING) && !(sim_end(philo->data)))
		printf(MAG"%-6ld"RESET" %d is thinking\n", time, philo->id_philo);
	else if ((st == DEAD) && !(sim_end(philo->data)))
		printf(RED"%-6ld"RESET" %d died\n", time, philo->id_philo);
	pthread_mutex_unlock(&philo->data->write_mtx);
}
