/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 09:53:08 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/10 15:55:19 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"

# include <pthread.h>	// threads
# include <stdlib.h>	// exit malloc free
# include <stdio.h>		// printf
# include <unistd.h>	// usleep
# include <sys/time.h>	// gettimeofday

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
|	- mutex				protects writing and touching active_philos
|							also helps sync thread start
|							shared with monitor
|	- id				id of the philo for writing & strategy
|	- time_to_die	    	         until death		|
|	- time_to_eat		milliseconds spent eating		|
|	- time_to_sleep	   	                sleeping		| these come from
|	- meal_limit		times a philo can eat			| program params
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
	pthread_mutex_t	*mutex;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_limit;
	int				*active_philos;
	struct timeval	*death_timer;
	struct timeval	*timestamp_start;
}					t_philo;

/* --------------------------------------------------------------------- *\
|		t_data
|
|	Main program structure to hold data
|	Init in main.c, filled as part of program init process
|	Sent to monitor thread
|
|	members:
|
|	- args				curated arguments: number of philos, time to die, to eat,
|							to sleep, meal limit
|	- mutex				protects writing and touching active_philos
|							also helps sync thread start
|							shared with monitor
|	- threads			all threads used - philo and monitor
|	- forks				list of mutexes, one for each philo
|	- philos			list of s_philo structures to send to each philo thread
|	- monitor			monitor structure sent to monitor thread
|	- active_philos		number of philos that have not reached the meal limit
|	- death_timer_array	array containing each philo's death timer
\* --------------------------------------------------------------------- */
typedef struct s_data
{
	int				args[5];
	pthread_mutex_t	mutex[1];
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	t_philo			*philos;
	int				active_philos[1];
	struct timeval	*death_timers;
	struct timeval	timestamp_start[1];
}					t_data;

//// Threaded functions for philos and monitor
// threads.c
// philo.c
// monitor.c
void	launch_threads(t_data data);
void	*philo(void *arg);
void	*monitor(void *arg);

//// Functions to manipulate gettimeofday time values
// time.c
int		sub_ms(struct timeval a, struct timeval b);
void	add_ms(struct timeval *a, int ms);

//// Init functions to init structures
// init.c
void	init_data(t_data *data);
void	init_philos(t_data data);

//// Exit functions that free or print usage before exiting
// exit.c
void	usage(void);
void	exit_prog(t_data data);

//// Params handling
// params.c
int		read_params(int ac, char **av, int args[5]);

#endif
