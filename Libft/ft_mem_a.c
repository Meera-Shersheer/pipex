/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:37:30 by mshershe          #+#    #+#             */
/*   Updated: 2025/03/15 16:56:11 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief The ft_memchr function searchs for a character 
 * in side a number of memory blocks specified by 
 *  the address of the first memory block and the number 
 * of blocks to search in .
 * @param[in] s {const void *} the address of the first memory block
 * @param[in] c {int} the character to search for
 * @param[in] n {size_t} the number of memory blocks "bytes"
 * @return {void *} the address of the character we search 
 * for in the provided blocks
 * @test
 * int	main(void)
 * {
 *     char s[] = "banana";
 *
 *  char* ptr = (char*)ft_memchr(s, '\0', sizeof(s));
 *     if (ptr != NULL)
 *         printf( "character found in %p \n" , ptr);
 *     else
 *         printf( "character not found\n");
 * }  
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}

/** 
 * @brief The ft_memcmp function compare the characters (bytes)
 *  between s1 and s2 for a 
 * certain number of memory blocks specified by n 
 * @param[in] s1 {const void *} the address of the first memory block
 * @param[in] s2 {const void *} the address of the second memory block
 * @param[in] n {size_t} the number of memory blocks "bytes"
 * @return {int} return the differnce betwwen the 2 memory blocks (s1 - s2)
 * @test
 *   int	main(void)
 *   {
 *       const char *s1 = "hello";
 *       const char *s2 = "helo";
 *       int c = ft_memcmp(s1, s2 , 0);
 *       printf ("%d",c);
 *       return (0);
 *   }
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*_s1;
	const unsigned char	*_s2;

	_s1 = (const unsigned char *)s1;
	_s2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*_s1 != *_s2)
			return (*_s1 - *_s2);
		i++;
		_s1++;
		_s2++;
	}
	return (0);
}

/** 
 * @brief The ft_memcpy function copies  n bytes from memory area s2 to memory
       area s1.  The memory areas must not overlap.
 * @param[in] s1 {void *} the address of the first memory block
 * @param[in] s2 {const void *} the address of the second memory block
 * @param[in] n {size_t} the number of memory blocks "bytes"
 * @return {void *} a pointer to s1
 * @test
 *	int	main(void)
 *	{
 *	//test 1:
 *	char	s2[] = "Test_1 for ft_memcpy";
 *	char	s1[100];
 *	ft_memcpy(s1, s2, 10);
 *	printf("Copied string is %s", s1);
 *	//test 2:
 *	char s3[] = {10, 20, 30, 40, 50};
 *	char	s4[100];
 *	ft_memcpy(s4, s3, 7);
 *	printf("\nCopied array is ");
 *	for (int i=0; i<7; i++)
 *		printf("%d ", s4[i]);
 *	return (0);
 *	}
 */
void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;
	void	*dst1;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = 0;
	dst1 = s1;
	while (i < n)
	{
		*(unsigned char *)s1 = *(unsigned char *)s2;
		s1++;
		s2++;
		i++;
	}
	return (dst1);
}

/** 
 * @brief The ft_memmove function copies  n bytes from memory
 *  area src to memory area dest.  The memory areas may overlap
 * @param[in] dest {void *} the address of the first memory block
 * @param[in] src {const void *} the address of the second memory 
 * block to copy from 
 * @param[in] n {size_t} the number of memory blocks "bytes"
 * @return {void *} a pointer to dest
 * 
 * @test
 * @code{.c}
 *  int	main(void)
 * 	{
 * 		char	test_1[20] = "abcdefghij";
 * 		char	test_2[20] = "abcdefghij";
 * 		char	test_3[20] = "abcdefghij";
 * 		char	test_4[20] = "1234567890";
 * 		char	test_5[20] = "ZeroLength";
 * 		char	test_7[20] = "1234567890123456789";
 * 		char	test_8[30] = "abcdefghijk";
 * 		char	test_9[30] = "abcdefghijk";
 * 	
 * 		ft_memmove(test_1 + 5, test_1 + 2, 5);
 * 		ft_memmove(test_2 + 5, test_2, 5);
 * 		ft_memmove(test_3, test_3 + 5, 5);
 * 		ft_memmove(test_4, test_4, 5);
 * 		ft_memmove(test_5, test_5, 0);
 * 		ft_memmove(test_7 + 10, test_7, 10);
 * 		ft_memmove(test_8 + 10, test_8 + 5, 3);
 * 		ft_memmove(test_9 + 15, test_9, 10);
 * 		printf("Test 1: %s\n", test_1);
 * 		printf("Test 2: %s\n", test_2);
 * 		printf("Test 3: %s\n", test_3);
 * 		printf("Test 4: %s\n", test_4);
 * 		printf("Test 5: %s\n", test_5);
 * 		printf("Test 7: %s\n", test_7);
 * 		printf("Test 8: %s\n", test_8);
 * 		printf("Test 9: %s\n", test_9);
 * 		return (0);
 * 	}
 * @endcode
 * */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	else if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/** 
 * @brief The function fills the first n bytes of the memory 
 * area pointed to by s with the constant byte c.
 * @param[in] s {void *} the address of the first memory block 
 * to start from .
 * @param[in] c {int} the value to set .
 * @param[in] n {size_t} the number of memory blocks "bytes".
 * @return {void *} the address of the first memory block.
 * @test
 *  int	main(void)
 *	{
 *		char	str[] = "try the fuction by using test_1";
 *		int		num[] = {9, 3, 5, 4, 7, 1, 9, 3};
 *		char	s[5];
 *	
 *		// test1
 *		printf("Before ft_memset(): %s\n", str);
 *		ft_memset(str + 4, '.', 21 * sizeof(char));
 *		printf("After ft_memset():  %s\n", str);
 *		// test2
 *		printf("before ft_memset :\n");
 *		for (int i = 0; i < 8; i++)
 *			printf("%d ", num[i]);
 *		ft_memset(num, 4, 8 * sizeof(num[1]));
 *		printf("\n After ft_memset :\n");
 *		for (int j = 0; j < 8; j++)
 *			printf("%d ", num[j]);
 *		// test3
 *		ft_memset(s, 'M', 4 * sizeof(s[0]));
 *		printf("\nS: %s \n", s);
 *		return (0);
 *	} 
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = c;
		n--;
		ptr++;
	}
	return (s);
}
