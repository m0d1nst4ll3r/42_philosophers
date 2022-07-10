/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 21:27:18 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/10 02:02:21 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Subtracts a timeval to another timeval and returns the difference in ms
int	sub_ms(struct timeval a, struct timeval b)
{
	int	ms;

	ms = 1000 * (a.tv_sec - b.tv_sec);
	ms += (a.tv_usec - b.tv_usec) / 1000;
	return (ms);
}

// Adds milliseconds to a timeval
// Used to calculate when a philo should die
void	add_ms(struct timeval *a, int ms)
{
	a->tv_usec += ms * 1000;
	a->tv_sec += a->tv_usec / 1000000;
	a->tv_usec %= 1000000;
}
