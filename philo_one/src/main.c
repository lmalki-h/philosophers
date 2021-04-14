/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:21:19 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/13 14:34:18 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

static int	start_threads(t_phil **phils, t_state *state)
{
	int			i;
	pthread_t	thread;

	i = 0;
	state->start_time = get_time_in_ms();
	while (i < state->nb_phil)
	{
		if (pthread_create(&thread, NULL, routine, (void *)phils[i]))
			return (FAILURE);
		if (pthread_detach(thread))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static void	do_simulation(t_phil **phils)
{
	t_state *state;

	state = phils[0]->state;
	if (start_threads(phils, state) == FAILURE)
	{
		write(STDERR_FILENO, "Error: pthreads could not create\n", 16);
		free_simulation(phils);
		exit(FAILURE);
	}
	pthread_mutex_lock(state->finish);
	while (state->at_table > 0)
		usleep(100);
	if (!state->death)
		printf("Each philosopher ate %i times\n", state->nb_meals);
}

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
