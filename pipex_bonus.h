/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:39:59 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/12 10:39:47 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

typedef struct s_dlist
{
	struct s_dlist	*pre;
    char    **cmd;
	struct s_dlist	*next;
}					t_dlist;

//ft_dlist_functions2
t_dlist	*create_dlist(char **cmd);
t_dlist	*add_front_dlist(t_dlist *list, t_dlist *node);
t_dlist	*add_last_dlist(t_dlist *list, t_dlist *node);
t_dlist	*get_head(t_dlist *node);
t_dlist	*get_tail(t_dlist *node);
//ft_dlist_functions1
t_dlist	*del_node(t_dlist **list);
t_dlist	*del_head_tail(t_dlist **node);
t_dlist	*get_node( t_dlist *list, int index);
int	get_index(t_dlist *list, t_dlist *node);
int	dlistsize(t_dlist *lst);
//ft_dlist_functions3
void	free_stack(t_dlist **stack);
void	ft_free(char **matrix);
void	print_list(t_dlist *list); //for later removal
//utils
size_t	ft_strlen_d(char **s);
char	*ft_strtrim_start(char const *s1, char const *set);

//check_cmd
char **check_cmd_path(char *cmd_arg, char **envp);
char	*get_env_path(char **envp);
char	**get_directories(char *path_env);
char	*check_cmd_exist(char **cmd, char *path_env);

//pipex
void	exit_pipex(t_dlist **list, int fd1, int fd2);
void	print_result(char **result);

//execute_cmd
void    exceute_cmd_in(char **cmd,t_dlist **list, int infile, int *pipe_fd);
void    exceute_cmd_out(char **cmd,t_dlist **list, char *outfile,int *pipe_fd);
void    exceute_cmd(char **cmd,t_dlist **list,int *pipe_fd);
void pipex_multi(t_dlist *list, char *infile, char *outfile);
#endif