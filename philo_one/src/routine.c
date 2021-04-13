/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:02:54 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/13 13:40:09 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

static void	*routine_death(void *arg)
{
	t_phil		*phil;

	phil = (t_phil *)arg;
	while (!phil->death && phil->nb_meals < phil->state->nb_meals)
	{
		pthread_mutex_lock(phil->mutex);
		if (time_since(phil->time_of_last_meal) >= phil->state->time_to_die)
		{
			pthread_mutex_lock(phil->state->print);
			print_status(phil, DEAD);
			phil->state->death = 1;
			pthread_mutex_unlock(phil->mutex);
			pthread_mutex_unlock(phil->state->print);
			pthread_mutex_unlock(phil->state->finish);
			return ((void *)0);
		}
		pthread_mutex_unlock(phil->mutex);
		usleep(1000);
	}
	return ((void *)0);
}

void		sleeps(t_phil *phil)
{
	pthread_mutex_lock(phil->state->print);
	print_status(phil, SLEEP);
	pthread_mutex_unlock(phil->state->print);
	ft_usleep(phil->state->time_to_sleep);
}

void		think(t_phil *phil)
{
	pthread_mutex_lock(phil->state->print);
	print_status(phil, THINK);
	pthread_mutex_unlock(phil->state->print);
}

void		*routine(void *arg)
{
	t_phil		*phil;
	pthread_t	death;

	phil = (t_phil *)arg;
	phil->time_of_last_meal = phil->state->start_time;
	pthread_create(&death, NULL, &routine_death, arg);
	pthread_detach(death);
	while (!phil->death && phil->nb_meals < phil->state->nb_meals)
	{
		eat(phil);
		sleeps(phil);
		think(phil);
		usleep(100);
	}
	phil->state->at_table--;
	return ((void *)0);
}
