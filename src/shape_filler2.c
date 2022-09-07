/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_filler2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:32:10 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/07 17:14:57 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	fill_sphere(t_rtv *rtv, char **line_arg, int i)
{
	rtv->shape[i].type = "sphere";
	rtv->shape[i].pos = get_pos(line_arg[1]);
	rtv->shape[i].r = get_shape_desimals(line_arg[2]);
	rtv->shape[i].color.value = ft_atoi_base(line_arg[3], 16);
}

void	fill_plane(t_rtv *rtv, char **line_arg, int i)
{
	rtv->shape[i].type = "plane";
	rtv->shape[i].pos = get_pos(line_arg[1]);
	rtv->shape[i].cyl_h = get_pos(line_arg[2]);
	rtv->shape[i].color.value = ft_atoi_base(line_arg[3], 16);
}

void	fill_cone(t_rtv *rtv, char **line_arg, int i)
{
	rtv->shape[i].type = "cone";
	rtv->shape[i].pos = get_pos(line_arg[1]);
	rtv->shape[i].cyl_h = get_pos(line_arg[2]);
	rtv->shape[i].r = get_shape_desimals(line_arg[3]);
	rtv->shape[i].color.value = ft_atoi_base(line_arg[4], 16);
}

void	fill_cylinder(t_rtv *rtv, char **line_arg, int i)
{
	rtv->shape[i].type = "cylinder";
	rtv->shape[i].pos = get_pos(line_arg[1]);
	rtv->shape[i].cyl_h = get_pos(line_arg[2]);
	rtv->shape[i].r = get_shape_desimals(line_arg[3]);
	rtv->shape[i].color.value = ft_atoi_base(line_arg[4], 16);
}

void	fill_camera_arguments(t_rtv *rtv, char **line_arg)
{
	if (check_coordinates_and_directions(line_arg[1]) == 1)
		rtv->camera.pos = get_pos(line_arg[1]);
	if (check_coordinates_and_directions(line_arg[2]) == 1)
		rtv->camera.coi = get_pos(line_arg[2]);
	if (check_coordinates_and_directions(line_arg[3]) == 1)
		rtv->camera.v_up = get_pos(line_arg[3]);
}
