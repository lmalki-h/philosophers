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

static void	*monitor_simulation(void *arg)
{
	t_state *state;

	state = (t_state *)arg;
	while (state->at_table > 0)
	{
		usleep(100);
	}
	printf("Each philosopher ate %i times\n", state->nb_meals);
	pthread_mutex_unlock(state->finish);
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

void		watch_dog(t_phil **phils, t_state *state)
{
	int	i;

	i = 0;
	pthread_mutex_lock(state->finish);
	if (state->death)
	{
		while (i < state->nb_phil)
		{
			phils[i]->death = true;
			i++;
		}
	}
	while (state->at_table > 0)
		usleep(100);
	pthread_mutex_unlock(state->finish);
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
	watch_dog(phils, state);
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
