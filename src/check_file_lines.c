/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:30:42 by jjuntune          #+#    #+#             */
/*   Updated: 2022/08/16 20:06:22 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int	check_sphere(char **line_arg)
{
	int	i;

	i = 0;
	while (line_arg[i] != NULL)
		i++;
	if (i != 4)
		return (-1);
	if (check_coordinates_and_directions(line_arg[1]) == 0)
		return (-1);
	if (check_r(line_arg[2]) == 0)
		return (-1);
	if (check_color(line_arg[3]) == 0)
		return (-1);
	return (1);
}

int	check_plane(char **line_arg)
{
	int	i;

	i = 0;
	while (line_arg[i] != NULL)
		i++;
	if (i != 4)
		return (-1);
	if (check_coordinates_and_directions(line_arg[1]) == 0)
		return (-1);
	if (check_coordinates_and_directions(line_arg[2]) == 0)
		return (-1);
	if (check_color(line_arg[3]) == 0)
		return (-1);
	return (1);
}

int	check_cylinder(char **line_arg)
{
	int	i;

	i = 0;
	while (line_arg[i] != NULL)
		i++;
	if (i != 5)
		return (-1);
	if (check_coordinates_and_directions(line_arg[1]) == 0)
		return (-1);
	if (check_coordinates_and_directions(line_arg[2]) == 0)
		return (-1);
	if (check_r(line_arg[3]) == 0)
		return (-1);
	if (check_color(line_arg[4]) == 0)
		return (-1);
	return (1);
}

int	check_cone(char **line_arg)
{
	int	i;

	i = 0;
	while (line_arg[i] != NULL)
		i++;
	if (i != 5)
		return (-1);
	if (check_coordinates_and_directions(line_arg[1]) == 0)
		return (-1);
	if (check_coordinates_and_directions(line_arg[2]) == 0)
		return (-1);
	if (check_r(line_arg[3]) == 0)
		return (-1);
	if (check_color(line_arg[4]) == 0)
		return (-1);
	return (1);
}

int	is_it_light(char **line_arg)
{
	int	i;

	i = 0;
	while (line_arg[i] != NULL)
		i++;
	if (i != 2)
		return (-1);
	if (strcmp(line_arg[0], "light") != 0)
		return (-1);
	if (check_coordinates_and_directions(line_arg[1]) == 0)
		return (-1);
	return (1);
}