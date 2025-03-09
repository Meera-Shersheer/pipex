/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:00:32 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/09 22:05:15 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(int argc, char **argv, char **envp)
{
	char **cmd1;
	char **cmd2;
	int pipefd[2];
	
	pipe(pipefd);
	cmd1 = NULL;
	cmd2 = NULL;
	if (argc != 5)
	{
		ft_printf("Error, the number of arguments is not correct\n");
		exit(1);
	}
	if (access(argv[1], F_OK | R_OK) != 0)
		exit_program(cmd1, cmd2, -1, -1);
		
	//check commands
	// work through the envp and the split
	cmd1 = check_cmd_path(argv[2], envp);
	cmd2 = check_cmd_path(argv[3], envp);

	// print_result(cmd1);
	// print_result(cmd2);
	
	if (access(argv[4], F_OK) != 0)
		open(argv[4], O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (access(argv[4], W_OK) != 0)
		exit_program(cmd1, cmd2, -1, -1);

	pipex(cmd1, cmd2, argv[1], argv[4]);
	//exceute_cmd_in(cmd1, argv[1], pipefd);
	//exceute_command();
	
	if (cmd1 != NULL)
		ft_free(cmd1);
	if (cmd2 != NULL)
		ft_free(cmd2);	
	// printf("success :) \n");
	return 0;
}

void	exit_program(char **ptr1, char **ptr2, int fd1, int fd2)
{
	if (ptr1 != NULL)
		ft_free(ptr1);
	if (ptr2 != NULL)
		ft_free(ptr2);
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	perror("Error");
	exit(1);
}

void	print_result(char **result)
{
	printf("result: ");
	if (result == NULL)
	{
		printf("NULL\n");
		return ;
	}
	for (int i = 0; result[i]; i++)
	{
		printf("\"%s\" ", result[i]);
	}
	printf("\n");
}