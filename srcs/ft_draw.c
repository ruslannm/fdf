/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:26:07 by rgero             #+#    #+#             */
/*   Updated: 2020/02/21 15:07:01 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_abs(float x)
{
	return ((x < 0 ? -x : x));
}

float	ft_max(float x, float y)
{
	float	x_abs;
	float	y_abs;

	x_abs = ft_abs(x);
	y_abs = ft_abs(y);
	return (x_abs < y_abs ? y_abs : x_abs);
}

void	ft_bresenham(float *pixel, float *pixel1, t_fdf *data)
{
	float	h_step;
	float	w_step;
	float	max;
	float	tmp[4];
	int		color;

	tmp[0] = pixel[0];
	tmp[1] = pixel[1];
	tmp[2] = pixel[2];
	tmp[3] = pixel[3];
	color = (tmp[3] || pixel1[3] ? 0xe80c0c : 0xffffff);
	ft_projection(data, &tmp[0], &tmp[1], tmp[2]);
	ft_projection(data, &pixel1[0], &pixel1[1], pixel1[2]);
	h_step = pixel1[0] - tmp[0];
	w_step = pixel1[1] - tmp[1];
	max = ft_max(h_step, w_step);
	h_step = h_step / max;
	w_step = w_step / max;
	while ((int)(tmp[0] - pixel1[0]) || (int)(tmp[1] - pixel1[1]))
	{
		ft_put_pixel(data, tmp[1], tmp[0], color);
		tmp[0] += h_step;
		tmp[1] += w_step;
	}
}

void	ft_get_pixel(t_fdf *data, int *point, float *pixel1, int type)
{
	if (-1 == type)
	{
		pixel1[0] = data->tab[point[0]][point[1]].pixel[0];
		pixel1[1] = data->tab[point[0]][point[1]].pixel[1];
		pixel1[2] = data->tab[point[0]][point[1]].pixel[2];
		pixel1[3] = data->tab[point[0]][point[1]].pixel[3];
	}
	else if (0 == type)
	{
		pixel1[0] = data->tab[point[0] + 1][point[1]].pixel[0];
		pixel1[1] = data->tab[point[0] + 1][point[1]].pixel[1];
		pixel1[2] = data->tab[point[0] + 1][point[1]].pixel[2];
		pixel1[3] = data->tab[point[0] + 1][point[1]].pixel[3];
	}
	else if (1 == type)
	{
		pixel1[0] = data->tab[point[0]][point[1] + 1].pixel[0];
		pixel1[1] = data->tab[point[0]][point[1] + 1].pixel[1];
		pixel1[2] = data->tab[point[0]][point[1] + 1].pixel[2];
		pixel1[3] = data->tab[point[0]][point[1] + 1].pixel[3];
	}
}

void	ft_draw(t_fdf *data)
{
	float	pixel[4][4];
	int		point[2];

	ft_rotate(data);
	point[0] = 0;
	while (point[0] < data->height)
	{
		point[1] = 0;
		while (point[1] < data->width)
		{
			ft_get_pixel(data, point, pixel[1], -1);
			if (point[0] < data->height - 1)
			{
				ft_get_pixel(data, point, pixel[2], 0);
				ft_bresenham(pixel[1], pixel[2], data);
			}
			if (point[1] < data->width - 1)
			{
				ft_get_pixel(data, point, pixel[3], 1);
				ft_bresenham(pixel[1], pixel[3], data);
			}
			point[1] = point[1] + 1;
		}
		point[0] = point[0] + 1;
	}
}
