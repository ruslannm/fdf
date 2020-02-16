/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:15:31 by rgero             #+#    #+#             */
/*   Updated: 2020/02/16 12:19:29 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		*ft_getstr_int(char *str, int width)
{
	char	**str_tab;
	int		i;
	int		*ret;

	str_tab = ft_strsplit(str, ' ');
	ret = (int*)malloc(sizeof(int) * (width + 1));
	i = 0;
	while (i < width)
	{
		ret[i] = ft_atoi(str_tab[i]);
		free(str_tab[i]);
		i++;
		//if ((pointer = ft_strchr(*str_tab, ',')))
	}
	free(str_tab);
	return (ret);
}

/*
**  - only coordinats whithout colors
*/

int		**ft_get_tab(t_list *income, int height, int width)
{
	int		**tab;
	int 	i;
	char	*str;

	tab = (int**)malloc(sizeof(int*) * (height + 1));
	i = 0;
	while (i < height)
	{
		str = income->content;
		income = income->next;
		tab[i++] = ft_getstr_int(str, width);
	}
	tab[i] = 0;
	return (tab);
}

static int		ft_count_words(const char *s, char c)
{
	int	ret;

	ret = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		while (*s != c && *s)
			s++;
		ret++;
		while (*s == c && *s)
			s++;
	}
	return (ret);
}


void		ft_read(int fd, int ***in_tab, int *ret)
{
	t_list	*income;
	t_list	*tmp;
	char	*str;
//	int ret[2];
//	int width;
//	int height;

	str = NULL;
	ret[0] = 0; //width = 0;
	ret[1] = 0; //height = 0;
	income = NULL;
	while (get_next_line(fd, &str))
	{
		ret[1] = ft_count_words(str, ' ');
    	tmp = ft_lstnew(str, ft_strlen(str));
		ft_lstaddback(&income, tmp);
		free(str);
		ret[0] = ret[0] + 1;
	}
	*in_tab = ft_get_tab(income, ret[0], ret[1]); 
}

void	ft_print_tab(int **in_tab, int height, int width)
{
	int	h;
	int	w;

	h = 0;
	while (h < height)
	{
		w = 0;
		while (w < width)
		{
			ft_putnbr(in_tab[h][w++]);
			ft_putchar(' ');
		}
		write(1, "\n", 1);
		h++;
	}
}


int			main(int argc, char **argv)
{
	int		fd;
	int		qnt[2];
//	t_list	*income;
	int		**in_tab;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		in_tab = NULL;
		if (fd > 0)
		{
			ft_read(fd, &in_tab, qnt);

			if (qnt  < 0)
				ft_putendl("error");
			else
			{
				ft_putendl("ok");
				ft_print_tab(in_tab, qnt[0], qnt[1]);
			}
//				ft_solution(income, ft_square_len(qnt * 4, income), qnt);
//			ft_lstdel(&income, &ft_del);

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
