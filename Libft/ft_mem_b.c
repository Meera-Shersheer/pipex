/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:17:04 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 18:58:29 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief The ft_bzero function erases  the data in the n 
 * bytes of the memory starting at the location
 * pointed to by s, by writing zeros (bytes containing '\0') to 
 * that area.
 * @param[in] s {void *} the address of the first memory block
 * @param[in] n {size_t} the number of memory blocks "bytes"
 * @test
 *    int	main(void)
 *    {
 *        char str[] = "try the fuction by using test_1";
 *            int num[] = {9,3,5,4,7,1,9,3};
 *        char s[5];
 *
 *        //test1
 *        printf("Before ft_bzero: %s\n", str);
 *        ft_bzero(str + 4 , 21*sizeof(char));
 *        printf("After ft_bzero:  %s\n", str);
 *        //test2
 *        printf("before ft_bzero :\n");
 *        for (int i=0; i < 8; i++)
 *            printf("%d ", num[i]);
 *        ft_bzero(num , 8*sizeof(num[1]));
 *        printf("\n After ft_bzero:\n");
 *        for (int j=0; j < 8; j++)
 *            printf("%d ", num[j]);
 *        //test3
 *        ft_bzero(s,4*sizeof(s[0]));
 *        printf("\nS: %s \n", s);
 *        return (0);
 *    }
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = '\0';
		n--;
		ptr++;
	}
}

/** 
 * @brief the ft_calloc allocates memory for an array of 
 * 'nmemb' elements of 'size' bytes each, set it to zero and
       returns a pointer to the allocated memory
 * @see malloc
 * @param[in] nmemb {size_t} number of elements
 * @param[in] size {size_t} number of bytes for each element
 * @return {void *} a pointer to the allocated memory
 * @test
 *    int main (void)
 *    {
 *        int*	ptr;
 *        int	n;
 *        int	i;
 *
 *        n = 5;// test_1: n = 5  test_2: n = 0  test_4: 1000000000
 *        i = 0;
 *        ptr = (int*)ft_calloc(n, sizeof(int));//test_3: size is zero
 *        if (ptr == NULL)
 *        {
 *            printf("Memory not allocated.\n");
 *            return (1);
 *        }
 *        else
 *        {
 *            printf("Memory successfully been allocated by calloc.\n");
 *        printf("The elements of the array are: ");
 *        while(i < n)
 *        {
 *        printf("%d ", ptr[i]);
 *        i++;
 *        }
 *        }
 *        return(0);
 *    }
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(nmemb * size);
	i = 0;
	if (ptr != NULL)
	{
		while (i < (nmemb * size))
		{
			*(ptr + i) = 0;
			i++;
		}
	}
	return ((void *)ptr);
}
