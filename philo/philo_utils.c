/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncheniou <ncheniou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:28:57 by ncheniou          #+#    #+#             */
/*   Updated: 2025/10/22 13:11:34 by ncheniou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arguments(int ac, char **av, t_table *table)
{
	int	i;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo nbr_philo time_die time_eat ");
		printf("time_sleep [nbr_eat]\n");
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (printf("Error: invalid argument\n"), 0);
		i++;
	}
	table->num_philo = ft_atol(av[1]);
	table->die_time = ft_atol(av[2]);
	table->eat_time = ft_atol(av[3]);
	table->sleep_time = ft_atol(av[4]);
	if (ac == 6)
		table->limit_meals = ft_atol(av[5]);
	else
		table->limit_meals = -1;
	table->stop_sim = 0;
	return (1);
}

static int	init_mutexes(t_table *table)
{
	int	i;

	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->sim_mutex, NULL);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		pthread_mutex_init(&table->philos[i].meal_mutex, NULL);
		table->forks[i].id = i;
		i++;
	}
	return (1);
}

static void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].time_last_meal = 0;
		table->philos[i].is_full = false;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->num_philo];
		table->philos[i].table = table;
		i++;
	}
}

int	init_simulation(t_table *table)
{
	table->forks = malloc(sizeof(t_fork) * table->num_philo);
	table->philos = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->forks || !table->philos)
		return (printf("Error: malloc failed\n"), 0);
	if (!init_mutexes(table))
	{
		free(table->forks);
		free(table->philos);
		return (0);
	}
	init_philos(table);
	return (1);
}

void	start_simulation(t_table *table)
{
	int			i;
	pthread_t	monitor;

	table->start_time = get_time_ms();
	i = 0;
	while (i < table->num_philo)
	{
		table->philos[i].time_last_meal = table->start_time;
		pthread_create(&table->philos[i].id_thread,
			NULL, philo_routine, &table->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitoring_philo, table);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philos[i].id_thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}
