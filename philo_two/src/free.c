/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:03:12 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/13 16:22:43 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

void	free_state(t_state *state)
{
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/finish");
	sem_close(state->print);
	sem_close(state->finish);
	sem_close(state->forks);
	free(state);
}

void	free_simulation(t_phil **phils)
{
	char	buf[LEN_BUF];
	int		i;
	int		nb_phil;

	nb_phil = phils[0]->state->nb_phil;
	free_state(phils[0]->state);
	i = -1;
	while (++i < nb_phil)
	{
		buf[0] = '\0';
		ft_strlcat(buf, "/", LEN_BUF);
		ft_strlcat(buf, phils[i]->id, LEN_BUF);
		sem_unlink(buf);
		sem_close(phils[i]->mutex);
		if (phils[i]->id)
			free(phils[i]->id);
		free(phils[i]);
	}
	free(phils);
}
