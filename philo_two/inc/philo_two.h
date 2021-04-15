/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:02:39 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/15 11:32:04 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include "../../shared/philosophers.h"
# define NB_PHIL_MAX 200
# define LEN_BUF 100
# define PRINT_SEM "/print"
# define FORKS_SEM "/forks"
# define FINISH_SEM "/finish"
# define UPDATE_SEM "/update"
# include <semaphore.h>

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
	sem_t					*print;
	sem_t					*update;
	sem_t					*finish;
	sem_t					*forks;
}							t_state;

typedef struct				s_phil
{
	char					*id;
	size_t					time_of_last_meal;
	int						nb_meals;
	sem_t					*mutex;
	struct s_state			*state;
}							t_phil;

void						*routine(void *arg);
void						free_state(t_state *state);
void						free_simulation(t_phil **phils);
t_phil						**init_simulation(int ac, char **av);
int							print_status(t_phil *phil, char *action);
void						eat(t_phil *phil);
void						start_simulation(t_phil **phils);
void						ft_strlcat(char *dst, const char *src, int len_dst);
#endif
