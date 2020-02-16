/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:16:01 by rgero             #+#    #+#             */
/*   Updated: 2020/02/16 15:45:41 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct		s_fdf
{
	int 			**in_tab;
	int				height;
	int				width;
	void			*mlx_ptr;
	void			*win_ptr;
	int				case_size;
	int				z_size;
}					t_fdf;

//void 	ft_bresenham(float h, float w, float h1, float w1, t_fdf *data);
void	ft_read_argv(t_fdf *data, int argc, char **argv);
void	ft_draw(t_fdf *data);

#endif
