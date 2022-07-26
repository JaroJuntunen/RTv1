/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:45:46 by jjuntune          #+#    #+#             */
/*   Updated: 2022/07/26 15:48:48 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"


//	C = Point at the center of the base of the cylinder
//	H = Point at the center of the top of the cylinder
//	r = Cylinder radius
//	P = Point on the cylinder surface
//	
//	L0 = Point on the line
//	h = cylinder sentral acses;

double	cylinder_intersection(t_ray *ray, t_rtv *rtv , int count)
{
	t_vector	h;
	t_vector	w;
	t_vector	abc;
	double		discr;
	double		t[2];
	double		temp;

	w = minus_vectors(ray->start , rtv->shape[count].pos);
	h = minus_vectors(rtv->shape[count].cyl_h, rtv->shape[count].pos); 
	temp = sqrt((m_a_vector(h,h)));
	h.x /= temp;
	h.y /= temp;
	h.z /= temp;
	abc.x = (m_a_vector(ray->dir, ray->dir) - (m_a_vector(ray->dir, h) * m_a_vector(ray->dir, h)));
	abc.y = (2 * (m_a_vector(ray->dir, w) - (m_a_vector(ray->dir, h) * m_a_vector(w, h))));
	abc.z = (m_a_vector(w, w) - (m_a_vector(w, h) * m_a_vector(w, h)) - (rtv->shape[count].r * rtv->shape[count].r));
	discr = ((abc.y * abc.y) - (4 * abc.x * abc.z));
	if (discr >= 0)
	{
		discr = sqrt(discr);
		t[0] = (-abc.y + discr) / (2 * abc.x);
		t[1] = (-abc.y - discr) / (2 * abc.x);
		if (t[0] < t[1] && t[0] > (double)0)
			return (t[0]);
		else
			return (t[1]);
	}
	return (-1);
}
