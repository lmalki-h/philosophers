/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:53:45 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/13 15:31:12 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

static void		create_sem(char *name, sem_t **sem, unsigned int value)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, value);
}

static bool		is_valid_state(t_state *state)
{
	if (state->nb_phil < 2 || state->nb_phil > 200)
		return (false);
	if (state->time_to_die < 60)
		return (false);
	if (state->time_to_eat < 60)
		return (false);
	if (state->time_to_sleep < 60)
		return (false);
	if (state->nb_meals < 1)
		return (false);
	if (state->print == NULL)
		return (false);
	return (true);
}

static t_state	*init_state(int ac, char **av)
{
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	if (!state)
	{
		write(STDERR_FILENO, "Error: malloc\n", 14);
		exit(-1);
	}
	state->nb_phil = ft_atoi(av[1]);
	state->time_to_die = ft_atoi(av[2]);
	state->time_to_eat = ft_atoi(av[3]);
	state->time_to_sleep = ft_atoi(av[4]);
	state->nb_meals = ac == 6 ? ft_atoi(av[5]) : INT_MAX;
	create_sem(PRINT_SEM, &state->print, 1);
	create_sem(FORKS_SEM, &state->forks, state->nb_phil);
	create_sem(FINISH_SEM, &state->finish, 0);
	create_sem(UPDATE_SEM, &state->update, 1);
	state->at_table = state->nb_phil;
	state->death = 0;
	return (state);
}

static t_phil	**init_philosophers(t_state *state)
{
	char		buf[LEN_BUF];
	t_phil		**phils;
	int			i;

	i = -1;
	phils = (t_phil **)malloc(sizeof(t_phil *) * state->nb_phil);
	if (!phils)
		return (NULL);
	while (++i < state->nb_phil)
	{
		phils[i] = (t_phil *)malloc(sizeof(t_phil));
		if (!phils[i])
			return (NULL);
		phils[i]->id = ft_itoa(i + 1);
		phils[i]->state = state;
		phils[i]->nb_meals = 0;
		buf[0] = '\0';
		ft_strlcat(buf, "/", LEN_BUF);
		ft_strlcat(buf, phils[i]->id, LEN_BUF);
		create_sem(buf, &phils[i]->mutex, 1);
	}
	return (phils);
}

t_phil			**init_simulation(int ac, char **av)
{
	t_state			*state;
	t_phil			**phil;

	state = init_state(ac, av);
	if (!is_valid_state(state))
	{
		free_state(state);
		write(STDERR_FILENO, "Error: invalid state\n", 21);
		exit(-1);
	}
	phil = init_philosophers(state);
	if (!phil)
	{
		free_state(state);
		write(STDERR_FILENO, "Error: Couldn't create philosophers\n", 42);
	}
	return (phil);
}
