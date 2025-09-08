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

int	check_and_maybe_die(t_table *tb, int i, long now)
{
	long	last;
	bool	full;

	pthread_mutex_lock(&tb->sim_mutex);
	last = tb->philos[i].time_last_meal;
	full = tb->philos[i].is_full;
	pthread_mutex_unlock(&tb->sim_mutex);
	if (!full && (now - last > tb->die_time))
	{
		print_death(&tb->philos[i]);
		stop_simulation(tb);
		return (1);
	}
	if (full)
		return (2);
	return (0);
}
