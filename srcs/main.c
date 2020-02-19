/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:15:31 by rgero             #+#    #+#             */
/*   Updated: 2020/02/19 14:50:48 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_key(int key, t_fdf *data)
{
    //int shift;

  //  ft_putnbr(key);
//	write(1, "\n", 1);
    if (126 == key)
		data->height_shift -= 10;
    else if (125 == key)
		data->height_shift += 10;
    if (123 == key)
		data->width_shift -= 10;
    else if (124 == key)
		data->width_shift += 10;
	else if (53 == key)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit (0);
	}
	if (key > 122 && key < 127)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		ft_draw(data);
	}
    return (0);
}

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

void		ft_get_tab(t_fdf *data)
{
	t_tab	**tab;
	int 	i;
	int		j;

	tab = (t_tab**)malloc(sizeof(t_tab*) * (data->height + 1));
	i = 0;
	while (i < data->height)
	{
		tab[i] = (t_tab*)malloc(sizeof(t_tab) * (data->width + 1));
		j = 0;
		while (j < data->width)
		{
			tab[i][j].pixel[0] = (float)(i * data->case_size);
			tab[i][j].pixel[1] = (float)(j * data->case_size);
			tab[i][j].pixel[2] = (float)(data->in_tab[i][j] * data->z_size);
			tab[i][j].pixel[3] = (float)(data->in_tab[i][j] * data->z_size);
			j++;
		}
		i++;
	}
	data->tab = tab;
}


/*
**  - only coordinats whithout colors
*/

void		ft_get_in_tab(t_list *income, t_fdf *data)
{
	int		**in_tab;
	int 	i;
	char	*str;

	in_tab = (int**)malloc(sizeof(int*) * (data->height + 1));
	i = 0;
	while (i < data->height)
	{
		str = income->content;
		income = income->next;
		in_tab[i++] = ft_getstr_int(str, data->width);
	}
	in_tab[i] = 0;
	data->in_tab = in_tab;
	ft_get_tab(data);
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

void		ft_read(int fd, t_fdf **data)
{
	t_list	*income;
	t_list	*tmp;
	char	*str;

	str = NULL;
	(*data)->height = 0;
	income = NULL;
	while (get_next_line(fd, &str))
	{
		(*data)->width = ft_count_words(str, ' ');
    	tmp = ft_lstnew(str, ft_strlen(str));
		ft_lstaddback(&income, tmp);
		free(str);
		(*data)->height = (*data)->height + 1;
	}
	ft_get_in_tab(income, *data); 
	ft_rotate(*data);
	close(fd);
}

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
			ft_putnbr(data->tab[h][w].pixel[0]);
			ft_putchar('*');
			ft_putnbr(data->tab[h][w].pixel[1]);
			ft_putchar('*');
			ft_putnbr(data->tab[h][w].pixel[2]);
			ft_putchar('*');
			ft_putnbr(data->tab[h][w].pixel[3]);
			ft_putchar(' ');
			w++;
		}
		write(1, "\n", 1);
		h++;
	}
}


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
				ft_print_tab(data);
				data->mlx_ptr = mlx_init();
				data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "fdf");
				ft_draw(data);
				mlx_key_hook(data->win_ptr, ft_key, data);
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
