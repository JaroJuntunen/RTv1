/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lines_arguments.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:59:58 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/20 15:05:22 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	check_coordinates_and_directions(char *arg)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if ((arg[i] <= '9' && arg[i] >= '0' ) || arg[i] == '-')
	{
		while (arg[i] != '\0')
		{
			if ((arg[i] >= '0' && arg[i] <= '9' )
				|| arg[i] == ',' || arg[i] == '-')
				i++;
			else if (arg[i] == '.' && ((arg[i + 1] >= '0' && arg[i + 1] <= '9')
					|| arg[i + 1] == '-'))
			{
				count++;
				i++;
			}
			else
				return (0);
		}
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
			return (0);
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
		if ((arg[i] >= '0' && arg[i] <= '9')
			|| (arg[i] >= 'a' && arg[i] <= 'f') || arg[i] == '-')
			i++;
		else if (arg[i] == 'x')
		{
			i++;
			count++;
		}
		else
			return (0);
	}
	if (count == 1)
		return (1);
	return (0);
}

int	check_camera(char **line_arg)
{
	int	i;

	i = 0;
	while (line_arg[i] != NULL)
		i++;
	if (i != 4)
		return (-1);
	if (strcmp(line_arg[0], "camera") != 0)
		return (-1);
	if (check_coordinates_and_directions(line_arg[1]) == 0)
		return (-1);
	if (check_coordinates_and_directions(line_arg[2]) == 0)
		return (-1);
	if (check_coordinates_and_directions(line_arg[3]) == 0)
		return (-1);
	return (1);
}
