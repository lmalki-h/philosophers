/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:33:00 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/15 11:33:24 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_three.h"

int		kill_processes(pid_t *pids, t_state *state)
{
	int i = 0;
	while (i < state->nb_phil)
	{
		kill(pids[i], SIGTERM);
		i++;
	}
	return (SUCCESS);
}

void	*monitor_routine(t_state *state)
{
	int		status;
	int 	finished_eating;

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
	return ((void *)0);
}

int		start_simulation(t_phil **phils)
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
	{
		monitor_routine(state);
		kill_processes(pids, state);
	}
	return (SUCCESS);
}