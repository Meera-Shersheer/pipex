/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:39:59 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/19 01:00:56 by mshershe         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>


// utils
size_t	ft_strlen_d(char **s);
char	*ft_strtrim_start(char const *s1, char const *set);
void	ft_free(char **matrix);
//check_cmd
char **check_cmd_path(char *cmd_arg, char **envp);
char	*get_env_path(char **envp);
char	**get_directories(char **cmd, char *path_env);
char	*check_cmd_exist(char **cmd, char *path_env);

//pipex
void exit_program(char **ptr1, char **ptr2, int fd1, int fd2);
void	exit_program_leak(char **ptr1, char **ptr2, int fd1, int fd2);
void exit_program_wo_e(char **ptr1, char **ptr2, int fd1, int fd2);
/*void	print_result(char **result);*/
void wrong_n_arguments(int n_arg);
//execute_cmd
void    exceute_cmd_in(char **args1, char **args2, char *infile, int *pipe_fd);
void    exceute_cmd_out(char **args1, char **args2, char *outfile,int *pipe_fd);
void pipex(char **args1, char **args2, char *infile, char *outfile);
int check_emptyfile(char *infile, char **args1,char **args2, int *pipe_fd);
#endif