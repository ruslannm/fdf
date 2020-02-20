/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:00:01 by rgero             #+#    #+#             */
/*   Updated: 2020/02/20 16:35:56 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_del(void *content, size_t len)
{
	ft_bzero(content, len);
	free(content);
}

void	ft_read_argv(t_fdf *data, int argc, char **argv)
{
	if (4 == argc)
	{
		data->case_size = ft_atoi(argv[2]);
		if (!data->case_size)
			data->case_size = 20;
		data->z_size = ft_atoi(argv[3]);
		if (!data->z_size)
			data->z_size = 1;
	}
	else
	{
		data->case_size = 20;
		data->z_size = 1;
	}
	data->height_shift = 150;
	data->width_shift = 150;
	data->x_angle = 0;
	data->y_angle = 0;
	data->z_angle = 0;
	data->height = 0;
}

int		ft_count_words(const char *s, char c)
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

int		ft_read(int fd, t_fdf **data, t_list *income, int ret)
{
	t_list	*tmp;
	char	*str;

	str = NULL;
	while (get_next_line(fd, &str) && 0 == ret)
	{
		if (!str)
			ret = -1;
		else
		{
			(*data)->width = ft_count_words(str, ' ');
			tmp = ft_lstnew(str, ft_strlen(str));
			ft_lstaddback(&income, tmp);
			free(str);
			(*data)->height = (*data)->height + 1;
		}
	}
	if (str)
		free(str);
	if (0 == ret)
		ft_get_in_tab(income, *data);
	close(fd);
	ft_lstdel(&income, &ft_del);
	return (ret);
}
