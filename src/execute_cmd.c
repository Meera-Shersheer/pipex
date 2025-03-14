/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:00:34 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/15 19:45:46 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void    exceute_cmd_in(char **args1,char **args2, char *infile, int *pipe_fd)
{
    int fd;
    pid_t id;
	int status;

	close(pipe_fd[0]);
	fd = check_emptyfile(infile, args1, args2, pipe_fd);
    if (fd == -1)
		exit_program(args1, args2, -1, pipe_fd[1]);
	if (dup2(fd, STDIN_FILENO) == -1)
		exit_program(args1, args2, fd, pipe_fd[1]);
	if((dup2(pipe_fd[1], STDOUT_FILENO)) == -1)
		exit_program(args1, args2, fd, pipe_fd[1]);
    id = fork();
	if(id == -1)
		exit_program(args1, args2, fd, pipe_fd[1]);
    else if(id == 0)
        execve(args1[0], args1, NULL);
    else
	{
		waitpid(id, &status, 0);
		if (WEXITSTATUS(status) != 0 && WEXITSTATUS(status) != 1)
				exit_program(args1, args2, fd, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	close(fd);
}

int check_emptyfile(char *infile, char **args1,char **args2, int *pipe_fd)
{
	int fd;
	char buffer[1];

	fd = open(infile, O_RDONLY);
	if (fd == -1)
		exit_program(args1, args2, -1, pipe_fd[1]);
	if (read(fd, buffer, 1) == 0)
	{
		close(fd);
		fd = open("/dev/null", O_RDONLY); 
		if (fd == -1)
			exit_program(args1, args2, -1, pipe_fd[1]);
	}
	else
	{
		close(fd);
		fd = open(infile, O_RDONLY);
		if (fd == -1)
			exit_program(args1, args2, -1, pipe_fd[1]);
		
	}
	return (fd);
}

void    exceute_cmd_out(char **args1, char **args2, char *outfile,int *pipe_fd)
{
    int fd;
    pid_t id;
	int status;

	close(pipe_fd[1]);
    fd = open(outfile, O_WRONLY | O_TRUNC);
    if (fd == -1)
		exit_program(args1, args2, -1, pipe_fd[0]);	
	if(dup2(fd, STDOUT_FILENO) == -1)
		exit_program(args1, args2, fd, pipe_fd[0]);
	if(dup2(pipe_fd[0], STDIN_FILENO) == -1)
		exit_program(args1, args2, fd, pipe_fd[0]);
    id = fork();
	if(id == -1)
		exit_program(args1, args2, fd, pipe_fd[0]);
    else if(id == 0)
        execve(args1[0], args1, NULL);
    else
	{
		waitpid(id, &status, 0);
		if (WEXITSTATUS(status) != 0)
			exit_program(args1, args2, fd, pipe_fd[1]);
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
	if(id == -1) //double sentences
		exit_program(args1, args2, pipefd[0], pipefd[1]);
    else if(id == 0)
    {
		exceute_cmd_in(args1,args2, infile, pipefd);
	}   
    else
	{
		waitpid(id, &status, 0);
		if (WEXITSTATUS(status) != 0)
			exit_program(args1, args2, pipefd[1], pipefd[1]);
		exceute_cmd_out(args2, args1, outfile, pipefd);
	}
}
