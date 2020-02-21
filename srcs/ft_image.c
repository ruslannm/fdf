/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:10:56 by rgero             #+#    #+#             */
/*   Updated: 2020/02/21 15:10:28 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_image(t_fdf *data)
{
	void	*mlx;
	void	*win;

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	if (data->menu)
	{
		mlx = data->mlx_ptr;
		win = data->win_ptr;
		mlx_string_put(mlx, win, 115, 20, 0xFFFFFF, "Menu");
		mlx_string_put(mlx, win, 0, 40, 0xFFFFFF, "_______________________"
												"___");
		mlx_string_put(mlx, win, 10, 80, 0xFFFFFF, "Move: Arrows");
		mlx_string_put(mlx, win, 10, 110, 0xFFFFFF, "Rotate X: NumPad 2/8");
		mlx_string_put(mlx, win, 10, 140, 0xFFFFFF, "Rotate Y: NumPad 4/6");
		mlx_string_put(mlx, win, 10, 170, 0xFFFFFF, "Rotate Z: NumPad 1/3"
													"/7/9");
		mlx_string_put(mlx, win, 10, 200, 0xFFFFFF, "Zoom: NumPad +/-");
		mlx_string_put(mlx, win, 10, 230, 0xFFFFFF,
										"Height: Mouse scroll");
		mlx_string_put(mlx, win, 10, 260, 0xFFFFFF, "Projection: Numpad 0");
		mlx_string_put(mlx, win, 10, 290, 0xFFFFFF, "Hide menu: ENTER");
		mlx_string_put(mlx, win, 10, 320, 0xFFFFFF, "Exit: ESCAPE");
	}
}

t_fdf	*ft_data_ini(void)
{
	t_fdf	*data;

	data = NULL;
	if ((data = (t_fdf*)malloc(sizeof(t_fdf))))
	{
		data->in_tab = NULL;
		data->tab = NULL;
	}
	return (data);
}

void	ft_data_delete(t_fdf *data)
{
	if (data)
	{
		if (data->in_tab)
			free(data->in_tab);
		if (data->tab)
			free(data->tab);
		free(data);
	}
}
