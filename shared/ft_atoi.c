/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 09:56:29 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/09 09:56:31 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int		ft_isblank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
				|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int				ft_atoi(char *str)
{
	int			sign;
	long int	ret;
	long int	i;

	sign = 1;
	ret = 0;
	i = 0;
	while (ft_isblank(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (ret < 0 && sign == -1)
			return (0);
		else if (ret < 0 && sign == 1)
			return (-1);
		ret *= 10;
		ret += (str[i] - '0');
		i++;
	}
	return ((int)(ret * sign));
}
