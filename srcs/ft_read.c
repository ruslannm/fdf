/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:00:01 by rgero             #+#    #+#             */
/*   Updated: 2020/02/19 15:32:34 by rgero            ###   ########.fr       */
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

void ft_read_argv(t_fdf *data, int argc, char **argv)
{
    if (4 == argc)
    {
        data->case_size = ft_atoi(argv[2]);
        data->z_size = ft_atoi(argv[3]);
    }
    else
    {
        data->case_size = 20;
        data->z_size = 1;
    }
    data->height_shift = 150;
    data->width_shift = 150;
    data->x_angle = 0.1;
    data->y_angle = 0.1;
    data->z_angle = 0.1;
};

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
