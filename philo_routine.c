#include "philo.h"

void	print_action(t_philo *philo, char *text)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->write_mutex);
	if (!sim_stopped(philo->table))
	{
		timestamp = get_time_ms() - philo->table->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, text);
	}
	pthread_mutex_unlock(&philo->table->write_mutex);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_action(philo, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
	else 
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		pthread_mutex_unlock(&philo->left_fork->mutex);
	}
}

void	*philo_routine(void *arg)
{
	t_philo *ph;

	ph = (t_philo *)arg;
	if (ph->table->num_philo == 1)
	{
		pthread_mutex_lock(&ph->left_fork->mutex);
		print_action(ph, "has taken a fork");
		ft_usleep(ph->table, ph->table->die_time);
		pthread_mutex_unlock(&ph->left_fork->mutex);
		return (NULL);
	}
	if (ph->id % 2 == 0)
		usleep(1000);
	while (!sim_stopped(ph->table))
	{
		print_action(ph, "is thinking");
		take_forks(ph);
		act_eat_sleep(ph);
	}
	return (NULL);
}

void	*monitoring_philo(void *arg)
{
	t_table	*tb;
	int		i;
	int		full_count;
	int		r;
	long	now;

	tb = (t_table *)arg;
	while (!sim_stopped(tb))
	{
		full_count = 0;
		now = get_time_ms();
		i = 0;
		while (i < tb->num_philo)
		{
			r = check_and_maybe_die(tb, i, now);
			if (r == 1)
				return (NULL);
			if (r == 2)
				full_count++;
			i++;
		}
		if (tb->limit_meals != -1 && full_count == tb->num_philo)
			return (stop_simulation(tb), NULL);
		usleep(1000);
	}
	return (NULL);
}
