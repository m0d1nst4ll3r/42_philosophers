/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 09:53:08 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/08 13:47:06 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>	// threads
#include <stdio.h>		// printf

/* --------------------------------------------------------------------- *\
|		t_philo
|
|	Structure passed to each philosopher thread.
|	Exists in an array, each struct corresponds to a different philo.
|
|	members:
|
|	- lfork				"forks" locked when eating, actually pointers
|	- rfork					to an array of mutexes (1 mutex per philo)
|	- write_mutex		protects writing, shared with monitor struct
|	- time_to_eat		milliseconds spent eating		|
|	- time_to_sleep	   	                sleeping		| these come from
|	- time_to_die	    	         until death		| program params
|	- meal_limit		times a philo can eat			|
|	- active_philos		number of philos that haven't reached the meal limit
|							this is decremented by 1 for each "stuffed" philo
|							monitor thread monitors this variable
|	- death_timer		when this philo will die, actually pointers
|							to an array monitored by the monitor thread
|							updated when philo is done eating
|	- timestamp_start	timestamp of when the threads started for writing
\* --------------------------------------------------------------------- */
typedef struct s_philo
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*write_mutex;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				meal_limit;
	int				*active_philos;
	int				*death_timer;
	int				timestamp_start;
}					t_philo;

/* --------------------------------------------------------------------- *\
|		t_monitor
|
|	Structure passed to monitor thread.
|	The monitor thread looks for conditions to stop:
|		All philosophers have reached the meal limit (active_philos == 0)
|		One philosopher is dead (death_timer_array[i] <= current time)
|
|	members:
|
|	- write_mutex			protects writing, shared with philo threads
|	- active_philos			number of philos that haven't reached the meal limit
|								this is decremented by 1 for each "stuffed" philo
|								we monitor this
|	- death_timer_array		array containing each philo's death timer
|								this is compared to current time
|	- timestamp_start		timestamp of when the threads started for writing
\* --------------------------------------------------------------------- */
typedef struct s_monitor
{
	pthread_mutex_t	*write_mutex;
	int				*active_philos;
	int				timestamp_start;
	int				*death_timer_array;
}		t_monitor;

//// Threaded functions for philos and monitor
// threads.c


#endif
