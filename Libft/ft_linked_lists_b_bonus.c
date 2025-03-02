/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_lists_b_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:07:01 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 18:55:21 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/** 
 * @brief the ft_lstclear function deletes and frees 
 * the given node and every 
 * successor of that node, using the function ’del’ 
 * and free. it sets the pointer to
 * the list to NULL.
 * @details t_list is a structure that has two variables
 *  'content', and 'next' which is a pointer to the next node. 
 * @see free
 * @param[in] lst {t_list **} the address of a pointer to a
 *  node
 * @param[in] del {input: [vpoid *]} The address of the 
 * function used to delete the content of the node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst != NULL && del != NULL)
	{
		while (*lst != NULL)
		{
			temp = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = temp;
		}
		*lst = NULL;
	}
}

/** 
 * @brief the ft_lstdelone function deletes and 
 * frees the given node only,
 *  using the function ’del’ and free. 
 * @details t_list is a structure that has two 
 * variables 'content' ,
 * and 'next' which is a pointer to the next node. 
 * @see free
 * @param[in] lst {t_list *} the address of the node to 
 * free
 * @param[in] del {input: [vpoid *]} The address of the 
 * function used to delete the content of the node.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del != NULL)
		del(lst->content);
	free(lst);
}

/** 
 * @brief the ft_lstlast function returns the last node 
 * of the list.
 * @details t_list is a structure that has two variables 'content' ,
 * and 'next' which is a pointer to the next node. 
 * @param[in] lst {t_list *}  the address of the head node of the list 
 * @return {t_list *} returns the last node of the list 
 */
t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

/** 
 * @brief Iterates the list ’lst’ and applies the function ’f’ on the content of 
 * each node.
 * @details t_list is a structure that has two variables 'content' ,
 * and 'next' which is a pointer to the next node. 
 * @param[in] lst {t_list *}  the address of a node .
 * @param[in] f {input: [void *]} a function used to iterate on the list.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f == NULL)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/** 
 * @brief the ft_lstmap function Iterates the list ’lst’ and applies the function
’f’ on the content of each node until the end of the list. Creating a new list .
 * @details t_list is a structure that has two variables 'content' ,
 * and 'next' which is a pointer to the next node. 
 * @see free | malloc
 * @param[in] lst {t_list *} the address of the node 
 * @param[in] del {input: [vpoid *]} The address of the function which used to 
 * delete the content of a node if needed.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*head;
	void	*before;

	head = NULL;
	if (lst == NULL && f == NULL && del == NULL)
		return (NULL);
	while (lst)
	{
		before = f(lst->content);
		node = ft_lstnew(before);
		if (!node)
		{
			if (before)
				del(before);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	return (head);
}
