/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chars_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:10:51 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 18:50:50 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief The ft_tolower function convert uppercase
 *  letters to lowercase.
 * @param[in] c {int} The character to convert.
 * @return {int } the converted letter
 * @test  
 *	int	main(int argc, char *argv[])
 *	{
 *		if (argc == 2)
 *			printf("%d", ft_tolower(*argv[1]));
 *		return (0);
 *	}
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

/** 
 * @brief The ft_toupper function convert lowercase
 *  letters to uppercase.
 * @param[in] c {int} The character to convert.
 * @return {int } the converted letter
 * @test  
 *	int	main(int argc, char *argv[])
 *	{
 *		if (argc == 2)
 *			printf("%d", ft_toupper(*argv[1]));
 *		return (0);
 *	}
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

/** 
 * @brief The ft_atoi function converts the the
 *  string pointed to by nptr to int.
 * @see ft_isdigit
 * @param[in] nptr {const char *} the string to be converted
 * @return {int} The converted value or 0 on error
 * @test
 *	int	main(void)
 *	{
 *			char str[] = "05-6+78";
 *	// cases teseted :-+-5678/ --5678/+5678/-567h8/
 	//					0/405/4000/000400
 *	// 0-+-5678/05 678/
 *			printf(" %d\n", ft_atoi("-+-5678"));
 *		printf(" %d\n", ft_atoi("--5678"));
 *		printf(" %d\n", ft_atoi("+5678"));
 *		printf(" %d\n", ft_atoi("-567h8"));
 *		printf(" %d\n", ft_atoi("0"));
 *		printf(" %d\n", ft_atoi("405"));
 *		printf(" %d\n", ft_atoi("4000"));
 *		printf(" %d\n", ft_atoi("000400"));
 *		printf(" %d\n", ft_atoi("0-+-5678"));
 *		printf(" %d\n", ft_atoi("05 678"));
 *		printf(" %d\n", ft_atoi(str));
 *	}
 */
int	ft_atoi(const char *nptr)
{
	int	num;
	int	pn;
	int	sign;

	pn = 1;
	num = 0;
	sign = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	while (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == '-')
			pn = -1;
		sign++;
		nptr++;
		if (sign > 1)
			return (0);
	}
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return (num * pn);
}

/** 
 * @brief the int_len function finds the number of 
 * characters an int needs to be represented in the string  
 * @param[in] b {int}  the int to find its length 
 * @return {int} the number of characters an int needs
 *  to be represented in the string  
 */
static int	int_len(int b)
{
	int	len;

	len = 0;
	if (b <= 0)
	{
		b *= -1;
		len++;
	}
	while (b > 0)
	{
		len++;
		b /= 10;
	}
	return (len);
}

/** 
 * @brief The ft_itoa function Allocates and returns
 *  a string
 * representing the integer received as an argument
 * @see malloc | ft_strdup | int_len
 * @param[in] n {int} the integer to be converted
 * @retval NULL if the allocation fails. 
 * @retval {char *} The string representing the integer.
 * @test
 *	int	main(void)
 *	{
 *		char *s0;
 *		char *s1;
 *		char *s2;
 *		char *s3;
 *		char *s4;
 *		char *s5;
 *		char *s6;
 *		char *s7;
 *		char *s8;
 *
 *		s0 = ft_itoa(0); // more cases 5000 /123678/ -623
 *		s1 = ft_itoa(-2147483648);
 *		s2 = ft_itoa(2147483647);
 *		s3 = ft_itoa(-2147483648LL);
 *		s4 = ft_itoa(156);
 *		s5 = ft_itoa(-123678);
 *		s6 = ft_itoa(1234567890);
 *		s7 = ft_itoa(30004);
 *		s8 = ft_itoa(304);
 *
 *		printf("%s",s0);
 *		printf("\n%s",s1);
 *		printf("\n%s",s2);
 *		printf("\n%s",s3);
 *		printf("\n%s",s4);
 *		printf("\n%s",s5);
 *		printf("\n%s",s6);
 *		printf("\n%s",s7);
 *		printf("\n%s",s8);
 *
 *	}
 */
char	*ft_itoa(int n)
{
	int		b;
	int		i;
	char	*s;

	if (n != 0 && n != -2147483648)
		s = malloc(int_len(n) + 1);
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	i = int_len(n);
	b = n;
	if (n < 0 && s != NULL)
	{
		s[0] = '-';
		b = n * -1;
	}
	while (b > 0 && --i >= 0 && n != -2147483648 && n != 0 && s != NULL)
	{
		s[i] = ((b % 10) + '0');
		b = b / 10;
	}
	if (n != 0 && n != -2147483648 && s != NULL)
		s[int_len(n)] = '\0';
	return (s);
}
