/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:26:07 by rgero             #+#    #+#             */
/*   Updated: 2020/02/20 16:26:15 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_get_mulmatrix(int angle, float a, float b, int sign)
{
	float	ret;

	ret = cos((float)angle / 10.) * a + sign * sin((float)angle / 10.) * b;
	return (ret);
}

void	ft_rotate_x(t_fdf *data, int i, int j)
{
	data->tab[i][j].pixel[1] = ft_get_mulmatrix(data->x_angle,
								data->tab[i][j].pixel[1],
								data->tab[i][j].pixel[2], -1);
	data->tab[i][j].pixel[2] = ft_get_mulmatrix(data->x_angle,
								data->tab[i][j].pixel[2],
								data->tab[i][j].pixel[1], 1);
}

void	ft_rotate_y(t_fdf *data, int i, int j)
{
	data->tab[i][j].pixel[0] = ft_get_mulmatrix(data->y_angle,
								data->tab[i][j].pixel[0],
								data->tab[i][j].pixel[2], 1);
	data->tab[i][j].pixel[2] = ft_get_mulmatrix(data->y_angle,
								data->tab[i][j].pixel[2],
								data->tab[i][j].pixel[0], -1);
}

void	ft_rotate_z(t_fdf *data, int i, int j)
{
	data->tab[i][j].pixel[0] = ft_get_mulmatrix(data->z_angle,
								data->tab[i][j].pixel[0],
								data->tab[i][j].pixel[1], -1);
	data->tab[i][j].pixel[1] = ft_get_mulmatrix(data->z_angle,
								data->tab[i][j].pixel[1],
								data->tab[i][j].pixel[0], 1);
}
