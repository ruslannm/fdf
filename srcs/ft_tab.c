/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:00:01 by rgero             #+#    #+#             */
/*   Updated: 2020/02/20 20:34:36 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_in_tab	*ft_getstr_int(char *str, int width)
{
	char		**str_tab;
	int			i;
	t_in_tab	*ret;

	str_tab = ft_strsplit(str, ' ');
	ret = (t_in_tab*)malloc(sizeof(t_in_tab) * (width + 1));
	i = 0;
	while (i < width)
	{
		if (str_tab[i])
		{
			ret[i].pixel[0] = ft_atoi(str_tab[i]);
			free(str_tab[i]);
		}
		else
			ret[i].pixel[0] = 0;
		i++;
	}
	free(str_tab);
	return (ret);
}

void		ft_get_tab(t_fdf *data, int ini)
{
	t_tab	**tab;
	int		i;
	int		j;

	if (0 == ini)
		tab = (t_tab**)malloc(sizeof(t_tab*) * (data->height + 1));
	else
		tab = data->tab;
	i = 0;
	while (i < data->height)
	{
		if (0 == ini)
			tab[i] = (t_tab*)malloc(sizeof(t_tab) * (data->width + 1));
		j = 0;
		while (j < data->width)
		{
			tab[i][j].pixel[0] = (i * data->case_size);
			tab[i][j].pixel[1] = (j * data->case_size);
			tab[i][j].pixel[2] = (data->in_tab[i][j].pixel[0] * data->z_size);
			tab[i][j].pixel[3] = (data->in_tab[i][j].pixel[0]);
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
	t_in_tab	**in_tab;
	int			i;
	char		*str;

	in_tab = (t_in_tab**)malloc(sizeof(t_in_tab*) * (data->height + 1));
	i = 0;
	while (i < data->height)
	{
		str = income->content;
		income = income->next;
		in_tab[i++] = ft_getstr_int(str, data->width);
	}
	in_tab[i] = 0;
	data->in_tab = in_tab;
	ft_get_tab(data, 0);
}
