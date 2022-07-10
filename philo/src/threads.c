/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:40:17 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/10 02:42:31 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo(void *arg)
{
	int		times_eaten;
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->start_mutex);
	pthread_mutex_unlock(philo->start_mutex);
	times_eaten = 0;
	while (times_eaten != philo->meal_limit)
	{
	}
	return (0);
}

static void	monitor2(t_data *data)
{
	int				i;
	struct timeval	curtime;

	if (!*data->active_philos)
		exit_prog(*data);
	i = -1;
	gettimeofday(&curtime, NULL);
	while (++i < data->args[0])
	{
		if (curtime.tv_sec >= data->death_timers[i].tv_sec
			&& curtime.tv_usec >= data->death_timers[i].tv_usec)
		{
			pthread_mutex_lock(data->write_mutex);
			printf("%d %d died\n", sub_ms(curtime, *data->timestamp_start),
				i);
			pthread_mutex_unlock(data->write_mutex);
			exit_prog(*data);
		}
	}
	usleep(5000);
}

static void	*monitor(void *arg)
{
	t_data			*data;

	data = (t_data *)arg;
	pthread_mutex_lock(data->start_mutex);
	pthread_mutex_unlock(data->start_mutex);
	while (1)
	{
		monitor2(data);
	}
	return (0);
}

// Launch all the philo threads
// Then launch the monitor thread
// A mutex is locked before and unlocked after, this keeps threads from
//   starting until all threads are launched
// The start timestamp and death timers are initialized right before unlocking
void	launch_threads(t_data data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(data.start_mutex);
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
		add_ms(data.death_timers + i, data.args[1]);
	pthread_mutex_unlock(data.start_mutex);
	i = -1;
	while (++i <= data.args[0])
		pthread_join(data.threads[i], NULL);
}
