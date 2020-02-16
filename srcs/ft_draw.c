/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:26:07 by rgero             #+#    #+#             */
/*   Updated: 2020/02/16 17:06:45 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_abs(int x)
{
	return ((x < 0 ? -x : x));
}

int		ft_max(int x, int y)
{
	int	x_abs;
	int y_abs;

	x_abs = ft_abs(x);
	y_abs = ft_abs(y);
	return (x_abs < y_abs ? y_abs : x_abs);
}

void ft_projection(t_fdf *data, float *h, float *w, int z)
{
	*h = (*h + *w) * sin(0.8) - z + data->height_shift;
	*w = (*w - *h) * cos(0.8) + data->width_shift;
	
//	*h = (*h + *w) * sin(0.6) - z + shift/2;
//	*w = (*w - *h) * cos(0.6) + shift;
}

void	ft_bresenham(float *pixel, float *pixel1, t_fdf *data)
{
	float	h_step;
	float	w_step;
	int		max;
	float	tmp[3];
	int		color;

	tmp[0] = pixel[0];
	tmp[1] = pixel[1];
	tmp[2] = pixel[2];
	color = (tmp[2] || pixel1[2] ? 0xe80c0c : 0xffffff);
	ft_projection(data, &tmp[0], &tmp[1], (int)tmp[2]);
	ft_projection(data, &pixel1[0], &pixel1[1], (int)pixel1[2]);
	h_step = pixel1[0] - tmp[0];
	w_step = pixel1[1] - tmp[1];
	max = ft_max(h_step, w_step);
	h_step = h_step / max;
	w_step = w_step / max;
	while  ((int)(tmp[0] - pixel1[0]) || (int)(tmp[1] - pixel1[1]))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, tmp[1], tmp[0], color);
		tmp[0] += h_step;
		tmp[1] += w_step;
	}
}

void	ft_get_pixel(t_fdf *data, float *pixel, float *pixel1, int type)
{
	if (-1 == type)
	{
		pixel1[2] = data->in_tab[(int)pixel[0]][(int)pixel[1]] * data->z_size;
		pixel1[0] = pixel[0] * data->case_size;
		pixel1[1] = pixel[1] * data->case_size;
	}
	else if (0 == type)
	{
		pixel1[2] = data->in_tab[(int)pixel[0] + 1][(int)pixel[1]] * data->z_size;
		pixel1[0] = (pixel[0] + 1) * data->case_size;
		pixel1[1] = pixel[1] * data->case_size;
	}
	else if (1 == type)
	{
		pixel1[2] = data->in_tab[(int)pixel[0]][(int)pixel[1] + 1] * data->z_size;
		pixel1[0] = pixel[0] * data->case_size;
		pixel1[1] = (pixel[1] + 1) * data->case_size;
	}
}

void	ft_draw(t_fdf *data)
{
	float	pixel[4][3];

	pixel[0][0] = 0;
	while (pixel[0][0] < data->height)
	{
		pixel[0][1] = 0;
//		pixel[0][2] = data->in_tab[pixel[0][0]][pixel[0][1]] * data->z_size;
		while (pixel[0][1] < data->width)
		{
			ft_get_pixel(data, pixel[0], pixel[1], -1);
			if (pixel[0][0] < data->height - 1)
			{
				ft_get_pixel(data, pixel[0], pixel[2], 0);
				ft_bresenham(pixel[1], pixel[2], data);
			}
			if (pixel[0][1] < data->width - 1)
			{
				ft_get_pixel(data, pixel[0], pixel[3], 1);
				ft_bresenham(pixel[1], pixel[3], data);
			}
			pixel[0][1] = pixel[0][1] + 1;
		}
		pixel[0][0] = pixel[0][0] + 1;
	}
}