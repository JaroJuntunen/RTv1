/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:35:06 by jjuntune          #+#    #+#             */
/*   Updated: 2022/07/28 16:06:27 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(const char *str, int base)
{
	int	i;
	int	pn;
	int	r;

	pn = 1;
	i = 0;
	r = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		pn = -1;
		i++;
	}
	if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	while ((str[i] <= '9' && str[i] >= '0') || (str[i] >= 'a' && str[i] < ('a' + (base - 10))))
	{
		if (str[i] <= '9' && str[i] >= '0')
		{
			r = r + (str[i] - '0');
			if ((str[i + 1] <= '9' && str[i + 1] >= '0') || (str[i + 1] >= 'a' && str[i + 1] < ('a' + (base - 10))))
				r = r * base;
		}
		else if (str[i] >= 'a' && str[i] < ('a' + (base - 10)))
		{
			r = r + (str[i] - ('a' - 10));
			if ((str[i + 1] <= '9' && str[i + 1] >= '0') || (str[i + 1] >= 'a' && str[i + 1] < ('a' + (base - 10))))
				r = r * base;
		}
		i++;
	}
	return (r * pn);
}