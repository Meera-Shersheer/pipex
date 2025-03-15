/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:19:51 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/15 22:31:40 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void here_doc(char *limiter)
{
	int hdoc_fd[2];
	int id;
	int status;
	
	if (pipe(hdoc_fd) == -1)
		exit_pipex(NULL, NULL);
	
	id = fork();
	if(id == -1)
		exit_program_leak(NULL, NULL, hdoc_fd[0], hdoc_fd[1]);
	else if (id == 0)
		read_stdin(hdoc_fd, limiter);
	else
	{
		waitpid(id, &status, 0);
		if (WEXITSTATUS(status) != 0 && WEXITSTATUS(status) != 1)
			exit_program_leak(NULL, NULL, hdoc_fd[0], hdoc_fd[1]);
		close (hdoc_fd[0]);
		close (hdoc_fd[1]);
	}
}

void read_stdin(int *fd, char *limiter)
{
	char *line;
	char *lim;
	int len;
	
	lim = ft_strjoin(limiter, "\n");
	if(lim == NULL)
		exit_program_leak(NULL, NULL, fd[0], fd[1]);
	close(fd[0]);	
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
			break ;
		}
		write(fd[1],line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
}
