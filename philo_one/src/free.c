/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:03:12 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/12 21:07:58 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

void	free_state(t_state *state)
{
	pthread_mutex_destroy(state->print);
	free(state->print);
	pthread_mutex_unlock(state->finish);
	pthread_mutex_destroy(state->finish);
	free(state->finish);
	pthread_mutex_destroy(state->update);
	free(state->update);
	free(state);
}

void	free_simulation(t_phil **phils)
{
	int i;
	int	nb_phil;

	i = -1;
	nb_phil = phils[0]->state->nb_phil;
	free_state(phils[0]->state);
	while (++i < nb_phil)
	{
		pthread_mutex_destroy(phils[i]->forks[0]);
	}
	free(phils[0]->forks[0]);
	i = -1;
	while (++i < nb_phil)
	{
		if (phils[i]->id)
			free(phils[i]->id);
		pthread_mutex_destroy(phils[i]->mutex);
		free(phils[i]->mutex);
		free(phils[i]);
	}
	free(phils);
}
