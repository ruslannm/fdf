/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:00:01 by rgero             #+#    #+#             */
/*   Updated: 2020/02/19 14:38:50 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_read_argv(t_fdf *data, int argc, char **argv)
{
    if (4 == argc)
    {
        data->case_size = ft_atoi(argv[2]);
        data->z_size = ft_atoi(argv[3]);
    }
    else
    {
        data->case_size = 20;
        data->z_size = 1;
    }
    data->height_shift = 150;
    data->width_shift = 150;
    data->x_angle = 0.0;
    data->y_angle = 0.0;
    data->z_angle = 0.0;
};