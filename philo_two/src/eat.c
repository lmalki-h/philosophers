/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:27:08 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/13 14:05:12 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_two.h"

static void	take_forks(t_phil *phil)
{
	sem_wait(phil->state->forks);
	sem_wait(phil->state->forks);
}

static void	clean_forks(t_phil *phil)
{
	sem_post(phil->state->forks);
	sem_post(phil->state->forks);
}

void		eat(t_phil *phil)
{
	take_forks(phil);
	sem_wait(phil->mutex);
	sem_wait(phil->state->print);
	print_status(phil, TAKE_FORKS);
	print_status(phil, EAT);
	sem_post(phil->state->print);
	phil->time_of_last_meal = get_time_in_ms();
	sem_post(phil->mutex);
	ft_usleep(phil->state->time_to_eat);
	clean_forks(phil);
	phil->nb_meals++;
}
