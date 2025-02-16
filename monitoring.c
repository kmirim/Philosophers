#include "philo.h"

// Função para verificar se um filósofo morreu
static bool philo_died(t_philo *philo)
{
    long duration; // Duração desde a última refeição
    long t_to_die; // Tempo para morrer

    // Verifica se o filósofo atingiu o número máximo de refeições
    if (get_bool(&philo->philo_mtx, &philo->max_meals))
        return (false);

    // Calcula a duração desde a última refeição
    duration = gettime(MILLISECOND) - get_long(&philo->philo_mtx, &philo->last_meal_time);
    // Obtém o tempo para morrer em milissegundos
    t_to_die = philo->data->time_to_die;

    // Verifica se a duração desde a última refeição é maior que o tempo para morrer
    if (duration > t_to_die)
        return (true);
    return (false);
}

// Função para monitorar o jantar dos filósofos
void *monitor_dinner(void *info)
{
    t_data *data;
    int i;

    data = (t_data *)info;
    i = -1;

    // Espera até que todos os filósofos estejam prontos
    while (!all_threads_running(&data->table_mtx, &data->philos_ready, data->philo_nbr))
        continue;

    // Loop principal de monitoramento
    while (!sim_end(data))
    {
        i = -1;
        // Verifica cada filósofo
        while (++i < data->philo_nbr && !sim_end(data))
        {
            // Se um filósofo morreu
            if (philo_died(data->philos + i))
            {
                t_philo *philo = data->philos + i;
                // Calcula o tempo desde o início do programa
                long time = gettime(MILLISECOND) - philo->data->init_s;
                // Se o filósofo não atingiu o número máximo de refeições
                if (!philo->max_meals)
                {
                    // Bloqueia o mutex de escrita
                    pthread_mutex_lock(&philo->data->write_mtx);
                    // Se a simulação ainda não terminou, imprime a mensagem de morte
                    if (!sim_end(philo->data))
                        printf(RED"%-6ld"RESET" %d died\n", time, philo->id_philo);
                    // Desbloqueia o mutex de escrita
                    pthread_mutex_unlock(&philo->data->write_mtx);
                }
                // Sinaliza que a simulação terminou
                set_bool(&data->table_mtx, &data->finish_s, true);
            }
        }
    }
    return (NULL);
}