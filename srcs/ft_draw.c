/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:26:07 by rgero             #+#    #+#             */
/*   Updated: 2020/02/18 19:05:10 by rgero            ###   ########.fr       */
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

float	ft_get_mulmatrix(float angle, float a, float b, int sign)
{
	float	ret;

	ret = cos(angle) * a + sign * sin(angle) * b;
	return (ret);
}


void	ft_rotate(t_fdf *data)
{
	int		i;
	int		j;

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
				data->x_angle = 0;
			}
			if (data->y_angle)
			{
				data->tab[i][j].pixel[0] = ft_get_mulmatrix(data->y_angle, data->tab[i][j].pixel[0], data->tab[i][j].pixel[2], 1);
				data->tab[i][j].pixel[2] = ft_get_mulmatrix(data->y_angle, data->tab[i][j].pixel[2], data->tab[i][j].pixel[0], -1);
				data->y_angle = 0;
			}
			if (data->z_angle)
			{
				data->tab[i][j].pixel[0] = ft_get_mulmatrix(data->z_angle, data->tab[i][j].pixel[0], data->tab[i][j].pixel[1], -1);
				data->tab[i][j].pixel[2] = ft_get_mulmatrix(data->z_angle, data->tab[i][j].pixel[1], data->tab[i][j].pixel[0], 1);
				data->z_angle = 0;
			}


/*			if (data->y_angle)
			{
				data->tab[i][j].pixel[0] = cos(data->y_angle) * data->tab[i][j].pixel[0] +\
				sin(data->x_angle) * data->tab[i][j].pixel[2];
				data->tab[i][j].pixel[2] = sin(data->x_angle) * data->tab[i][j].pixel[1] +\
				cos(data->x_angle) * data->tab[i][j].pixel[2];
				data->y_angle = 0;
			}
			if (data->z_angle)
			{
				data->tab[i][j].pixel[1] = cos(data->x_angle) * data->tab[i][j].pixel[1] -\
				sin(data->x_angle) * data->tab[i][j].pixel[2];
				data->tab[i][j].pixel[2] = sin(data->x_angle) * data->tab[i][j].pixel[1] +\
				cos(data->x_angle) * data->tab[i][j].pixel[2];
				data->z_angle = 0;
			}
*/

			j++;
		}
		i++;
	}
}

void ft_projection1(t_fdf *data, float *h, float *w, int z)
{
	*h = (*h + *w) * sin(0.8) - z + data->height_shift;
	*w = (*w - *h) * cos(0.8) + data->width_shift;
	
//	*h = (*h + *w) * sin(0.6) - z + shift/2;
//	*w = (*w - *h) * cos(0.6) + shift;
}

void ft_projection(t_fdf *data, float *h, float *w, int z)
{
	float a[3];
	float c[3];

	a[0] = *h;
	a[1] = *w;
	a[2] = (float)z;
	c[0] = (a[0] * sqrt(3) - a[2] * sqrt(3)) / sqrt(6);
	c[1] = (a[0] + 2 * a[1] + a[2]) / sqrt(6);
	c[2] = (a[0] * sqrt(2) - a[1] * sqrt(2) + a[2] * sqrt(2)) / sqrt(6);
	*h = c[0];
	*w = c[1];
	data->x_angle = 0;
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
/*
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
*/

void	ft_get_pixel(t_fdf *data, int *point, float *pixel1, int type)
{
	if (-1 == type)
	{
		pixel1[0] = data->tab[point[0]][point[1]].pixel[0];
		pixel1[1] = data->tab[point[0]][point[1]].pixel[1];
		pixel1[2] = data->tab[point[0]][point[1]].pixel[2];
	}
	else if (0 == type)
	{
		pixel1[0] = data->tab[point[0] + 1][point[1]].pixel[0];
		pixel1[1] = data->tab[point[0]][point[1]].pixel[1];
		pixel1[2] = data->tab[point[0]][point[1]].pixel[2];
	}
	else if (1 == type)
	{
		pixel1[0] = data->tab[point[0]][point[1]].pixel[0];
		pixel1[1] = data->tab[point[0]][point[1] + 1].pixel[1];
		pixel1[2] = data->tab[point[0]][point[1]].pixel[2];
	}
}

void	ft_draw(t_fdf *data)
{
	float	pixel[4][3];
	int		point[2];

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