/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:00:32 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/18 07:32:37 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
	int i;
	int len;
	t_dlist *cmd_list;
	char *temp_file;
	
	i = 2;
	cmd_list = NULL;
	if (argc < 5)
		wrong_n_arguments(argc);	
	if(ft_strlen(argv[1]) > ft_strlen("here_doc"))
		len = ft_strlen(argv[1]);
	else
		len = ft_strlen("here_doc");
	if (ft_strncmp(argv[1], "here_doc", len) == 0)
	{
		i = 3;
	//	check_rest(&cmd_list, argc, argv, envp);
		temp_file = create_unique_infile();
		if(temp_file == NULL)
			exit_pipex(NULL, NULL);
		here_doc(argv[2], cmd_list, temp_file);		
	}
	else
	{
		if (access(argv[1], F_OK | R_OK) != 0)
			exit_pipex(&cmd_list, NULL);
	}
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
		if(ft_strncmp(argv[1], "here_doc", len) == 0) 
		{
			cmd_list->add_trunc = 'p';
			pipex_multi(cmd_list,temp_file, argv[argc - 1]);
		}
		else
			pipex_multi(cmd_list, argv[1], argv[argc - 1]);
	if (cmd_list != NULL)
		free_stack(&cmd_list);
	//unlink(temp_file); //cause errors
	//close (temp_file);
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

char *create_unique_infile()
{
    char *filename;
    int fd;
    int i;
	
	i = 0;
    while (1)
    {
        filename = ft_strjoin("here_doc_", ft_itoa(i));
		filename = gnl_strjoin(filename, ".tmp");
		fd = open(filename, O_CREAT | O_RDWR | O_EXCL, 0644);
        if (fd != -1)
		{
			close (fd);
			return (filename);
		}
        i++;
		free(filename);
    }
    return (NULL);
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
