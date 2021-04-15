/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:33:00 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/15 11:51:03 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_three.h"

static int	kill_processes(pid_t *pids, int nb_phil)
{
	int	i;

	i = 0;
	while (i < nb_phil)
	{
		kill(pids[i], SIGTERM);
		i++;
	}
	return (SUCCESS);
}

static void	*monitor_routine(pid_t *pids, t_state *state)
{
	int		status;
	int		finished_eating;

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
	kill_processes(pids, state->nb_phil);
	return ((void *)0);
}

int			do_simulation(t_phil **phils)
{
	t_state		*state;
	pid_t		pids[NB_PHIL_MAX];
	pid_t		id;
	int			i;

	i = 0;
	state = phils[0]->state;
	state->start_time = get_time_in_ms();
	while (i < state->nb_phil)
	{
		if ((id = fork()) == 0)
			break ;
		pids[i] = id;
		i++;
	}
	if (id == 0)
	{
		routine(phils[i]);
		exit(SUCCESS);
	}
	else
	{
		monitor_routine(pids, state);
	}
	return (SUCCESS);
}
