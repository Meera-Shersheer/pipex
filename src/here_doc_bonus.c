/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:19:51 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/18 06:48:31 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char *here_doc(char *limiter, t_dlist *list, char *outfile)
{
	int hdoc_fd[dlistsize(list)][2];
	int id;
	int pid;
	char *infile;
	int j;
	int status;
	
	 set_pipes(list, hdoc_fd);
	pid = fork();
	if(pid == -1)
		exit_pipes(&list, hdoc_fd, dlistsize(list) - 1 , 1);
	else if (pid == 0)
		infile = read_stdin(hdoc_fd[0], limiter);
	else
	{
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) != 0 && WEXITSTATUS(status) != 1)
			exit_pipes(&list, hdoc_fd, dlistsize(list) - 1 , 1);
		printf("pased first point\n");	
		
		////////////////////////////// function1 
		// get stuck here
			while (list)
			{
				j = get_index(get_head(list), list);
				id = fork();
				if(id == -1)
					exit_pipes(&list, hdoc_fd, dlistsize(list) - 1 , 1);
				else if (id == 0)
				{
					printf("pased second point\n");	
					child_process_here(list, hdoc_fd, outfile);
					return (NULL);
				}
				else
				{
					waitpid(id, &status, 0);
					if (WEXITSTATUS(status) != 0 && WEXITSTATUS(status) != 1)
							exit_pipes(&list, hdoc_fd, dlistsize(list) - 1 , 1);
					close (hdoc_fd[j][0]);
					if (j < dlistsize(list) - 1)
						close (hdoc_fd[j + 1][1]);
					list = list->next;
				}
			}

/////////////////////////////end of the the function1

	
		// close (hdoc_fd[0]);
		// close (hdoc_fd[1]);
		
	}
	return (infile);

}



void	set_fds_here(t_dlist *list, int (*fd)[2],char *outfile)
{
	int j;

	j = get_index(get_head(list), list);
	// if(list->pre == NULL)
	// 	fd[j][0] = check_emptyfile(infile, list, fd, j);
	//check what happen if the heredoc was empty with grep
	if(list->next == NULL)
	{
		fd[j + 1][1] = open(outfile, O_WRONLY | O_TRUNC);
		if (fd[j + 1][1] == -1)
			exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
	}
	if(dup2(fd[j][0], STDIN_FILENO) == -1)
				exit_pipes(&list,fd, dlistsize(list) - 1 , 1);
	if(dup2(fd[j + 1][1], STDOUT_FILENO) == -1)
				exit_pipes(&list, fd, dlistsize(list) - 1 , 1);
}

void	child_process_here(t_dlist *list, int (*fd)[2],char *outfile)
{
	int j;
	
	j = get_index(get_head(list), list);
	close_unused( fd, dlistsize(list) - 1, j);
	set_fds_here(list, fd, outfile);
	execve(list->cmd[0],list->cmd,NULL);
	exit_pipes(&list,fd, dlistsize(list) - 1 , 1);
}

void check_rest(t_dlist **list, int argc, char **argv, char **envp)
{
	int i;

	i = 3;
	if(list == NULL)
		exit_pipex(NULL, NULL);
	while (i < (argc - 1))
	{
		if(*list == NULL)
			*list = create_dlist(check_cmd_path(argv[i], envp));
		else
			*list = add_last_dlist(*list, create_dlist(check_cmd_path(argv[i], envp)));
		i++;
	}
	if (access(argv[argc - 1], F_OK) != 0)
		open(argv[argc - 1], O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (access(argv[argc - 1], W_OK) != 0)
		exit_pipex(list, NULL);
}
char *read_stdin(int *fd, char *limiter)
{
	char *line;
	char *lim;
	int len;
	
	// if(pipe(fd) == -1)
	// 	exit_pipex(NULL, NULL);
	// fd[1] = open("infile",  O_CREAT | O_TRUNC | O_WRONLY, 0644);
	close(fd[0]);
	// if(dup2(fd[1], STDOUT_FILENO) == -1)
	// 	exit_pipex(NULL, NULL);
	lim = ft_strjoin(limiter, "\n");
	if(lim == NULL)
		exit_program_leak(NULL, NULL, fd[0], fd[1]);	
	while(1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if( ft_strlen(line) > ft_strlen(lim))
			len = ft_strlen(line);
		else
			len = ft_strlen(lim);
		if (ft_strncmp(line, lim, len) == 0)
		{
			free(line);
			close(fd[1]);
			return ("infile") ;
		}
		write(fd[1],line, ft_strlen(line) + 1);
		free(line);
	}
	close(fd[1]);
	return ("infile") ;
}
