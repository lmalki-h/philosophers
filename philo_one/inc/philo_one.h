/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:02:39 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/15 11:29:47 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include "../../shared/philosophers.h"
# define NB_PHIL_MAX 200
# define LEN_BUF 100

typedef struct				s_state
{
	int						nb_phil;
	int						time_to_die;
	int						time_to_sleep;
	int						time_to_eat;
	int						nb_meals;
	int						at_table;
	int						start_time;
	int						death;
	pthread_mutex_t					*print;
	pthread_mutex_t					*finish;
	pthread_mutex_t					*update;
}							t_state;

typedef struct				s_phil
{
	char					*id;
	pthread_mutex_t			*forks[2];
	size_t					time_of_last_meal;
	int						nb_meals;
	pthread_mutex_t			*mutex;
	struct s_state			*state;
}							t_phil;

void						*routine(void *arg);
void						free_state(t_state *state);
void						free_simulation(t_phil **phils);
t_phil						**init_simulation(int ac, char **av);
int							print_status(t_phil *phil, char *action);
void						eat(t_phil *phil);
void						do_simulation(t_phil **phils);

#endif
