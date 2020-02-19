/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 19:26:15 by rgero             #+#    #+#             */
/*   Updated: 2020/02/19 19:40:44 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
