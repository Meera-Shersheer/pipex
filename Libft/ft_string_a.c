/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:06:57 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 18:53:10 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief the ft_strlen function calculates the length of 
 * the string pointed to by s, excluding the terminating 
 * null byte ('\0').
 * @param[in] s {const char *} the address of the c string 
 * to find the length of.
 * @return {size_t} the length of the string 
 * @test
 *    int main (int argc, char **argv )
 *    {
 *        if (argc ==2 )
 *            printf("%ld",ft_strlen (argv[1]));
 *        return (0);
 *    } 
 */
size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n] != '\0')
		n++;
	return (n);
}

/** 
 * @brief ft_strlcpy function copies up to size - 1 
 * characters from the NUL-terminated string src to dst, 
 * NUL-terminating the result. 
 * @see ft_strlen 
 * @param[in] dst {char *} the NUL-terminated string to copy to
 * @param[in] src {const char *} the NUL-terminated string to copy from 
 * @param[in] size {size_t} the number of characters to copy including 
 * the null terminating characrter
 * @return {size_t}  the length of src
 * @test
 *    int main(void)
 *    {
 *        char dest[6];
 *    //const char *src = "Hello, World!";// >> dest[20]
 *    // const char *src = "This is a long string"; //>> dest[10]
 *        //const char *src = "Exact length";// >> dest[14]
 *        //const char *src = "";//>> dest[14]
 *        //const char *src = "Short";//>> dest[1]
 *        const char *src = "abcde";//>> dest[6]
 *        size_t result = ft_strlcpy(dest, src, sizeof(dest));
 *
 *        printf("Destination: %s\n", dest);
 *        printf("Result: %zu\n", result);
 *
 *        return (0);
 *    }
 *    
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && size - 1 > i)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/** 
 * @brief ft_strlcat function appends the NUL-terminated 
 * string src to the end of dst.It will append at most 
 * [size - strlen(dst) - 1]bytes, NUL-terminating the result.
 * @see ft_strlen 
 * @param[in] dst  {char *}  the string that will append to.
 * @param[in] src {const char *} the string we append. 
 * @param[in] size {size_t}  the total size of the buffer 
 * available in the destination string (dst) including the 
 * null terminating characrter
 * @return {size_t} the total length of the string it tried 
 * to create ( the length of dst + the length of src)
 * @test
 *  int	main(void) {
 *
 *      //test_1
 *      char dst[20] = "Hello, ";
 *      const char *src = "World!";
 *      //test_2
 *  //	char dst[10] = "Hello";
 *  //	const char *src = "World!";
 *      //test_3 >> same as test 1 but with dst[13] instead of dst[20]
 *      //test_4
 *  //	char dst[20] = "Hello, ";
 *  //	const char *src = "";
 *      //test_5 >> same as test_2 but with a 
 * 		//size of 0 as an argument to the function
 *      //test_6
 *  //	char dst[6] = "";
 *  //	const char *src = "Hello";
 *
 *      size_t result = ft_strlcat(dst, src, sizeof(dst));// size =0,
 *          size = sizeof(dst)
 *      printf("Destination: %s\n", dst);
 *      printf("Result: %zu\n", result);
 *      return (0);
 *  }
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_l;
	size_t	src_l;
	size_t	counter;
	size_t	i;

	i = 0;
	dst_l = ft_strlen(dst);
	src_l = ft_strlen(src);
	counter = dst_l;
	while (src[i] && i < (size - dst_l - 1) && size > dst_l)
	{
		dst[counter] = src[i];
		i++;
		counter++;
	}
	if ((size - dst_l) > 0)
		dst[counter] = '\0';
	if (size < dst_l)
		return (size + src_l);
	return (dst_l + src_l);
}

/** 
 * @brief ft_strdup function returns a pointer to a new 
 * string which is a duplicate of the string s
 * @see malloc | ft_strlen
 * @param[in] s {const char *} the NUL-terminated string to duplicate
 * @return returns a pointer to the new string or NULL in case of failure
 * @test
 *  #include <stdio.h>
 *
 *    int	main(void)
 *    {
 *    // const char *s = "Hello, world!";
 *    //const char *s = "";
 *    //const char *s = "Line1\nLine2\tTabbed";
 *
 *        char *dup = ft_strdup(s);
 *
 *        if (dup == NULL) {
 *            printf("failed\n");
 *            return (1);
 *        }
 *
 *        printf("s: %s\n", s);
 *        printf("Dup: %s\n", dup);
 *        return (0);
 *    }  
 */
char	*ft_strdup(const char *s)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (ptr != NULL)
	{
		while (s[i] != '\0')
		{
			ptr[i] = s[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}

/** 
 * @brief Allocates (with malloc(3)) and returns a 
 * new string, which is the result of the concatenation of 
 * ’s1’ and ’s2’
 * @see malloc | ft_strlen
 * @param[in] s1 {const char *} The prefix string.
 * @param[in] s2  {const char *} The suffix string.
 * @return returns a pointer to the new string or NULL in
 *  case of failure  
 * @test
 *    int main (void)
 *    {
 *        char	*ptr;
 *
 *        char *s1 ="hi";
 *            char *s2 =", bye";
 *            ptr = ft_strjoin(s1, s2);
 *            printf("%s" , ptr);
 *    }
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n;
	size_t	i;
	size_t	t;
	char	*ptr;

	n = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	t = 0;
	ptr = malloc(n + 1);
	if (ptr != NULL)
	{
		while (i < ft_strlen(s1))
		{
			ptr[i] = s1[i];
			i++;
		}
		while (t < ft_strlen(s2))
		{
			ptr[i] = s2[t];
			t++;
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
