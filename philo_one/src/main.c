/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:21:19 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/15 11:34:41 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

int			main(int ac, char **av)
{
	t_phil	**phils;

	phils = NULL;
	if (ac < NB_MIN_ARG || ac > NB_MAX_ARG)
		write(STDERR_FILENO, "Error: wrong number of arguments\n", 33);
	else
	{
		phils = init_simulation(ac, av);
		do_simulation(phils);
		free_simulation(phils);
	}
	return (SUCCESS);
}
