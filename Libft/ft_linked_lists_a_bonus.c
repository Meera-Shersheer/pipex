/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists_a_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:07:06 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 18:55:01 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/** 
 * @brief the ft_lstnew function creates a new node , 
 * assigning NULL to the list variable next.
 * @details t_list is a structure that has two variables 'content' ,
 * and 'next' which is a pointer to the next node. 
 * @see malloc
 * @param[in] content {void *} The content to create
 *  the node with
 * @return {t_list *} the address of the new node or NULL 
 * in case of allocation failure
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node != NULL)
	{
		node->content = content;
		node->next = NULL;
	}
	else
		return (NULL);
	return (node);
}

/** 
 * @brief the ft_lstsize find the length of the list.
 * @details t_list is a structure that has two variables
 *  'content' ,
 * and 'next' which is a pointer to the next node. 
 * @param[in] lst {t_list *}  the address of the head 
 * node of the list 
 * @return {int} returns the length of the list 
 */
int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/** 
 * @brief Adds the node ’new’ at the beginning of the list.
 * @details t_list is a structure that has two variables
 *  'content',and 'next' which is a pointer to the next node. 
 * @param[in] lst {t_list **} The address of a pointer 
 * to the head of a list.
 * @param[in] new {t_list *} The address of a pointer 
 * to the node to be added to the list
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	*lst = new;
	new->next = temp;
}

/** 
 * @brief Adds the node ’new’ at the end of the list.
 * @details t_list is a structure that has two 
 * variables 'content' ,
 * and 'next' which is a pointer to the next node. 
 * @param[in] lst {t_list **} The address of a pointer 
 * to the head of a list.
 * @param[in] new {t_list *} The address of a pointer 
 * to the node to be added to the list
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (new == NULL)
		return ;
	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			end = ft_lstlast(*lst);
			end->next = new;
		}
		else
			*lst = new;
	}
}
