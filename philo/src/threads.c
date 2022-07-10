/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:40:17 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/10 16:15:03 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Launch all the philo threads
// Then launch the monitor thread
// A mutex is locked before and unlocked after, this keeps threads from
//   starting until all threads are launched
// The start timestamp and death timers are initialized right before unlocking
void	launch_threads(t_data data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(data.mutex);
	while (++i < data.args[0])
	{
		if (pthread_create(data.threads + i, NULL, &philo, data.philos + i))
			exit_prog(data);
	}
	if (pthread_create(data.threads + i, NULL, &monitor, &data))
		exit_prog(data);
	gettimeofday(data.timestamp_start, NULL);
	i = -1;
	while (++i < data.args[0])
	{
		data.death_timers[i].tv_sec = data.timestamp_start->tv_sec;
		data.death_timers[i].tv_usec = data.timestamp_start->tv_usec;
		add_ms(data.death_timers + i, data.args[1]);
	}
	pthread_mutex_unlock(data.mutex);
	i = -1;
	while (++i <= data.args[0])
		pthread_join(data.threads[i], NULL);
}
