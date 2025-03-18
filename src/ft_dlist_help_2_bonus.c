/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_help_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:32:29 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/18 07:22:27 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

t_dlist	*create_dlist(char **cmd)
{
	t_dlist	*list;

	list = malloc(sizeof(t_dlist));
	if (list == NULL)
		exit(1);
	else
	{
		list->cmd = cmd;
		list->add_trunc = 0;
		list->pre = NULL;
		list->next = NULL;
	}
	return (list);
}

t_dlist	*add_front_dlist(t_dlist *list, t_dlist *node)
{
	t_dlist	*head;
	t_dlist	*tail;

	head = NULL;
	tail = NULL;
	if (list != NULL)
	{
		head = get_head (list);
		tail = get_tail (node);
		head->pre = tail;
		tail->next = head;
	}
	else
	{
		list = node;
		head = get_head (list);
	}
	return (get_head (head));
}

t_dlist	*add_last_dlist(t_dlist *list, t_dlist *node)
{
	t_dlist	*tail;

	if (node == NULL)
		return (get_head (node));
	tail = get_tail (list);
	if (tail != NULL)
	{
		tail->next = node;
		node -> pre = tail;
	}
	return (get_head (node));
}

t_dlist	*get_head(t_dlist *node)
{
	if (node == NULL)
		return (NULL);
	while (node->pre != NULL)
		node = node->pre;
	return (node);
}

t_dlist	*get_tail(t_dlist *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}
