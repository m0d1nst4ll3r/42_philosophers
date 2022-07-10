/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:53:56 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/10 16:17:13 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_message(int id, char *msg, struct timeval start,
		pthread_mutex_t *mutex)
{
	struct timeval	curtime;

	pthread_mutex_lock(mutex);
	gettimeofday(&curtime, NULL);
	printf("%d %d %s", sub_ms(curtime, start), id, msg);
	pthread_mutex_unlock(mutex);
}

// Lock both forks before eating, unlock after
// Update death timer (using a variable to avoid monitor reading at wrong time)
// Sleep
// Print both actions
static void	eat_and_sleep(t_philo *philo)
{
	struct timeval	curtime;

	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(philo->rfork);
	print_message(philo->id, EAT, *philo->timestamp_start, philo->mutex);
	gettimeofday(&curtime, NULL);
	add_ms(&curtime, philo->time_to_die);
	add_ms(&curtime, philo->time_to_eat);
	philo->death_timer->tv_usec = curtime.tv_usec;
	philo->death_timer->tv_sec = curtime.tv_sec;
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	print_message(philo->id, SLEEP, *philo->timestamp_start, philo->mutex);
	usleep(philo->time_to_sleep * 1000);
}

// The mutex lock at the beginning is used to synchronize thread start
// times_eaten used to know when to stop
// For the first time philos eat, even philos go first, odd go second
void	*philo(void *arg)
{
	int		times_eaten;
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->mutex);
	pthread_mutex_unlock(philo->mutex);
	times_eaten = 0;
	while (times_eaten != philo->meal_limit)
	{
		print_message(philo->id, THINK, *philo->timestamp_start, philo->mutex);
		if (!times_eaten && philo->id % 2)
		{
			usleep(philo->time_to_eat * 1000);
		}
		eat_and_sleep(philo);
		times_eaten++;
	}
	pthread_mutex_lock(philo->mutex);
	(*philo->active_philos)--;
	pthread_mutex_unlock(philo->mutex);
	return (0);
}
