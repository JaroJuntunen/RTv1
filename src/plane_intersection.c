/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection->c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:55:13 by jjuntune          #+#    #+#             */
/*   Updated: 2022/08/16 17:08:49 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	fix_normal(t_ray *ray, t_rtv *rtv, int count)
{
	double	temp;

	temp = sqrt((m_a_vector(rtv->shape[count].cyl_h,rtv->shape[count].cyl_h)));
	rtv->shape[count].cyl_h.x /= temp;
	rtv->shape[count].cyl_h.y /= temp;
	rtv->shape[count].cyl_h.z /= temp;
	temp = m_a_vector(rtv->shape[count].cyl_h, ray->dir);
	if (temp < 0)
	{
	rtv->shape[count].cyl_h.x *= -1.0;
	rtv->shape[count].cyl_h.y *= -1.0;
	rtv->shape[count].cyl_h.z *= -1.0;
	}
}

double	plane_intersection(t_ray *ray, t_rtv *rtv , int count)
{
	double		intersection;
	double		t;
	t_vector	n;
	t_vector	temp;

	fix_normal(ray,rtv ,count);
	n = rtv->shape[count].cyl_h;
	intersection = 	m_a_vector(ray->dir, n);
	temp = minus_vectors(ray->start, rtv->shape[count].pos);
	temp.x *= -1.0;
	temp.y *= -1.0;
	temp.z *= -1.0;
	t = (m_a_vector(temp, n) / intersection);
	if (intersection != 0 && t > 0)
		return (t);
	return (-1);
}
