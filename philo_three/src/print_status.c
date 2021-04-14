/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:14:47 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/14 12:15:32 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_three.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void		ft_strlcat(char *dst, const char *src, int len_dst)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (i < len_dst && src[j] != '\0')
	{
		dst[i++] = src[j++];
	}
	dst[i] = '\0';
}

int			print_status(t_phil *phil, char *action)
{
	char	buf[LEN_BUF];
	char	*time;

	buf[0] = '\0';
	if (phil->state->death)
		return (0);
	time = ft_itoa(time_since(phil->state->start_time));
	ft_strlcat(buf, time, LEN_BUF);
	free(time);
	ft_strlcat(buf, " ", LEN_BUF);
	ft_strlcat(buf, phil->id, LEN_BUF);
	ft_strlcat(buf, " ", LEN_BUF);
	ft_strlcat(buf, action, LEN_BUF);
	ft_strlcat(buf, "\n", LEN_BUF);
	 if (!phil->state->death)
		write(1, buf, ft_strlen(buf));
	return (1);
}
