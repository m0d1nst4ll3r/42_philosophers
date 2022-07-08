/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:40:14 by rpohlen           #+#    #+#             */
/*   Updated: 2022/07/08 13:47:19 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int				args[5]; //num philo, die, eat, sleep, limit
	pthread_mutex_t	**forks;
	t_philo			**philos;

	//interpret args, error out, write into args[5]
	read_params(ac, av, args);
	//create forks, error out if fail
	forks = create_forks(args[1]);
	//create philos, error out (+ free mutex) if fail
	philos = create_philos(args[1]);
	//
	return (0);
}
