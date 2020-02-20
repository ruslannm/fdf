/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:26:07 by rgero             #+#    #+#             */
/*   Updated: 2020/02/20 16:29:53 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotate(t_fdf *data)
{
	int		i;
	int		j;

	ft_get_tab(data, 1);
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (data->x_angle)
				ft_rotate_x(data, i, j);
			if (data->y_angle)
				ft_rotate_y(data, i, j);
			if (data->z_angle)
				ft_rotate_z(data, i, j);
			j++;
		}
		i++;
	}
}

void	ft_projection(t_fdf *data, float *h, float *w, float z)
{
	float a[3];
	float c[3];

	a[0] = *h;
	a[1] = *w;
	a[2] = z;
	c[0] = (a[0] * sqrt(3) - a[2] * sqrt(3)) / sqrt(6) + data->height_shift;
	c[1] = (a[0] + 2 * a[1] + a[2]) / sqrt(6) + data->width_shift;
	c[2] = (a[0] * sqrt(2) - a[1] * sqrt(2) + a[2] * sqrt(2)) / sqrt(6);
	*h = c[0];
	*w = c[1];
}
