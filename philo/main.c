/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncheniou <ncheniou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:21:49 by ncheniou          #+#    #+#             */
/*   Updated: 2025/10/21 16:22:40 by ncheniou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (!parse_arguments(argc, argv, &table))
		return (EXIT_FAILURE);
	if (!init_simulation(&table))
		return (EXIT_FAILURE);
	start_simulation(&table);
	cleanup_simulation(&table);
	return (EXIT_SUCCESS);
}
