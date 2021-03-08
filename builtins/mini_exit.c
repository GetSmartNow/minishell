/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:44:29 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/06 13:43:06 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				mini_exit(char **s)
{
	write(1, s[0], ft_strlen(s[0]));
	write(1, "\n", 1);
	exit (0);
}