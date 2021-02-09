/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:56:13 by ctycho            #+#    #+#             */
/*   Updated: 2021/02/08 12:43:29 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

int			get_next_line(char **line);
char		*strdup_till_null(char *s);
size_t		ft_strlen_1(const char *s);
char		*ft_join_str(char *s1, char *s2);
char		*find_null(char *remainder);
int			check_end(char *s);

#endif
