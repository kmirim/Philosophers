/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:39:13 by lbarcelo          #+#    #+#             */
/*   Updated: 2025/02/17 04:24:52 by lbarcelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h> // retirar depois de testar mutex/thread
# include <sys/time.h>
# include <unistd.h>
/*
 * ASCI ESCAPE SEQUENCES FOR BOLD TEXT COLORS:
 * Personalizar retorno de erros e sugestões.
 */

# define RED "\x1b[1;31m"
# define GREEN "\x1b[1;32m"
# define YELLOW "\x1b[1;33m"
# define BLUE "\x1b[1;34m"
# define MAG "\x1b[1;35m"
# define CYAN "\x1b[1;36m"
# define WHITE "\x1b[1;37m"
# define RESET "\x1b[0m"

# define DEBUG_MODE 0

/*DEFINIÇÕES PARA O COMPILADOR*/
typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

/*ENUM PARA STATUS DOS PHILOS*/

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEAD,
}						t_philo_status;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

/*ENUM PARA VALORES DE MUTEX E THREADS*/
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

/*ESTRUTURA DO FORK(GARFO)*/
typedef struct s_fork
{
	t_mtx				fork_mtx;
	int					fork_id;
}						t_fork;

/*ESTRUTURA DE UM PHILO(FILÓSOFO)*/
typedef struct s_philo
{
	int					id_philo;

	long				meals_counter;
	bool				max_meals;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mtx				philo_mtx;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_max_meals;
	bool				init_s;
	bool				finish_s;
	long				start_time;
	bool				all_threads_ready;
	long				philos_ready;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				table_mtx;
	t_mtx				write_mtx;
	pthread_t			monitor_thread;
}						t_data;
//---------utils.c-------//

void					error_exit(const char *str);
void					desynch_philo(t_philo *philo);
long					gettime(t_time_code time_code);
void					precise_usleep(long usec, t_data *data);
void					cleaning_table(t_data *data);

//---------parsing.c-------//
void					parse_input(t_data *data, char **value);

//--------safe_funcitions.c-------//
void					safe_pthread(pthread_t *thread, void *(*foo)(void *),
							void *data, t_opcode opcode);
void					safe_mtx(t_mtx *mutex, t_opcode opcode);
void					*safe_malloc(size_t bytes);
//-------------init.c-------------//
void					data_init(t_data *data);

//------------dinner.c-------------//
void					dinner_start(t_data *data);
void					*dinner_simulation(void *data);
void					*lone_philo(void *data);
void					thinking(t_philo *philo);

//---------getters_setters.c-----------//
void					set_bool(t_mtx *mtx, bool *target, bool value);
void					set_long(t_mtx *mtx, long *target, long value);
long					get_long(t_mtx *mtx, long *value);
bool					get_bool(t_mtx *mtx, bool *value);
bool					sim_end(t_data *data);

void					add_long(t_mtx *mtx, long *var);

//---------synchro utils-----------//
void					wait_all_threads(t_data *data);
bool					all_threads_running(t_mtx *mtx, long *threads,
							long philo_nbr);

//---------write_status----------//
void					write_status(t_philo_status st, t_philo *philo);

//--------teste_mutex.c----------//
void					test_mutex(void);
void					*thread_function(void *value);
void					test_thread(void);

//--------monitoring.c----------//
void					*monitor_dinner(void *info);

#endif
