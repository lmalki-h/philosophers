/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmalki-h <lmalki-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 09:56:36 by lmalki-h          #+#    #+#             */
/*   Updated: 2021/04/13 13:42:01 by lmalki-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t		get_size(long int n)
{
	size_t	size;

	size = 0;
	if (n == 0)
	{
		size = 1;
	}
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static	int			ft_isnegative(long int n)
{
	int		sign;

	sign = 0;
	if (n < 0)
		sign = 1;
	return (sign);
}

void				*ft_calloc(size_t count, size_t size)
{
	void			*ret;
	unsigned char	*s;
	size_t			i;

	if ((ret = (void *)malloc(count * size)) == NULL)
		return (NULL);
	i = 0;
	s = (unsigned char *)ret;
	while (i < count)
	{
		s[i] = 0;
		i++;
	}
	return (ret);
}

char				*ft_itoa(long int n)
{
	int			sign;
	int			size;
	char		*ret;
	long int	num;

	num = n;
	if ((sign = ft_isnegative(num)) == 1)
		num *= -1;
	size = get_size(num);
	if ((ret = ft_calloc((size + sign + 1), sizeof(char))) == NULL)
		return (NULL);
	if (num == 0)
		ret[0] = '0';
	else
	{
		while (num > 0)
		{
			ret[size + sign - 1] = (num % 10) + '0';
			num /= 10;
			size--;
		}
		if (sign)
			ret[0] = '-';
	}
	return (ret);
}
