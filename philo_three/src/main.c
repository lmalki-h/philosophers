/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 13:21:19 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/14 13:17:38 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_three.h"

int		watch_dog(pid_t *pids, t_state *state)
{
	int i = 0;
	sem_wait(state->finish);
	while (i < state->nb_phil)
	{
		kill(pids[i], SIGTERM);
		i++;
	}
	return (SUCCESS);
}

void	*monitor_routine(void *arg)
{
	int		status;
	t_state *state;
	int 	finished_eating;

	state = (t_state *)arg;
	finished_eating = 0;
	while (finished_eating < state->nb_phil)
	{
		waitpid(0, &status, WUNTRACED);
		if (WEXITSTATUS(status) == DEATH)
		{
			return ((void *)0);

		}
		else if (WEXITSTATUS(status) == FINISHED)
			finished_eating++;
	}
	if (finished_eating == state->nb_phil)
		printf("Each philosopher ate %i times\n", state->nb_meals);
	sem_post(state->finish);
	return ((void *)0);
}

static int monitor_simulation(t_state *state)
{
	pthread_t	thread;

	if (state->nb_meals < INT_MAX)
	{
		if (pthread_create(&thread, NULL, monitor_routine, (void *)state))
			return (FAILURE);
		if (pthread_detach(thread))
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	start_simulation(t_phil **phils)
{
	t_state		*state;
	pid_t		pids[NB_PHIL_MAX];
	pid_t		id;
	int			i;

	i = 0;
	state = phils[0]->state;
	if (monitor_simulation(state))
	{
		write(STDERR_FILENO, "Error: could not start monitoring thread\n", 41);
		return (FAILURE);
	}
	state->start_time = get_time_in_ms();
	while (i < state->nb_phil)
	{
		if ((id = fork()) == 0)
		{
			break ;
		}
		pids[i] = id;
		i++;
	}
	if (id == 0)
	{
		routine(phils[i]);
		exit(SUCCESS);
	}
	else
		watch_dog(pids, state);
	return (SUCCESS);
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
