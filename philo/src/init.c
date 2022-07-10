/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:29:43 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/10 16:22:38 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// As many forks and timers as philos
// Num of philos is in args[0]
// Error out if any malloc failed, or if mutex init failed
// Active philos needs to be a pointer because philos will modify it
void	init_data(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(*data->forks) * data->args[0]);
	data->philos = malloc(sizeof(*data->philos) * data->args[0]);
	data->death_timers = malloc(sizeof(*data->death_timers) * data->args[0]);
	data->threads = malloc(sizeof(*data->threads) * (data->args[0] + 1));
	if (!data->forks || !data->philos || !data->death_timers || !data->threads
		|| pthread_mutex_init(data->mutex, NULL))
		exit_prog(*data);
	i = -1;
	while (++i < data->args[0])
	{
		if (pthread_mutex_init(data->forks + i, NULL))
			exit_prog(*data);
	}
	*data->active_philos = data->args[0];
}

// Copying data into each philos structure
// Death timers are assigned based on index
// Forks: left fork is the philo's fork, right fork is the next philo's fork
void	init_philos(t_data data)
{
	int	i;

	i = -1;
	while (++i < data.args[0])
	{
		data.philos[i].lfork = data.forks + i;
		if (i + 1 == data.args[0])
			data.philos[i].rfork = data.forks;
		else
			data.philos[i].rfork = data.forks + i + 1;
		data.philos[i].mutex = data.mutex;
		data.philos[i].time_to_die = data.args[1];
		data.philos[i].time_to_eat = data.args[2];
		data.philos[i].time_to_sleep = data.args[3];
		data.philos[i].meal_limit = data.args[4];
		data.philos[i].active_philos = data.active_philos;
		data.philos[i].death_timer = data.death_timers + i;
		data.philos[i].timestamp_start = data.timestamp_start;
		data.philos[i].id = i + 1;
	}
}
