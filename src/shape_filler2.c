/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_filler2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:32:10 by jjuntune          #+#    #+#             */
/*   Updated: 2022/08/23 20:04:29 by jjuntune         ###   ########.fr       */
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
