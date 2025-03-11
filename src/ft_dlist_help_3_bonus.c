/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_help_3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:33:37 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/11 15:24:42 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	free_stack(t_dlist **stack)
{
	t_dlist	*temp;

	if (!stack || !(*stack))
		return ;
	*stack = get_head(*stack);
	while (*stack != NULL)
	{
		ft_free((*stack)->cmd);
		temp = (*stack)->next;
		free (*stack);
		*stack = temp;
	}
	*stack = NULL;
	stack = NULL;
}

void	ft_free(char **matrix)
{
	size_t	row;

	row = 0;
	if (!matrix)
		return ;
	if (!(*matrix))
		return (free(matrix));
	while (row < ft_strlen_d(matrix))
	{
		free (matrix[row]);
		row++;
	}
	free (matrix);
}

//edit
void	print_list(t_dlist *list) 
{
	//t_dlist *head = get_head (list);
	t_dlist *head = list;
	if (head == NULL)
	{
		printf("nill\n");
		return;
	}
	while (head != NULL)
	{
		print_result(list->cmd);
		head = head->next;
	}
}
