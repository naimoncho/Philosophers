#include "philo.h"

void	act_eat_sleep(t_philo *ph)
{
	pthread_mutex_lock(&ph->table->sim_mutex);
	ph->time_last_meal = get_time_ms();
	pthread_mutex_unlock(&ph->table->sim_mutex);
	print_action(ph, "is eating");
	ft_usleep(ph->table, ph->table->eat_time);
	drop_forks(ph);
	ph->meals_eaten++;
	if (ph->table->limit_meals != -1
		&& ph->meals_eaten >= ph->table->limit_meals)
		ph->is_full = true;
	print_action(ph, "is sleeping");
	ft_usleep(ph->table, ph->table->sleep_time);
}

// VERSIÓN BUENA
int check_and_maybe_die(t_table *tb, int i, long now)
{
    long last_meal;
    bool is_full;

    // Entramos en la sección crítica solo para leer los datos de forma segura
    pthread_mutex_lock(&tb->philos[i].meal_mutex);
    last_meal = tb->philos[i].time_last_meal;
    is_full = tb->philos[i].is_full;
    pthread_mutex_unlock(&tb->philos[i].meal_mutex); // <<< ¡Soltamos el mutex INMEDIATAMENTE!

    // Ahora que estamos fuera de la sección crítica, podemos tomar decisiones y llamar a otras funciones
    if (!is_full && (now - last_meal > tb->die_time))
    {
        print_death(&tb->philos[i]); // Esto ya no causa deadlock
        stop_simulation(tb);
        return (1); // Murió
    }
    if (is_full)
        return (2); // Lleno
    return (0); // Sigue vivo
}
