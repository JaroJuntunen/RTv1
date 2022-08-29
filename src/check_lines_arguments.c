/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lines_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:59:58 by jjuntune          #+#    #+#             */
/*   Updated: 2022/08/11 15:52:20 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	check_coordinates_and_directions(char *arg)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (arg[i] != '\0')
	{
		if ((arg[i] >= '0' && arg[i] <= '9' ) || arg[i] == ',' || arg[i] == '-')
			i++;
		else if (arg[i] == '.')
		{
			count++;
			i++;
		}
		else
			return (-1);
	}
	if (count == 2)
		return (1);
	return (0);
}

int	check_r(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i] != '\0')
	{
		if ((arg[i] >= '0' && arg[i] <= '9') || arg[i] == '-')
			i++;
		else if (arg[i] == ',')
		{
			count++;
			i++;
		}
		else
			return (-1);
	}
	if (count < 2)
		return (1);
	return (0);
}

int	check_color(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i] != '\0')
	{
		if ((arg[i] >= '0' && arg[i] <= '9') || (arg[i] >= 'a' && arg[i] <= 'f') || arg[i] == '-')
			i++;
		else if (arg[i] == 'x')
		{
			i++;
			count++;
		}
		else
			return (-1);
	}
	if (count == 1)
		return (1);
	return (0);
}
