/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:15:31 by rgero             #+#    #+#             */
/*   Updated: 2020/02/07 18:40:51 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		***ft_get_tab(t_list income, int height, int width)
{
	int	tab[2];
	int 	i;

	tab = (int**)malloc(sizeof(int*) * (height + 1));
	i = 0;
	while (i < height)
	{

	}

}

int			ft_read(int fd, t_list **in_tab)
{
	t_list	*income;
	t_list	*tmp;
	char	*str;
	int width;
	int width_temp;
	int height;

	str = NULL;
	width = 0;
	height = 0;
	while (get_next_line(fd, str))
	{
		width_temp = ft_strlen(str);
    	tmp = ft_lstnew(str, width_temp);
		ft_lstaddback(&income, tmp);
		free(str);
		if (width_temp > width)
			width = width_temp;
		height++;
	}
	*in_tab = ft_get_tab(income, height, width); 
	return (0);
}

int			main(int argc, char **argv)
{
	int		fd;
	int		qnt;
//	t_list	*income;
	int		***in_tab;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		in_tab = NULL;
		if (fd > 0)
		{
			qnt = ft_read(fd, &in_tab);

			if ((qnt = ft_read(fd, &income, NULL, -1)) < 0)
				ft_putendl("error");
			else
				ft_solution(income, ft_square_len(qnt * 4, income), qnt);
			ft_lstdel(&income, &ft_del);
*/
			close(fd);
		}
		else
			ft_putendl("error");
	}
	else
		ft_putendl("usage: ./fdf <filename>");
	void		*mlx_ptr;
	void		*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FDF");
//	mlx_pixel_put()
	mlx_loop(mlx_ptr);
	return (0);
}
