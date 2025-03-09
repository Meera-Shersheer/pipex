/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:39:59 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/08 18:03:59 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

# include "./Libft/ft_printf.h"
# include "./Libft/get_next_line_bonus.h"
# include "./Libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h> 


// utils
size_t	ft_strlen_d(char **s);
char	*ft_strtrim_start(char const *s1, char const *set);
void	ft_free(char **matrix);
//check_cmd
char **check_cmd_path(char *cmd_arg, char **envp);
char	*get_env_path(char **envp);
char	**get_directories(char *path_env);
char *check_cmd_exist(char **cmd, char *path_env);
char	**split_command(char *cmd_arg);

//pipex
void exit_program(char **ptr1, char **ptr2);
void	print_result(char **result);


void	handle_quotes(char **cmd_arg);
#endif