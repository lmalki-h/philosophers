/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_in_ms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 09:56:46 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/09 09:58:12 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t		get_time_in_ms(void)
{
	struct timeval		time;
	size_t				time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = (size_t)(time.tv_sec * ONE_MICROSECOND) +
	(size_t)(time.tv_usec * 0.001);
	return (time_in_ms);
}
