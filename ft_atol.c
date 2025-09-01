/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naimcheniounigomez <naimcheniounigomez@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:55:34 by naimcheniou       #+#    #+#             */
/*   Updated: 2025/08/06 21:10:18 by naimcheniou      ###   ########.fr       */
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