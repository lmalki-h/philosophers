/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 09:56:41 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/09 09:58:37 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		ft_usleep(size_t time)
{
	size_t	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < time)
		usleep(100);
}
