/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:25:23 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/10 01:14:52 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* --------------------------------------------------------------------- *\
|		ft_atoi_strict
|
|	Works like regular atoi, except it only accepts numbers, and it
|		recognizes overflows.
|
|	A number is defined as an optional '-' and then only digits,
|		no spaces, no plusses, no empty strings.
|
|	When a bad format or overflow is detected, return 1.
|
|	Because of the error return, the number is passed as reference.
\* --------------------------------------------------------------------- */
static int	ft_atoi_strict(const char *s, int *n)
{
	char	neg;

	if (!s || !n || !*s)
		return (1);
	neg = 1;
	*n = 0;
	if (*s == '-')
	{
		neg = -1;
		s++;
	}
	while (*s && (*s ^ '0') < 10)
	{
		if (*n != (int)((unsigned int)*n * 10) / 10)
			return (1);
		*n = *n * 10 + *s - '0';
		if (*n && (*n - (neg < 0)) < 0)
			return (1);
		s++;
	}
	if (*s)
		return (1);
	*n = neg * *n;
	return (0);
}

// Check if number of args is ok
// If so, check if all args are numbers and atoi them
// If so, check if all args were the right value
// If so, return 0, otherwise, return 1
int	read_params(int ac, char **av, int args[5])
{
	if (ac == 5 || ac == 6)
	{
		args[4] = -1;
		if (!ft_atoi_strict(av[1], args + 0)
			&& !ft_atoi_strict(av[2], args + 1)
			&& !ft_atoi_strict(av[3], args + 2)
			&& !ft_atoi_strict(av[4], args + 3)
			&& (ac == 5 || !ft_atoi_strict(av[5], args + 4)))
		{
			if (args[0] >= 1 && args[1] >= 0 && args[2] >= 0
				&& args[3] >= 0 && (ac == 5 || args[4] >= 0))
				return (0);
		}
	}
	return (1);
}
