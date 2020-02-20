/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:26:07 by rgero             #+#    #+#             */
/*   Updated: 2020/02/20 14:49:38 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_get_mulmatrix(int angle, float a, float b, int sign)
{
	float	ret;

	ret = cos((float)angle / 10.) * a + sign * sin((float)angle / 10.) * b;
	return (ret);
}

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
			{
				data->tab[i][j].pixel[1] = ft_get_mulmatrix(data->x_angle, data->tab[i][j].pixel[1], data->tab[i][j].pixel[2], -1);
				data->tab[i][j].pixel[2] = ft_get_mulmatrix(data->x_angle, data->tab[i][j].pixel[2], data->tab[i][j].pixel[1], 1);
			}
			if (data->y_angle)
			{
				data->tab[i][j].pixel[0] = ft_get_mulmatrix(data->y_angle, data->tab[i][j].pixel[0], data->tab[i][j].pixel[2], 1);
				data->tab[i][j].pixel[2] = ft_get_mulmatrix(data->y_angle, data->tab[i][j].pixel[2], data->tab[i][j].pixel[0], -1);
			}
			if (data->z_angle)
			{
				data->tab[i][j].pixel[0] = ft_get_mulmatrix(data->z_angle, data->tab[i][j].pixel[0], data->tab[i][j].pixel[1], -1);
				data->tab[i][j].pixel[1] = ft_get_mulmatrix(data->z_angle, data->tab[i][j].pixel[1], data->tab[i][j].pixel[0], 1);
			}
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
