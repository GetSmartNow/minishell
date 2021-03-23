/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_p2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:09:07 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/23 18:14:07 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			not_valid_arg(t_mini *s, int i)
{
	write(STDERR, "bash: export: `", 15);
	write(STDERR, s->mass3d[0][i], ft_strlen(s->mass3d[0][i]));
	write(STDERR, "': not a valid identifier\n", 26);
	g_sig.exit_status = 1;
}
