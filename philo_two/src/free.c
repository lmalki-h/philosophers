/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:03:12 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/13 15:42:08 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

void	free_state(t_state *state)
{
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/finish");
	free(state);
}

void	free_simulation(t_phil **phils)
{
	int i;
	int	nb_phil;

	nb_phil = phils[0]->state->nb_phil;
	free_state(phils[0]->state);
	i = -1;
	while (++i < nb_phil)
	{
		if (phils[i]->id)
			free(phils[i]->id);
		free(phils[i]);
	}
	free(phils);
}
