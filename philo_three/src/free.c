/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:03:12 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/14 11:07:10 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_three.h"

void	free_state(t_state *state)
{
	if (sem_unlink("/print"))
		write(STDERR_FILENO, "Error: failed to unlink /print\n", 31);
	if (sem_unlink("/forks"))
		write(STDERR_FILENO, "Error: failed to unlink /forks\n", 31);
	if (sem_unlink("/finish"))
		write(STDERR_FILENO, "Error: failed to unlink /finish\n", 32);
	if (sem_close(state->print))
		write(STDERR_FILENO, "Error: failed to close /print\n", 30);
	if (sem_close(state->forks))
		write(STDERR_FILENO, "Error: failed to close /forks\n", 30);
	if (sem_close(state->finish))
		write(STDERR_FILENO, "Error: failed to close /finish\n", 31);
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
		if (sem_unlink(buf))
			write(STDERR_FILENO, "Error: failed to unlink mutex\n", 30);
		if (sem_close(phils[i]->mutex))
			write(STDERR_FILENO, "Error: failed to close mutex\n", 29);
		if (phils[i]->id)
			free(phils[i]->id);
		free(phils[i]);
	}
	free(phils);
}
