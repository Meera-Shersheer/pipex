/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:00:34 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/11 16:39:56 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"
//enter data to pipe -> writes the pipe
//the input of the pipe is taken from the infile 
void    exceute_cmd_in(char **cmd,t_dlist **list, int infile, int *pipe_fd)
{
    int fd;
    pid_t id;
	int status;

	close(pipe_fd[0]);
    fd = open(infile, O_RDONLY);
    if (fd == -1)
		exit_pipex(list, -1, pipe_fd[1]);
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_pipex(list, fd, pipe_fd[1]);
	if(dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		exit_pipex(list, fd, pipe_fd[1]);
    id = fork();
	if(id == -1)
		exit_pipex(list, fd, pipe_fd[1]);
    else if(id == 0)
        execve(cmd[0], cmd, NULL);
    else
	{
		waitpid(id, &status, 0);
		if (WEXITSTATUS(status) != 0)
			exit_pipex(list, fd, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	close(fd);
}

//take data from the pipe -> read from the pipe
//the output of the pipe is written to the outfile
void    exceute_cmd_out(char **cmd,t_dlist **list, char *outfile,int *pipe_fd)
{
    int fd;
    pid_t id;
	int status;

	close(pipe_fd[1]);
    fd = open(outfile, O_WRONLY);
    if (fd == -1)
		exit_pipex(list, -1, pipe_fd[0]);	
	if(dup2(fd, STDOUT_FILENO) == -1)
		exit_pipex(list, fd, pipe_fd[0]);
	if(dup2(pipe_fd[0], STDIN_FILENO)== -1)
		exit_pipex(list, fd, pipe_fd[0]);
    id = fork();
	if(id == -1)
		exit_pipex(list, fd, pipe_fd[0]);
    else if(id == 0)
        execve(cmd[0], cmd, NULL);
    else
	{
		waitpid(id, &status, 0);
		if (WEXITSTATUS(status) != 0)
			exit_pipex(list, fd, pipe_fd[1]);
	}
	close(pipe_fd[0]);
	close(fd);
}

void pipex(char **args1, char **args2, char *infile, char *outfile)
{	
	pid_t id;
	int status;
	int pipefd[2];
	
	if (pipe(pipefd) == -1)
		exit_program(args1, args2, -1, -1);
	id = fork();
	if(id == -1)
		exit_program(args1, args2, -1, -1);
    else if(id == 0)
    {
		exceute_cmd_in(args1,args2, infile, pipefd);
	}   
    else
	{
		waitpid(id, &status, 0);
		exceute_cmd_out(args2, args1, outfile, pipefd);
	}
	
}
void pipex_multi(t_dlist *list, char *infile, char *outfile)
{	
	pid_t id;
	int n_pipes;
	int status;
	int pipefd[2];
	
	if (pipe(pipefd) == -1)
		exit_pipex(list, -1, -1);
	n_pipes = dlistsize(list);
	id = fork();
	if(id == -1)
		exit_pipex(list, -1, -1);
    else if(id == 0)
    {
		exceute_cmd_in(list->cmd ,&list, infile, pipefd);
		list = list->next;
		while(n_pipes < 0)
		{
			
			n_pipes--;
			list = list->next;
		}
	}   
    else
	{
		waitpid(id, &status, 0);
		exceute_cmd_out(args2, args1, outfile, pipefd);
	}
	
}
