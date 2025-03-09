/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:00:34 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/09 16:43:34 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void    exceute_cmd_in(char *path, char **args, char *infile,int *pipe_fd)
{
    int fd;
    pid_t id;
	int status;

	close(pipe_fd[0]);
    fd = open(infile, O_RDONLY);
    if (fd == -1)
    {
        //exit
    }
	fd = dup2(fd, STDIN_FILENO);
	if(fd == -1)
	{
		//exit
	}
	pipe_fd[1] = dup2(pipe_fd[1], STDOUT_FILENO);
	if(pipe_fd[1] == -1)
	{
		//exit
	}
    id = fork();
	if(id == -1)
	{
		//exit
	}
    else if(id == 0)
        execve(path, args, NULL);
    else
		waitpid(id, &status, 0);
	close(fd);
}

void    exceute_cmd_out(char *path, char **args, char *outfile,int *pipe_fd)
{
    int fd;
    pid_t id;
	int status;

	close(pipe_fd[1]);
    fd = open(outfile, O_WRONLY);
    if (fd == -1)
    {
        //exit
    }
	fd = dup2(fd, STDOUT_FILENO);
	if(fd == -1)
	{
		//exit
	}
	pipe_fd[0] = dup2(pipe_fd[0], STDOUT_FILENO);
	if(pipe_fd[0] == -1)
	{
		//exit
	}
    id = fork();
	if(id == -1)
	{
		//exit
	}
    else if(id == 0)
        execve(path, args, NULL);
    else
		waitpid(id, &status, 0);
	close(fd);
}

pipex(char **args1, char **args2, char *infile, char *outfile)
{	
	pid_t id;
	int status;
	int pipefd[2];
	
	if (pipe(pipefd) == -1)
	{
		//exit
    }
	id = fork();
	if(id == -1)
	{
		//exit
	}
    else if(id == 0)
    {
		exceute_cmd_read(args1[0], args1, infile, pipefd);
	}   
    else
	{
		waitpid(id, &status, 0);
		exceute_cmd_write(args2[0], args2, outfile, pipefd);
	}
	
}
