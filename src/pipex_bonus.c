/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:00:32 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/18 15:15:41 by mshershe         ###   ########.fr       */
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
	temp_file = NULL;
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
			exit_pipex(NULL, NULL, NULL);
		while (i < (argc - 1))
		{
			if(cmd_list == NULL)
				cmd_list = create_dlist(check_cmd_path(argv[i], envp, temp_file));
			else
				cmd_list = add_last_dlist(cmd_list, \
				create_dlist(check_cmd_path(argv[i], envp, temp_file)));
			i++;
		}
		cmd_list->infile_h = temp_file;
		here_doc(argv[2], cmd_list, temp_file);		
	}
	else
	{
		if (access(argv[1], F_OK | R_OK) != 0)
			exit_pipex(&cmd_list, NULL, &temp_file);
		while (i < (argc - 1))
		{
			if(cmd_list == NULL)
				cmd_list = create_dlist(check_cmd_path(argv[i], envp, temp_file));
			else
				cmd_list = add_last_dlist(cmd_list, create_dlist(check_cmd_path(argv[i], envp, temp_file)));
			i++;
		}
	}
	
		if (access(argv[argc - 1], F_OK) != 0)
			open(argv[argc - 1], O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (access(argv[argc - 1], W_OK) != 0)
			exit_pipex(&cmd_list, NULL, &temp_file);
		if(ft_strncmp(argv[1], "here_doc", len) == 0) 
		{
			cmd_list->add_trunc = 'p';
			pipex_multi(cmd_list,temp_file, argv[argc - 1]);
		}
		else
			pipex_multi(cmd_list, argv[1], argv[argc - 1]);
	if (cmd_list != NULL)
		free_stack(&cmd_list);


	// if (temp_file != NULL && unlink(temp_file) != 0)
	// {
	// 	printf("Iam unlink");
	// //	exit_pipex(NULL, NULL, NULL);
	
	// }
	if (temp_file != NULL) {
		int t = unlink(temp_file);
        if (t != 0) {
            perror("Error unlinking temporary file"); // More detailed error handling
        }
        free(temp_file); 
    }

		
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
	char *num;
	char *prefix;
    int fd;
    int i;
	
	i = 0;
	prefix = ft_strdup("here_doc_");
	if (!prefix)
        exit_program_leak(NULL, NULL, -1, -1);
    while (1)
    {
		num = ft_itoa(i);
        filename = ft_strjoin(prefix, num);
		free (num);
		if (filename == NULL)
		{
			free (prefix);
			exit_program_leak(NULL,NULL,-1,-1);
		}
		fd = open(filename, O_CREAT | O_RDWR | O_EXCL, 0644);
        if (fd > -1)
		{
			close (fd);
			free (prefix);
			return (filename);
		}
        i++;
		free(filename);
    }
	// free(filename);
	free (prefix);
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
