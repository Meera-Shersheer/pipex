/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:00:32 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/15 02:03:56 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
	int i;
	t_dlist *cmd_list;
	
	i = 2;
	cmd_list = NULL;
	if (argc != 5)
		wrong_n_arguments(argc);
	if (access(argv[1], F_OK | R_OK) != 0)
		exit_pipex(&cmd_list, NULL);
	while (i < (argc - 1))
	{
		if(cmd_list == NULL)
			cmd_list = create_dlist(check_cmd_path(argv[i], envp));
		else
			cmd_list = add_last_dlist(cmd_list, create_dlist(check_cmd_path(argv[i], envp)));
		i++;
	}
	if (access(argv[argc - 1], F_OK) != 0)
		open(argv[argc - 1], O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (access(argv[argc - 1], W_OK) != 0)
		exit_pipex(&cmd_list, NULL);
	pipex_multi(cmd_list, argv[1], argv[argc - 1]);
	if (cmd_list != NULL)
		free_stack(&cmd_list);
	return 0;
}

void wrong_n_arguments(int n_arg)
{
	if(n_arg > 5)
		ft_printf("Error, too many arguments\n");
	else
		ft_printf("Error, the number of arguments is less than expected\n");
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
