/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:34:18 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/21 20:08:51 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief the function of count_words finds the number of 
 * words in a string separated by the character c
 * @param[in] s {char const *} the string to count words in 
 * @param[in] c {char} the seperator
 * @return {int} the number of words in a string 
 */
static int	count_words(char const *s, char c)
{
	int	nstr;
	int	i;

	nstr = 0;
	i = 0;
	if (s == NULL || *s == '\0')
		return (0);
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nstr++;
			while (s[i] == c && s[i + 1] != '\0')
				i++;
		}
		i++;
	}
	if (s[i - 1] != c)
		nstr++;
	return (nstr);
}

/** 
 * @brief  the words_len function  finds the length of a word
 * @param[in] s {char const *} the string to count words in 
 * @param[in] c {char} the seperator
 * @return {int} the number of letters in a word 
 */
static int	words_len(char const *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL || *s == '\0')
		return (0);
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

/** 
 * @brief the free_s function used to free all the 
 * contents of the sub pointers in ptr and free ptr itself
 * @see free
 * @param[in] ptr {char **} the pointer to free
 * @param[in] l {int} counter
 * @return NULL
 */
static char	**free_s(char **ptr, int l)
{
	if (ptr != NULL)
	{
		while (l >= 0)
		{
			if (ptr[l] != NULL)
				free(ptr[l]);
			l--;
		}
	}
	free(ptr);
	return (NULL);
}

/**
 * @brief the ft_split seperate the words separated by 'c' 
 * into a 2D array and returns a pointer to it 
 * @see malloc | count_words | words_len | free_s | ft_strlcpy
 * @param[in] s {char const *}  the string we want to split and 
 * extract its words
 * @param[in] c {char} the seperator
 * @return {char **} a pointer to a 2D array that have the words 
 * of the string with a c as a seperator
 * @test
 *	void	print_result(char **result)
 *	{
 *		if (result == NULL)
 *		{
 *			printf("NULL\n");
 *			return ;
 *		}
 *		for (int i = 0; result[i]; i++)
 *		{
 *			printf("\"%s\"\n", result[i]);
 *		}
 *	}
 *
 *	int	main(void)
 *	{
 *		char	s[] = "This is a test string";
 *		char	c;
 *		char	**result;
 *
 *		c = ' ';
 *		result = ft_split(s, c);
 *		print_result(result);
 *		// Free allocated memory
 *		for (int i = 0; result[i]; i++)
 *		{
 *			free(result[i]);
 *		}
 *		free(result);
 *		return (0);
 *	}
 */
char	**ft_split(char const *s, char c)
{
	int		i;
	int		l;
	int		n;
	char	**ptr;

	ptr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || *s == '\0' || !ptr)
		return (free(ptr), NULL);
	i = 0;
	l = -1;
	while (count_words(s, c) > ++l)
	{
		while (s[i] == c && s[i])
			i++;
		n = words_len(&s[i], c);
		ptr[l] = malloc(n + 1);
		if (ptr[l] == NULL)
			ptr = free_s(ptr, l);
		if (!ptr)
			return (NULL);
		ft_strlcpy(ptr[l], (char *)(s + i), n + 1);
		i = i + n;
	}
	ptr[count_words(s, c)] = NULL;
	return (ptr);
}
