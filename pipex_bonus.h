/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:39:59 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/18 07:34:59 by mshershe         ###   ########.fr       */
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
	char    add_trunc;
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
/*void	print_list(t_dlist *list);*/ //for later removal
//utils
size_t	ft_strlen_d(char **s);
char	*ft_strtrim_start(char const *s1, char const *set);

//check_cmd
char **check_cmd_path(char *cmd_arg, char **envp);
char	*get_env_path(char **envp);
char	**get_directories(char **cmd, char *path_env);
char	*check_cmd_exist(char **cmd, char *path_env);

//pipex
void	exit_pipex(t_dlist **list, char **ptr);
char *create_unique_infile();

/*void	print_result(char **result);*/
void wrong_n_arguments(int n_arg);
//execute_cmd
void	set_fds(t_dlist *list, int (*fd)[2], char *infile, char *outfile);
void pipex_multi(t_dlist *list, char *infile, char *outfile);
void set_pipes(t_dlist *list,  int (*fd)[2]);
void	child_process(t_dlist *list, int (*fd)[2], char *infile, char *outfile);
int check_emptyfile(char *infile, t_dlist *list, int (*fd)[2],int j);
//cleanup
void	exit_pipes(t_dlist **list, int (*fd)[2], int i, int j);
void close_unused( int (*fd)[2],int i, int j);
void	exit_pipex(t_dlist **list, char **ptr);
void	exit_program_leak(char **ptr1, char **ptr2, int fd1, int fd2);

void here_doc(char *limiter, t_dlist *list, char *temp_infile);
char *read_stdin(int *fd, char *limiter, int fd_infile);
void check_rest(t_dlist **list, int argc, char **argv, char **envp);
#endif