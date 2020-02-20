/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:16:01 by rgero             #+#    #+#             */
/*   Updated: 2020/02/20 16:26:50 by rgero            ###   ########.fr       */
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

typedef	struct 		s_in_tab
{
	int				pixel[2];
}					t_in_tab;

typedef	struct 		s_tab
{
	float			pixel[4];
}					t_tab;

typedef struct		s_fdf
{
	t_in_tab 		**in_tab;
	t_tab			**tab;
	int				height;
	int				width;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*leg_ptr;
	int				case_size;
	int				z_size;
	int				height_shift;
	int				width_shift;
	int				x_angle;
	int				y_angle;
	int				z_angle;
}					t_fdf;


void	ft_read_argv(t_fdf *data, int argc, char **argv);
int		ft_read(int fd, t_fdf **data, t_list *income, int ret);
void	ft_draw(t_fdf *data);
void	ft_rotate(t_fdf *data);
void	ft_rotate_x(t_fdf *data, int i, int j);
void	ft_rotate_y(t_fdf *data, int i, int j);
void	ft_rotate_z(t_fdf *data, int i, int j);
void	ft_projection(t_fdf *data, float *h, float *w, float z);
void	ft_get_tab(t_fdf *data, int ini);
t_fdf	*ft_data_ini(void);
void	ft_data_delete(t_fdf *data);
void	ft_get_in_tab(t_list *income, t_fdf *data);

#endif
