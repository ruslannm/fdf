/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:10:56 by rgero             #+#    #+#             */
/*   Updated: 2020/02/20 18:08:20 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_put_menu(t_fdf *fdf)
{
	void	*mlx;
	void	*win;

	if (fdf->menu)
	{
		mlx = fdf->mlx_ptr;
		win = fdf->win_ptr;
		mlx_string_put(mlx, win, 115, 20, 0xFFFFFF, "Menu");
		mlx_string_put(mlx, win, 0, 40, 0xFFFFFF, "_________________________");
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