/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:15:31 by rgero             #+#    #+#             */
/*   Updated: 2020/02/20 16:32:05 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** rotation
** 12 - q
** 0 - a
** 13 - w
** 1 - s
** 14 - e
** 2 - d
*/

void	ft_key_angle(int key, t_fdf *data)
{
	if (12 == key)
		data->x_angle += 1;
	else if (0 == key)
		data->x_angle -= 1;
	else if (13 == key)
		data->y_angle += 1;
	else if (1 == key)
		data->y_angle -= 1;
	else if (14 == key)
		data->z_angle += 1;
	else if (2 == key)
		data->z_angle -= 1;
}

int		ft_key(int key, t_fdf *data)
{
	if (!(53 == key || (122 < key && 127 > key) || 69 == key || 78 == key
		|| (0 <= key && 3 > key) || (11 < key && 15 > key)))
		return (0);
	if (53 == key)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	else if (126 == key)
		data->height_shift -= 10;
	else if (125 == key)
		data->height_shift += 10;
	if (123 == key)
		data->width_shift -= 10;
	else if (124 == key)
		data->width_shift += 10;
	else if (69 == key)
		data->case_size += 5;
	else if (78 == key)
		data->case_size -= 5;
	else
		ft_key_angle(key, data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	ft_draw(data);
	return (0);
}

/*
** button
** 1 - left
** 2 - right
** change size Z
** 5 - top
** 4 - down
*/

int		ft_mouse(int button, int x, int y, t_fdf *data)
{
	if (5 == button)
		data->z_size += 1;
	else if (4 == button)
		data->z_size -= 1;
	if ((4 == button || 5 == button) && x >= 0 && y >= 0)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		ft_draw(data);
	}
	return (0);
}

void	ft_put_windows(t_fdf *data)
{
	data->mlx_ptr = mlx_init();
	data->leg_ptr = mlx_new_window(data->mlx_ptr, 500, 500, "fdf legend");
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "fdf:");
	ft_draw(data);
	mlx_key_hook(data->win_ptr, ft_key, data);
	mlx_mouse_hook(data->win_ptr, ft_mouse, data);
	mlx_loop(data->mlx_ptr);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_fdf	*data;

	if (argc == 2 || argc == 4)
	{
		fd = open(argv[1], O_RDONLY);
		data = ft_data_ini();
		if (fd > 0 && data)
		{
			ft_read_argv(data, argc, argv);
			if (-1 == ft_read(fd, &data, NULL, 0))
				ft_putendl("usage: ./fdf <filename> [case_size z_size]");
			else if (data->height <= 0)
				ft_putendl("error");
			else
				ft_put_windows(data);
		}
		else
			ft_putendl("error");
		ft_data_delete(data);
	}
	else
		ft_putendl("usage: ./fdf <filename> [case_size z_size]");
	return (0);
}
