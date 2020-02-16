/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:26:07 by rgero             #+#    #+#             */
/*   Updated: 2020/02/16 15:07:44 by rgero            ###   ########.fr       */
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

void	ft_bresenham(int *pixel, int *pixel1, t_fdf *data)
{
	float	h_step;
	float	w_step;
	int		max;
	int		tmp[3];

	tmp[0] = pixel[0];
	tmp[1] = pixel[1];
	tmp[2] = pixel[2];
	h_step = pixel1[0] - tmp[0];
	w_step = pixel1[1] - tmp[1];
	max = ft_max(h_step, w_step);
	h_step = h_step / max;
	w_step = w_step / max;
	while  ((int)(tmp[0] - pixel1[0]) || (int)(tmp[1] - pixel1[1]))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, tmp[1], tmp[0], 0xffffff);
		tmp[0] += h_step;
		tmp[1] += w_step;
	}
}

void	ft_get_pixel(t_fdf *data, int *pixel, int *pixel1, int type)
{
	if (-1 == type)
	{
		pixel1[2] = data->in_tab[pixel[0]][pixel[1]] * data->z_size;
		pixel1[0] = pixel[0] * data->case_size;
		pixel1[1] = pixel[1] * data->case_size;
	}
	else if (0 == type)
	{
		pixel1[2] = data->in_tab[pixel[0] + 1][pixel[1]] * data->z_size;
		pixel1[0] = (pixel[0] + 1) * data->case_size;
		pixel1[1] = pixel[1] * data->case_size;
	}
	else if (1 == type)
	{
		pixel1[2] = data->in_tab[pixel[0]][pixel[1] + 1] * data->z_size;
		pixel1[0] = pixel[0] * data->case_size;
		pixel1[1] = (pixel[1] + 1) * data->case_size;
	}
}

void	ft_draw(t_fdf *data)
{
	int	pixel[4][3];

	pixel[0][0] = 0;
	while (pixel[0][0] < data->height - 1)
	{
		pixel[0][1] = 0;
//		pixel[0][2] = data->in_tab[pixel[0][0]][pixel[0][1]] * data->z_size;
		while (pixel[0][1] < data->width - 1)
		{
			ft_get_pixel(data, pixel[0], pixel[1], -1);
			ft_get_pixel(data, pixel[0], pixel[2], 0);
			ft_bresenham(pixel[1], pixel[2], data);
			ft_get_pixel(data, pixel[0], pixel[3], 1);
			ft_bresenham(pixel[1], pixel[3], data);
			pixel[0][1] = pixel[0][1] + 1;
		}
		pixel[0][0] = pixel[0][0] + 1;
	}
}