/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:27:58 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/10 01:49:42 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage(void)
{
	printf("Usage:\n\
./philo   number_of_philosophers   time_to_die   time_to_eat\
   time_to_sleep   [number_of_times_each_philosopher_must_eat]\n");
	exit(0);
}

void	exit_prog(t_data data)
{
	int	i;

	i = -1;
	while (++i < data.args[0])
		pthread_mutex_destroy(data.forks + i);
	free(data.forks);
	free(data.philos);
	free(data.death_timers);
	free(data.threads);
	pthread_mutex_destroy(data.write_mutex);
	pthread_mutex_destroy(data.start_mutex);
	exit(1);
}
