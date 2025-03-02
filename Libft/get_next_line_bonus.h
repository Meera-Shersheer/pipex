/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:29:03 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/14 19:14:52 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		gnl_strlen(char *str);
int		gnl_strchr(char *str, char c);
char	*gnl_strdup(char *str);
char	*gnl_strjoin(char *str1, char *str2);
char	*gnl_substr(char *str, int start, int size);
char	*get_next_line(int fd);
char	*comp(char **buffer, int fd, char **line, int *read_bytes);
#endif