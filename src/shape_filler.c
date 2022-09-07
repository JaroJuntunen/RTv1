/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_filler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:40:57 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/07 19:22:59 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	fill_shape(t_rtv *rtv, char *line, int i)
{
	char	**line_arg;

	line_arg = ft_strsplit(line, ' ');
	if (line_arg == NULL)
		parser_error_handler(1);
	if (strcmp(line_arg[0], "sphere") == 0)
		fill_sphere(rtv, line_arg, i);
	else if (strcmp(line_arg[0], "plane") == 0)
		fill_plane(rtv, line_arg, i);
	else if (strcmp(line_arg[0], "cylinder") == 0)
		fill_cylinder(rtv, line_arg, i);
	else if (strcmp(line_arg[0], "cone") == 0)
		fill_cone(rtv, line_arg, i);
	else if (strcmp(line_arg[0], "light") == 0)
		if (is_it_light(line_arg) == 1)
			rtv->light.pos = get_pos(line_arg[1]);
	if (strcmp(line_arg[0], "camera") == 0)
	{
		fill_camera_arguments(rtv, line_arg);
	}
	ft_arrdel(line_arg);
}

t_vector	get_pos(char *line_arg_pos)
{
	t_vector	pos;
	char		**positions;

	positions = ft_strsplit(line_arg_pos, '.');
	pos.x = ft_atof(positions[0]);
	pos.y = ft_atof(positions[1]);
	pos.z = ft_atof(positions[2]);
	ft_arrdel(positions);
	return (pos);
}
