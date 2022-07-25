/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:29:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/07/25 14:45:13 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double	cone_intersection(t_ray *ray, t_rtv *rtv , int count)
{
	double		m;
	double		temp;
	t_vector	w;
	t_vector	h;
	t_vector	abc;

	h = minus_vectors(rtv_shape[count].pos, rtv_shape[count].cyl_h);
	w = ray->start - rtv_shape[count].cyl_h;
	temp = sqrt((m_a_vector(h,h)));
	h.x /= temp;
	h.y /= temp;
	h.z /= temp;
	m = (rtv_shape[count].r * rtv_shape[count].r) / multiply_vectors(h,h);
	abc.x = (m_a_vector(ray->dir, ray->dir) -m * m_a_vector(multiply_vectors(ray->dir, h), multiply_vectors(ray->dir, h)) - m_a_vector(multiply_vectors(ray->dir, h), multiply_vectors(ray->dir, h)))
	abc.y = (2 * (m_a_vector(ray->dir, w) - m * (m_a_vector(ray->dir, h) * m_a_vector(w, h) - (m_a_vector(ray->dir, h) * m_a_vector(w, h)))))
	abc.z = (m_a_vector(w , w) - m * m_a_vector(w, multiply_vectors(h, h))-  multiply_vectors(h, h));
	if ((abc.y * abc.y) - (4 * abc.x * abc.z) >= 0)
	{
		t[0] = (-abc.y + sqrt((abc.y * abc.y) - (4 * abc.x * abc.z));) / (2 * m_a_vector(w , w));
		t[1] = (-abc.y - sqrt((abc.y * abc.y) - (4 * abc.x * abc.z));) / (2 * m_a_vector(w ,w));
		if (t[0] > t[1] && t[0] > (double)0)
			return (t[0]);
		else
			return (t[1]);
	}
	return (-1);
}

	
}