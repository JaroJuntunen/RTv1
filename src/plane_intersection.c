/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 20:22:17 by jjuntune          #+#    #+#             */
/*   Updated: 2022/09/12 16:03:12 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	fix_normal(t_ray *ray, t_rtv *rtv, int count)
{
	double	temp;

	temp = sqrt((dot_prdct(rtv->shape[count].cyl_h, rtv->shape[count].cyl_h)));
	rtv->shape[count].cyl_h.x /= temp;
	rtv->shape[count].cyl_h.y /= temp;
	rtv->shape[count].cyl_h.z /= temp;
	temp = dot_prdct(rtv->shape[count].cyl_h, ray->dir);
	if (temp < 0)
	{
		rtv->shape[count].cyl_h.x *= -1.0;
		rtv->shape[count].cyl_h.y *= -1.0;
		rtv->shape[count].cyl_h.z *= -1.0;
	}
}

double	plane_intersection(t_ray *ray, t_rtv *rtv, int count)
{
	double		intersection;
	double		t;
	t_vector	n;
	t_vector	temp;

	fix_normal(ray, rtv, count);
	n = rtv->shape[count].cyl_h;
	intersection = dot_prdct(ray->dir, n);
	temp = minus_vectors(ray->start, rtv->shape[count].pos);
	temp.x *= -1.0;
	temp.y *= -1.0;
	temp.z *= -1.0;
	t = (dot_prdct(temp, n) / intersection);
	rtv->t[0] = t;
	rtv->t[1] = t;
	if (intersection != 0 && t > 0)
		return (t);
	return (-1);
}
