/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <rgero@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:16:01 by rgero             #+#    #+#             */
/*   Updated: 2020/02/07 16:46:23 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# define BUFF_SIZE 546

typedef struct		s_link
{
	unsigned char	letter;
	unsigned char	bit;
	struct s_link	*left;
	struct s_link	*right;
	struct s_link	*up;
	struct s_link	*down;
	struct s_link	*root_top;
	struct s_link	*root_side;
}					t_link;

typedef struct		s_stack
{
	struct s_link	*link;
	struct s_stack	*next;
}					t_stack;

#endif
