/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncheniou <ncheniou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:29:19 by ncheniou          #+#    #+#             */
/*   Updated: 2025/10/21 16:30:35 by ncheniou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(char *s)
{
	int	index;

	index = 0;
	if (!s || !s[0])
		return (0);
	while (s[index])
	{
		if (s[index] < '0' || s[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

long	get_time_ms(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

int	sim_stopped(t_table *table)
{
	int	sim;

	pthread_mutex_lock(&table->sim_mutex);
	sim = table->stop_sim;
	pthread_mutex_unlock(&table->sim_mutex);
	return (sim);
}

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->sim_mutex);
	table->stop_sim = 1;
	pthread_mutex_unlock(&table->sim_mutex);
}

void	ft_usleep(t_table *table, long ms)
{
	long	start;

	start = get_time_ms();
	while (!sim_stopped(table))
	{
		if (get_time_ms() - start >= ms)
			break ;
		usleep(500);
	}
}
