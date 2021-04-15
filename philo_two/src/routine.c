/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:02:54 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/15 11:40:21 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

static void	*routine_death(void *arg)
{
	t_phil		*phil;

	phil = (t_phil *)arg;
	while (!phil->state->death && phil->nb_meals < phil->state->nb_meals)
	{
		sem_wait(phil->mutex);
		if (time_since(phil->time_of_last_meal) >= phil->state->time_to_die)
		{
			sem_wait(phil->state->print);
			print_status(phil, DEAD);
			phil->state->death = 1;
			sem_post(phil->mutex);
			sem_post(phil->state->print);
			sem_post(phil->state->finish);
			return ((void *)0);
		}
		sem_post(phil->mutex);
		usleep(1000);
	}
	return ((void *)0);
}

static void	sleeps(t_phil *phil)
{
	sem_wait(phil->state->print);
	print_status(phil, SLEEP);
	sem_post(phil->state->print);
	ft_usleep(phil->state->time_to_sleep);
}

static void	think(t_phil *phil)
{
	sem_wait(phil->state->print);
	print_status(phil, THINK);
	sem_post(phil->state->print);
}

void		*routine(void *arg)
{
	t_phil		*phil;
	pthread_t	death;

	phil = (t_phil *)arg;
	phil->time_of_last_meal = get_time_in_ms();
	pthread_create(&death, NULL, &routine_death, arg);
	pthread_detach(death);
	while (!phil->state->death && phil->nb_meals < phil->state->nb_meals)
	{
		eat(phil);
		sleeps(phil);
		think(phil);
		usleep(100);
	}
	sem_wait(phil->state->update);
	phil->state->at_table--;
	sem_post(phil->state->update);
	return ((void *)0);
}
