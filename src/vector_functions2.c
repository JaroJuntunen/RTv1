/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjuntune <jjuntune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:56:22 by jjuntune          #+#    #+#             */
/*   Updated: 2022/08/30 19:58:51 by jjuntune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector	multiply_vect_float(t_vector a, double b)
{
	t_vector	new;

	new.x = (a.x * b);
	new.y = (a.y * b);
	new.z = (a.z * b);
	return (new);
}

t_vector	divide_vect_float(t_vector a, double b)
{
	t_vector	new;

	new.x = (a.x / b);
	new.y = (a.y / b);
	new.z = (a.z / b);
	return (new);
}

t_vector	cross_product(t_vector a, t_vector b)
{
	t_vector	new;

	new.x = ((a.y * b.z) - (a.z * b.y));
	new.y = ((a.z * b.x) - (a.x * b.z));
	new.z = ((a.x * b.y) - (a.y * b.x));
	return (new);
}
