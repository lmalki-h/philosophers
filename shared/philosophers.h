/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 09:56:56 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/12 19:49:18 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <limits.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <pthread.h>
# define SUCCESS 0
# define FAILURE 1
# define FIRST 0
# define SECOND 1
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define TAKE_FORKS "takes forks"
# define DEAD "died"
# define ONE_MICROSECOND 1000
# define DEATH 42
# define FINISHED 21
# define NB_MIN_ARG 5
# define NB_MAX_ARG 6

size_t				get_time_in_ms(void);
int					ft_atoi(char *str);
char				*ft_itoa(long int n);
void				ft_usleep(size_t time);
int					time_since(size_t time_in_ms);
void				*ft_calloc(size_t count, size_t size);
#endif
