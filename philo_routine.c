#include "philo.h"

void	print_action(t_philo *philo, char *text)
{
	long	timestamp;
	pthread_mutex_lock(&philo->table->write_mutex);
	if (!philo->table->stop_sim)
	{
		timestamp = get_time_ms() - philo->table->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, text);
	}
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_action(philo, "has taken a fork");

	pthread_mutex_lock(&philo->right_fork->mutex);
	print_action(philo, "has taken a fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	*philo_routine(void *arg)
{
	t_philo *ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		usleep(1000);
	while (!ph->table->stop_sim)
	{
		print_action(ph, "is thinking");
		take_forks(ph);
		pthread_mutex_lock(&ph->table->sim_mutex);
		ph->time_last_meal = get_time_ms();
		pthread_mutex_unlock(&ph->table->sim_mutex);
		print_action(ph, "is eating");
		usleep(ph->table->eat_time * 1000);
		ph->meals_eaten++;
		if (ph->table->limit_meals != -1 && ph->meals_eaten >= ph->table->limit_meals)
		ph->is_full = true;
		drop_forks(ph);
		print_action(ph, "is sleeping");
		usleep(ph->table->sleep_time * 1000);
	}
	return (NULL);
}

void	*monitoring_philo(void *arg)
{
	t_table	*tb;
	int	i;

	tb = (t_table *)arg;
	while(!tb->stop_sim)
	{
		i = 0;
		while (i < tb->num_philo)
		{
			pthread_mutex_lock(&tb->sim_mutex);
			if (!tb->philos[i].is_full && get_time_ms() - tb->philos[i].time_last_meal > tb->die_time)
			{
				tb->stop_sim = 1;
				print_action(&tb->philos[i], "died");
				pthread_mutex_unlock(&tb->sim_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&tb->sim_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
