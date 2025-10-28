/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naimcheniounigomez <naimcheniounigomez@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:55:34 by naimcheniou       #+#    #+#             */
/*   Updated: 2025/09/08 13:37:17 by naimcheniou      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	n;
	int		i;
	long	sign;

	n = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	if (!ft_isdigit(str[i]))
		(ft_putstr_fd("Error\n", STDERR_FILENO), exit(EXIT_FAILURE));
	while (ft_isdigit(str[i]))
		n = (str[i++] - '0') + (n * 10);
	if (!ft_isdigit(str[i]) && str[i])
		(ft_putstr_fd("Error\n", STDERR_FILENO), exit(EXIT_FAILURE));
	n *= sign;
	if (n > INT_MAX || n < INT_MIN)
		(ft_putstr_fd("Error\n", STDERR_FILENO), exit(EXIT_FAILURE));
	return (n);
}

void	print_death(t_philo *p)
{
	long	ts;

	pthread_mutex_lock(&p->table->write_mutex);
	ts = get_time_ms() - p->table->start_time;
	printf("%ld %d died\n", ts, p->id);
	pthread_mutex_unlock(&p->table->write_mutex);
}

void	cleanup_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->sim_mutex);
	free(table->forks);
	free(table->philos);
}
