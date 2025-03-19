/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:00:32 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/19 20:34:45 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**cmd1;
	char	**cmd2;

	cmd1 = NULL;
	cmd2 = NULL;
	if (argc != 5)
		wrong_n_arguments(argc);
	pipex(argv, envp);
	ft_free(cmd1);
	ft_free(cmd2);
	return (0);
}

void	wrong_n_arguments(int n_arg)
{
	if (n_arg > 5)
		ft_printf("Error, too many arguments\n");
	else
		ft_printf("Error, the number of arguments is less than expected\n");
	exit(1);
}

void	exit_program(char **ptr, int fd1, int fd2)
{
	if (ptr != NULL)
		ft_free(ptr);
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	perror("Error");
	exit(1);
}

void	exit_program_leak(char **ptr1, int fd1, int fd2)
{
	if (ptr1 != NULL)
		ft_free(ptr1);
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	write(2, "Error: program couldn't proceed\n", \
	ft_strlen("Error: program couldn't proceed\n"));
	exit(1);
}

void	exit_program_wo_e(char **ptr1, int fd1, int fd2)
{
	if (ptr1 != NULL)
		ft_free(ptr1);
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	exit(1);
}
/*
void	print_result(char **result)
{
	ft_printf("result: ");
	if (result == NULL)
	{
		ft_printf("NULL\n");
		return ;
	}
	for (int i = 0; result[i]; i++)
	{
		ft_printf("\"%s\" ", result[i]);
	}
	ft_printf("\n");
}
*/