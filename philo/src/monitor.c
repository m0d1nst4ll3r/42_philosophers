/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:54:53 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/10 16:36:16 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Regularly check
// If the philos have all finished eating, if so exit
// If any philo is dead, if so print a message and exit
static void	monitor2(t_data *data)
{
	int				i;
	struct timeval	curtime;

	i = -1;
	gettimeofday(&curtime, NULL);
	while (++i < data->args[0])
	{
		if (curtime.tv_sec >= data->death_timers[i].tv_sec
			&& curtime.tv_usec >= data->death_timers[i].tv_usec)
		{
			pthread_mutex_lock(data->mutex);
			printf("%d %d died\n", sub_ms(curtime, *data->timestamp_start),
				i + 1);
			exit_prog(*data);
		}
	}
	if (!*data->active_philos)
		exit_prog(*data);
	usleep(100);
}

// The mutex lock in the beginning is used to synchronize thread starts
void	*monitor(void *arg)
{
	t_data			*data;

	data = (t_data *)arg;
	pthread_mutex_lock(data->mutex);
	pthread_mutex_unlock(data->mutex);
	while (1)
	{
		monitor2(data);
	}
	return (0);
}
