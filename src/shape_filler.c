/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_filler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:40:57 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/07 17:14:32 by jjuntune         ###   ########.fr       */
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

double	get_desimal_div(int count)
{
	double	ret;

	ret = 1.0;
	while (count != 0)
	{
		ret *= 10;
		count--;
	}
	return (ret);
}

double	get_shape_desimals(char *line_arg_r)
{
	int		i;
	int		count;
	double	r;
	double	negative;

	negative = 1.0f;
	r = 0.0;
	i = 0;
	count = 1;
	if (line_arg_r[i] == '-')
	{
		negative = -1.0f;
		i++;
	}
	while (line_arg_r[i] >= '0' && line_arg_r[i] <= '9')
	{
		r += ((double)line_arg_r[i] - '0');
		if ((double)line_arg_r[++i] >= '0' && (double)line_arg_r[i] <= '9')
			r *= 10.0;
	}
	if (line_arg_r[i++] == ',')
		while (line_arg_r[i] >= '0' && line_arg_r[i] <= '9')
			r += ((double)line_arg_r[i++] - '0') / get_desimal_div(count++);
	return (r * (double)negative);
}

t_vector	get_pos(char *line_arg_pos)
{
	t_vector	pos;
	char		**positions;

	positions = ft_strsplit(line_arg_pos, '.');
	pos.x = get_shape_desimals(positions[0]);
	pos.y = get_shape_desimals(positions[1]);
	pos.z = get_shape_desimals(positions[2]);
	ft_arrdel(positions);
	return (pos);
}
