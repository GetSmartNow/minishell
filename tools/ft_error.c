/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvernius <mvernius@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:19:26 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/08 19:20:41 by mvernius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				ft_error(char *error, int flag)
{
	if (flag == 1)
	{
		write(1, "bash: ", 6);
		write(1, error, ft_strlen(error));
		write(1, ": No such file or directory\n", 28);
	}
}
