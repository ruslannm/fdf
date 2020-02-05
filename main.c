/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:15:31 by rgero             #+#    #+#             */
/*   Updated: 2020/02/05 18:46:31 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_square_len(int nb, t_list *income)
{
	int		ret;

	while (!(ret = ft_sqrt(nb)))
		nb++;
	if (ret < 4)
		while (income)
		{
			if (ft_size_tetra((char *)income->content) > ret)
				ret = ft_size_tetra((char *)income->content);
			income = income->next;
		}
	return (ret);
}

int			ft_read(int fd, t_list **income, char *str, int i)
{
	int		err;
	char	tet[17];
	char	*tmp;
	char	*buff_pos;

	err = ft_get_buff(fd, &str);
	if (!err)
	{
		tmp = str;
		while (ft_get_) && !err)
		{
			if (++i % 5 != 4)
			{
				err = ft_check_tetra_line(buff_pos, tmp, &tet[(i % 5) * 4]);
				if ((i + 1) % 5 == 4)
					err = ft_check_tetra(tet, income);
			}
			else if (buff_pos != tmp)
				err = -1;
			tmp = buff_pos + 1;
		}
		free(str);
	}
	return (err == -1 || (i + 2) % 5 != 0 ? -1 : (i + 2) / 5);
}

int			main(int argc, char **argv)
{
	int		fd;
	int		qnt;
	t_list	*income;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		income = NULL;
		if (fd > 0)
		{
			qnt = ft_read(fd, &income, NULL, -1);

			if ((qnt = ft_read(fd, &income, NULL, -1)) < 0)
				ft_putendl("error");
			else
				ft_solution(income, ft_square_len(qnt * 4, income), qnt);
			ft_lstdel(&income, &ft_del);
			close(fd);
		}
		else
			ft_putendl("error");
	}
	else
		ft_putendl("usage: ./fdf <filename>");
	return (0);
}
