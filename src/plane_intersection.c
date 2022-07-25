/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:55:13 by jjuntune          #+#    #+#             */
/*   Updated: 2022/07/22 16:00:32 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double	plane_intersection(t_ray *ray, t_rtv *rtv , int count)
{
	double		intersection;
	double		t;
	t_vector	n;
	t_vector	temp;
	double		temp_len;

	n = rtv->shape[count].pos;
	
	intersection = 	m_a_vector(ray->dir, n);
	temp = minus_vectors(ray->start, rtv->shape[count].cyl_h);
	temp_len = sqrt((m_a_vector(temp,temp)));
	temp.x *= -1.0f;
	temp.y *= -1.0f;
	temp.z *= -1.0f;
	temp.x /= temp_len;
	temp.y /= temp_len;
	temp.z /= temp_len;
	temp_len = sqrt((m_a_vector(n,n)));
	n.x /= temp_len;
	n.y /= temp_len;
	n.z /= temp_len;
	t = m_a_vector(temp, n);
	t /= intersection;
	if (intersection != 0)
		return (t);
	return (-1);
}
