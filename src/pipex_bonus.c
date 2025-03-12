/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:00:32 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/12 12:44:58 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
	int i;
	t_dlist *cmd_list;
	
	i = 1;
	cmd_list = NULL;
	if (argc < 5)
	{
		ft_printf("Error, the number of arguments is less than expected\n");
		exit(1);
	}
	if (access(argv[1], F_OK | R_OK) != 0)
		exit_pipex(&cmd_list, -1, -1);
		
	// work through the envp and the split
	//creat the list of commnds and check every command
	while (i < (argc - 1))
	{
		if(cmd_list == NULL)
			cmd_list = create_dlist(check_cmd_path(argv[i], envp));
		else
			cmd_list = add_last_dlist(cmd_list, create_dlist(check_cmd_path(argv[i], envp)));
		i++;
	}

	//print_list(cmd_list);
	
	if (access(argv[4], F_OK) != 0)
		open(argv[4], O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (access(argv[4], W_OK) != 0)
		exit_pipex(&cmd_list, -1, -1);
	pipex_multi(cmd_list, argv[1], argv[4]);
	
	if (cmd_list != NULL)
		free_stack(&cmd_list);
	// printf("success :) \n");
	return 0;
}

void	exit_pipex(t_dlist **list, int fd1, int fd2)
{
	if (list != NULL)
		free_stack(list);
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	perror("Error");
	exit(1);
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
