/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:21:19 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/14 11:34:51 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

static void	*monitor_simulation(void *arg)
{
	t_state *state;

	state = (t_state *)arg;
	while (!state->death && state->at_table > 0)
	{
		usleep(100);
	}
	if (state->death)
		return ((void *)0);
	printf("Each philosopher ate %i times\n", state->nb_meals);
	sem_post(state->finish);
	return ((void *)0);
}

static int	start_threads(t_phil **phils, t_state *state)
{
	int			i;
	pthread_t	thread;

	i = 0;
	if (state->nb_meals < INT_MAX)
	{
		if (pthread_create(&thread, NULL, monitor_simulation, (void *)state))
			return (FAILURE);
		if (pthread_detach(thread))
			return (FAILURE);
	}
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

static void	start_simulation(t_phil **phils)
{
	t_state *state;

	state = phils[0]->state;
	if (start_threads(phils, state) == FAILURE)
	{
		write(STDERR_FILENO, "Error: pthreads could not create\n", 16);
		free_simulation(phils);
		exit(FAILURE);
	}
	sem_wait(state->finish);
	while (state->at_table > 0)
		usleep(100);
	sem_post(state->finish);
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
		start_simulation(phils);
		free_simulation(phils);
	}
	return (SUCCESS);
}
