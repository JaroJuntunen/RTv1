/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:29:24 by jjuntune          #+#    #+#             */
/*   Updated: 2022/07/26 15:47:02 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static double	calculate_a(t_ray *ray, double m, t_vector	h)
{
	double		temp1;
	double		temp2;
	double		temp3;

	temp1 = m_a_vector(ray->dir, ray->dir);
	temp2 = (m * m_a_vector(multiply_vectors(ray->dir, h), multiply_vectors(ray->dir, h)));
	temp3 = m_a_vector(multiply_vectors(ray->dir, h), multiply_vectors(ray->dir, h));
	return (temp1 - temp2 - temp3);
}

static double	calculate_b(t_ray *ray, double m, t_vector	w, t_vector	h)
{
	double		temp1;
	double		temp2;
	double		temp3;

	temp1 = m_a_vector(ray->dir, w);
	temp2 = m * m_a_vector(ray->dir, h) * m_a_vector(w, h);
	temp3 =m_a_vector(ray->dir, h) * m_a_vector(w, h);
	return (2 * (temp1 - temp2 - temp3));
}

static double	calculate_c(double m, t_vector	w, t_vector	h)
{
	double		temp1;
	double		temp2;
	double		temp3;

	temp1 = m_a_vector(w , w);
	temp2 = m * m_a_vector(w, h) * m_a_vector(w, h);
	temp3 = m_a_vector(w,h) * m_a_vector(w,h);
	return (temp1 - temp2 - temp3);
}

double	cone_intersection(t_ray *ray, t_rtv *rtv , int count)
{
	double		t[2];
	double		m;
	double		temp;
	t_vector	w;
	t_vector	h;
	t_vector	abc;

	w = minus_vectors(ray->start, rtv->shape[count].cyl_h);
	h = minus_vectors(rtv->shape[count].pos, rtv->shape[count].cyl_h);
	m = ((rtv->shape[count].r * rtv->shape[count].r) / m_a_vector(h,h));
	temp = sqrt((m_a_vector(h,h)));
	h.x /= temp;
	h.y /= temp;
	h.z /= temp;
	abc.x = calculate_a(ray, m, h);
	abc.y = calculate_b(ray, m, w, h);
	abc.z = calculate_c(m, w, h);
	if ((abc.y * abc.y) - (4 * abc.x * abc.z) > 0)
	{
		t[0] = (-abc.y + sqrt((abc.y * abc.y) - (4 * abc.x * abc.z))) / (2 * abc.x);
		t[1] = (-abc.y - sqrt((abc.y * abc.y) - (4 * abc.x * abc.z))) / (2 * abc.x);
		
		if (t[0] < t[1] && t[0] > (double)0)
			return (t[0]);
		else
			return (t[1]);
	}
	return (-1);
}