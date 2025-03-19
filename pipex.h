/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:39:59 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/19 20:59:09 by mshershe         ###   ########.fr       */
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
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

size_t	ft_strlen_d(char **s);
char	*ft_strtrim_start(char const *s1, char const *set);
void	ft_free(char **matrix);
char	**check_cmd_path(char **cmd, char **envp);
char	*get_env_path(char **envp);
char	**get_directories(char **cmd, char *path_env);
char	*check_cmd_exist(char **cmd, char *path_env);
void	exit_program(char **ptr, int fd1, int fd2);
void	exit_program_leak(char **ptr1, int fd1, int fd2);
void	exit_program_wo_e(char **ptr1, int fd1, int fd2);
/*void	print_result(char **result);*/
void	wrong_n_arguments(int n_arg);
char	*free_norm(char **ptr, char *ret);
void	exceute_cmd_in(char **argv, char **envp, int *pipe_fd);
void	exceute_cmd_out(char **argv, char **envp, int *pipe_fd);
void	pipex(char **argv, char **envp);
char	**command_matrix(char *argv);
void	error_norm(char *text);
void	dupfd(int oldfd, int newfd);
#endif