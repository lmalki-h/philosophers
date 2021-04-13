/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:53:45 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/12 21:06:14 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

static pthread_mutex_t		*init_mutexes(int nb)
{
	int					i;
	pthread_mutex_t		*mutexes;

	mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb);
	if (!mutexes)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(&mutexes[i], NULL))
			return (NULL);
		i++;
	}
	return (mutexes);
}

static bool					is_valid_state(t_state *state)
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

static t_state				*init_state(int ac, char **av)
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
	state->print = init_mutexes(1);
	state->finish = init_mutexes(1);
	pthread_mutex_lock(state->finish);
	state->at_table = state->nb_phil;
	state->death = 0;
	return (state);
}

static t_phil				**init_philosophers(t_state *state,
										pthread_mutex_t *forks)
{
	t_phil			**phil;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	int				i;

	i = 0;
	phil = (t_phil **)malloc(sizeof(t_phil *) * state->nb_phil);
	if (!phil)
		return (NULL);
	while (i < state->nb_phil)
	{
		phil[i] = (t_phil *)malloc(sizeof(t_phil));
		if (!phil[i])
			return (NULL);
		phil[i]->id = ft_itoa(i + 1);
		right = &forks[(i + 1) % state->nb_phil];
		left = &forks[i];
		phil[i]->forks[FIRST] = (i + 1) % 2 == 0 ? right : left;
		phil[i]->forks[SECOND] = (i + 1) % 2 == 0 ? left : right;
		phil[i]->state = state;
		phil[i]->nb_meals = 0;
		phil[i]->death = false;
		phil[i]->mutex = init_mutexes(1);
		i++;
	}
	return (phil);
}

t_phil						**init_simulation(int ac, char **av)
{
	t_state			*state;
	pthread_mutex_t *forks;
	t_phil			**phil;

	state = init_state(ac, av);
	if (!is_valid_state(state))
	{
		free_state(state);
		write(STDERR_FILENO, "Error: invalid state\n", 21);
		exit(-1);
	}
	forks = init_mutexes(state->nb_phil);
	if (!forks)
	{
		free_state(state);
		write(STDERR_FILENO, "Error: Couldn't create mutexes\n", 35);
	}
	phil = init_philosophers(state, forks);
	if (!phil)
	{
		free_state(state);
		free(forks);
		write(STDERR_FILENO, "Error: Couldn't create philosophers\n", 42);
	}
	return (phil);
}
