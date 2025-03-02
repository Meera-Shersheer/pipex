/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:24:05 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 19:03:00 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief the ft_striteri function applies the function f 
 * to each character of the string s, passing its index as 
 * the first argument and.
 * @param[in] s {char const *} The string on which to iterate on
 * @param[in] f {input :[unsigned int, char * ]} 
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	if (s != NULL && f != NULL)
	{
		while (s[i] != '\0')
		{
			f(i, &s[i]);
			i++;
		}
	}
}

/** 
 * @brief the ft_strmapi function creates a new string that have 
 * the characters 
 * resulted from applying the function f to each character of the
 * string s, passing its index as the first argument
 * and the character itself as the second to f.
 * @see malloc
 * @param[in] s {char const *} The string on which to iterate on
 * @param[in] f {return : [char] , input :[unsigned int, char]} 
 * The function to apply to each character.
 * @retval {char *} a pointer to the string created from the
 *  successive applications of ’f’ . 
 * @retval  NULL if the allocation fails.
 * @test
 *    char	f(unsigned int i, char c)
 *    {
 *        char	str;
 *
 *        (void)i;
 *        str = c + 1;
 *        return (str);
 *    }
 *
 *    int	main(void)
 *    {
 *        char str1[] = "abc";
 *        char* str2;
 *        str2 = ft_strmapi(str1, *f);
 *        printf("%s\n", str2);
 *
 *    }
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (ptr != NULL && f != NULL)
	{
		while (s[i] != '\0')
		{
			ptr[i] = f(i, s[i]);
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}

/** 
 * @brief the ft_strtrim function allocates returns a copy of ’s1’ with the 
 * characters specified in ’set’ removed from the beginning and the
 *  end of the string.
 * @see ft_strlen | ft_strchr | malloc | ft_memcpy
 * @param[in] s1 {char const *} the string to be trimmed
 * @param[in] set {char const *} The reference set of characters to trim.
 * @retval {char *} a poionter to the trimmed string 
 * @retval NULL pointer in case if failed allocation
 * @test
 *    int main()
 *    {
 *        char const s1[] = "ccMOHcc";
 *        char const set[] = "c";
 *        printf("%s", ft_strtrim(s1, set));
 *    }
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	int		t;
	char	*ptr;
	int		r;

	r = 0;
	t = ft_strlen(s1);
	while (s1[r] && ft_strchr(set, s1[r]))
		r++;
	while (t != r && ft_strchr(set, s1[t - 1]))
		t--;
	ptr = malloc(t - r + 1);
	if (!ptr)
		return (NULL);
	ptr = ft_memcpy((void *)ptr, &s1[r], t - r);
	ptr[t - r] = '\0';
	return (ptr);
}

/** 
 * @brief the len_sub function checks the validity of the substing 
 * len given to be extracted from the string s and updates len if necessary 
 * @see  ft_strlen
 * @param[in] s {char const *} The string to create the substring from
 * @param[in] start {unsigned int} The start index of the substring 
 * in the string ’s
 * @param[in] len {size_t} The maximum length of the substring 
 * @return {size_t} the length of the substring 
 */
static size_t	len_sub(char const *s, unsigned int start, size_t len)
{
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	if (ft_strlen(s) < (start) || (start + len) > ft_strlen(s))
		len = 0;
	return (len);
}

/** 
 * @brief The ft_substr function creates a substring from 
 * the string s 
 * @see ft_strlcpy | malloc | len_sub
 * @param[in] s {char const *} The string to create the substring from
 * @param[in] start {unsigned int} The start index of the substring in 
 * the string ’s
 * @param[in] len {size_t} The maximum length of the substring
 * @retval NULL in case of allocation failure
 * @retval {char *} a pointer to the substring created 
 * @test
 *    int	main(void)
 *    {
 *        unsigned int			start;
 *        size_t			len;
 *        char const			*s;
 *            char	*sub_s;
 *
 *        s = "Hello, world!";
 *        start = 2;
 *        len = 5;
 *        sub_s = ft_substr(s, start, len);
 *    //	sub_s = ft_substr("Hello, world!", 7, 5);
 *    //	sub_s = ft_substr("Hello, world!", 0, 5);
 *    //	sub_s = ft_substr("Hello, world!", 7, 20);
 *    //	sub_s = ft_substr("", 0, 5);
 *    //	sub_s = ft_substr("Hello, world!", 20, 5);
 *    //	sub_s = ft_substr("Hello, world!", 7, 0);
 *    //	sub_s = ft_substr("Hello, world!", 0, 0);
 *    //	sub_s = ft_substr("Hello, world!", 5, 0);
 *    //	sub_s = ft_substr("Short", 3, 10);
 *    //	sub_s = ft_substr("C programming", 4, 20);
 *    //	sub_s = ft_substr(NULL, 0, 5);
 *        printf("the original string is : %s",s);
 *        printf("\nthe substring is : %s",sub_s);
 *    }
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (s == NULL)
		return (NULL);
	len = len_sub(s, start, len);
	if (*s == '\0' || len == 0)
	{
		sub = malloc(sizeof(char));
		if (sub != NULL)
			sub[i] = '\0';
		return (sub);
	}
	sub = malloc((len + 1) * sizeof(char));
	if (sub != NULL)
	{
		while (s[i] != '\0')
		{
			if (i == start)
				ft_strlcpy(sub, (char *)&s[i], len + 1);
			i++;
		}
	}
	return (sub);
}
