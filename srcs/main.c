/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:15:31 by rgero             #+#    #+#             */
/*   Updated: 2020/02/19 18:17:00 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_key(int key, t_fdf *data)
{
    if (126 == key)
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
	else if (12 == key)
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
	else if (53 == key)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit (0);
	}
	if (key >= 0 && key < 14)
		ft_rotate(data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	ft_draw(data);
    return (0);
}

/*
** button 
** 1 - left
** 2 - right
** 5 - top
** 4 - down
*/

int ft_mouse(int button, int x, int y, t_fdf *data)
{
    if (5 == button)
		data->z_size += 1;
    else if (4 == button)
		data->z_size -= 1;
	if (x > 0 && x < 1000 && y > 0 && y < 1000)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		ft_draw(data);
	}
	return (0);
}
/*
void	ft_print_tab(t_fdf *data)
{
	int	h;
	int	w;

	h = 0;
	while (h < data->height)
	{
		w = 0;
		while (w < data->width)
		{
			ft_putnbr(data->in_tab[h][w]);
			ft_putchar(' ');
			w++;
		}
		write(1, "\n", 1);
		h++;
	}
	h = 0;
	while (h < data->height)
	{
		w = 0;
		while (w < data->width)
		{
			printf("%.3f*", data->tab[h][w].pixel[0]);
			printf("%.3f*", data->tab[h][w].pixel[1]);
			printf("%.3f*", data->tab[h][w].pixel[2]);
			printf("%.3f ", data->tab[h][w].pixel[3]);
			w++;
		}
		printf("\n");
		h++;
	}
}
*/

int			main(int argc, char **argv)
{
	int		fd;
	t_fdf	*data;

	if (argc == 2 || argc == 4)
	{
		fd = open(argv[1], O_RDONLY);
		data = (t_fdf*)malloc(sizeof(t_fdf));
		if (fd > 0 && data)
		{
			ft_read_argv(data, argc, argv);
			ft_read(fd, &data);
			if (data->height <= 0)
				ft_putendl("error");
			else
			{
				//ft_print_tab(data);
				data->mlx_ptr = mlx_init();
				data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "fdf");
				ft_draw(data);
				mlx_key_hook(data->win_ptr, ft_key, data);
				mlx_mouse_hook(data->win_ptr, ft_mouse, data);
				mlx_loop(data->mlx_ptr);
			}
		}
		else
			ft_putendl("error");
	}
	else
		ft_putendl("usage: ./fdf <filename>");
	return (0);
}
