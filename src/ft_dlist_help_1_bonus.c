/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_help_1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:34:54 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/11 15:24:01 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

t_dlist	*del_node(t_dlist **list)
{
	t_dlist	*replace;
	t_dlist	*temp;

	replace = NULL;
	if (list == NULL || *list == NULL)
		return (NULL);
	if ((*list)->pre == NULL || (*list)->next == NULL)
		return (del_head_tail(list));
	temp = (*list)->pre;
	replace = (*list)->next;
	(*list)->next = NULL;
	(*list)->pre = NULL;
	free(*list);
	*list = NULL;
	temp->next = replace;
	replace->pre = temp;
	return (temp);
}

t_dlist	*del_head_tail(t_dlist **node)
/*if ((*node)->pre == NULL) // del head
if((*node) -> next == NULL) // del tail*/
{
	t_dlist	*replace;

	replace = NULL;
	if (node == NULL || *node == NULL)
		return (NULL);
	if ((*node)->pre == NULL)
	{
		replace = (*node)->next;
		if ((*node)->next != NULL)
			(*node)->next = NULL;
		if (replace != NULL )
			replace->pre = NULL;
		free (*node);
		return (replace);
	}
	else if ((*node)-> next == NULL)
	{
		replace = (*node)->pre;
		(*node)->pre = NULL;
		if (replace != NULL)
			replace->next = NULL;
		free (*node);
		return (replace);
	}
	return (NULL);
}

t_dlist	*get_node( t_dlist *list, int index)
{
	int		i;
	t_dlist	*node;

	node = get_head (list);
	i = 0;
	while (i < index)
	{
		node = node->next;
		i++;
	}
	return (node);
}

int	get_index(t_dlist *list, t_dlist *node)
{
	int		i;
	t_dlist	*head;

	i = 0;
	if (list == NULL )
		return (-1);
	head = get_head (list);
	if (node == NULL || head == NULL)
		return (-1);
	while (head != NULL)
	{
		if (head == node)
			return (i);
		if (head->next != NULL)
			head = head->next;
		else
			break ;
		i++;
	}
	return (-1);
}

int	dlistsize(t_dlist *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (0);
	lst = get_head(lst);
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
