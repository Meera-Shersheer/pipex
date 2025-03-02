/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:36:14 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 19:01:53 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/** 
 * @brief the ft_strncmp function compares the first n
 *  bytes (at most) between the two strings s1 and s2 
 * @param[in] s1 {const char *} the first string to compare  
 * @param[in] s2 {const char *} the second string of comparision 
 * @param[in] n {size_t} the number of bytes to compare at most  
 * @retval 0 --> if s1 and s2 are equal  
 * @retval negative int --> if s2 is greater than s1 
 * @retval positive int --> if s1 greater than s2
 * @test
 * 	int	main(void) 
 *	{
 *		const char *s1 = "hello";
 *		const char *s2 = "helo";
 *		int c = ft_strncmp(s1, s2 , 6);
 *		printf ("%d",c);
 *		return (0);
 *	}
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if ((unsigned char)(s1[i]) != (unsigned char)(s2[i]))
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	if (i < n)
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	return (0);
}

/** 
 * @brief the ft_strchr function searches for the first 
 * occurrence of the character c in the string s.
 * @see ft_strlen
 * @param[in] s {const char *} the string to search in
 * @param[in] c {int} the character to search for
 * @return {char *} a pointer to the first occurrence of the
 *  character c in the string s , NULL if c not found in the
 *  string s.
 * @test
 *	int	main(void)
 *	{
 *		const char *s ;
 *		int c ;
 *
 *	//	s = "hila";
 *		s = "teste";
 *		c = 1024;
 *		printf ("%s",ft_strchr(s , c));
 *		return (0);
 *	}
 */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		else
			i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	return (NULL);
}

/** 
 * @brief the ft_strrchr function searches for the last 
 * occurrence of the character c in the string s.
 * @see ft_strlen
 * @param[in] s {const char *} the string to search in
 * @param[in] c {int} the character to search for
 * @return {char *} a pointer to the last occurrence of the 
 * character c in the string s
 * @test
 *	int	main(void)
 *	{
 *		const char *s ;
 *		int c ;
 *
 *		s = "hilai";
 *		c = '\0';//tried l , i and '\0'
 *		printf ("%p",ft_strrchr(s , c));
 *		return (0);
 *	}
 */
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		else
			i--;
	}
	return (NULL);
}

/** 
 * @brief the ft_strnstr functions looks for the first occurance in
 * the substring little in the string big in the first len characters
 * @see ft_strlen | ft_strncmp
 * @param[in] big {const char *} the string to search in
 * @param[in] little {const char *} the substring to look for  
 * @param[in] len  {size_t} the number of characters to do the search in 
 * @retval {char *} a pointer to big is returned if little is empty
 * @retval {char *} NULL is returned if little doesn't occure in big 
 * @retval {char *} otherwise a pointer to the first character of the 
 * first occurrence of little is returned.
 * @test
 *	int main (void)
 *	{
 *		const char *largestring = "Foo Bar Baz";
 *	//	const char *smallstring = "Bar";
 *		const char *smallstring_2 = "";
 *		char *ptr;
 *
 *	//	ptr = ft_strnstr(largestring, smallstring, 4);
 *	//	ptr = ft_strnstr(largestring, smallstring, 10);
 *		ptr = ft_strnstr(largestring, smallstring_2, 20);
 *		printf("%p", ptr);
 *	}
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		found;
	int		len_lit;
	size_t	i;

	found = 0;
	i = 0;
	len_lit = ft_strlen(little);
	if (!len_lit)
		return ((char *)big);
	else
	{
		while (*big && i < len)
		{
			if (*big == *little)
			{
				found = ft_strncmp(big, little, len_lit);
				if (found == 0 && (i + len_lit) <= len)
					return ((char *)big);
			}
			big++;
			i++;
		}
	}
	return (NULL);
}
