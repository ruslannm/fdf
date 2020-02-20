/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:15:31 by rgero             #+#    #+#             */
/*   Updated: 2020/02/20 18:09:43 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** rotation - numpad
** menu     - enter
*/

void	ft_key_angle(int key, t_fdf *data)
{
	if (89 == key || 92 == key)
		data->x_angle += 1;
	else if (83 == key || 85 == key)
		data->x_angle -= 1;
	else if (91 == key)
		data->y_angle += 1;
	else if (84 == key)
		data->y_angle -= 1;
	else if (88 == key)
		data->z_angle += 1;
	else if (86 == key)
		data->z_angle -= 1;
	else if (36 == key)
		data->menu = (data->menu ? 0 : 1);
	else if (82 == key)
		data->projection = (data->projection ? 0 : 1);
}

int		ft_key(int key, t_fdf *data)
{
	if (!(53 == key || (122 < key && 127 > key) || 69 == key || 78 == key ||
	36 == key || (82 < key && 93 > key && key != 87) || 82 == key))
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

	if (argc != 2)
		ft_err_exit("usage: ./fdf <filename> [case_size z_size]");
	if ((fd = open(argv[1], O_RDONLY | O_DIRECTORY)) > 0)
		ft_err_exit("Incorrect filename");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_err_exit("Incorrect filename");
	data = ft_data_ini();
	if (data)
	{
		ft_read_argv(data, argc, argv);
		if (-1 == ft_read(fd, &data, NULL, 0))
			ft_err_exit("usage: ./fdf <filename> [case_size z_size]");
		else if (data->height <= 0)
			ft_err_exit("Incorrect map");
		else
			ft_put_windows(data);
	}
	else
		ft_err_exit("error");
	ft_data_delete(data);
	return (0);
}
