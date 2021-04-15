/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:27:08 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/13 13:38:47 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

static void	take_forks(t_phil *phil)
{
	pthread_mutex_lock(phil->forks[FIRST]);
	pthread_mutex_lock(phil->forks[SECOND]);
}

static void	clean_forks(t_phil *phil)
{
	pthread_mutex_unlock(phil->forks[FIRST]);
	pthread_mutex_unlock(phil->forks[SECOND]);
}

void		eat(t_phil *phil)
{
	take_forks(phil);
	pthread_mutex_lock(phil->mutex);
	pthread_mutex_lock(phil->state->print);
	print_status(phil, TAKE_FORKS);
	print_status(phil, EAT);
	pthread_mutex_unlock(phil->state->print);
	phil->time_of_last_meal = get_time_in_ms();
	ft_usleep(phil->state->time_to_eat);
	pthread_mutex_unlock(phil->mutex);
	clean_forks(phil);
	phil->nb_meals++;
}
