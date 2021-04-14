/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:02:54 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/14 13:13:10 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_three.h"

static void	*routine_death(void *arg)
{
	t_phil		*phil;

	phil = (t_phil *)arg;
	while (!phil->death && phil->nb_meals < phil->state->nb_meals)
	{
		sem_wait(phil->mutex);
		if (time_since(phil->time_of_last_meal) >= phil->state->time_to_die)
		{
			sem_wait(phil->state->print);
			print_status(phil, DEAD);
			phil->death = true;
			sem_post(phil->mutex);
			sem_post(phil->state->finish);
			return ((void *)0);
		}
		sem_post(phil->mutex);
		usleep(100);
	}
	return ((void *)0);
}

void		sleeps(t_phil *phil)
{
	sem_wait(phil->state->print);
	print_status(phil, SLEEP);
	sem_post(phil->state->print);
	ft_usleep(phil->state->time_to_sleep);
}

void		think(t_phil *phil)
{
	sem_wait(phil->state->print);
	print_status(phil, THINK);
	sem_post(phil->state->print);
}

int 	routine(void *arg)
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
	if (phil->death)
	{
		printf("leaving because dead\n");
		exit(DEATH);
	}
	else
		exit(FINISHED);
}
