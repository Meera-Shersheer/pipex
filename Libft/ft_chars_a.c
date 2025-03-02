/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chars_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:15:28 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 18:50:13 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/** 
 * @brief The isalnum() function tests for any 
 * character for which isalpha(3) or isdigit(3) is true.
 * @param[in] c {int} The character to test.
 * @retval 1 if c is alphanumeric (either letter or digit).
 * @retval 0 if c is not alphanumeric (neither letter nor 
 * digit).
 * @test  
 * #include <stdio.h>
 * int	main(int argc, char *argv[])
 * {
 * 	if (argc == 2)
 * 		printf("%d", ft_isalnum(*argv[1]));
 * 	return (0);
 * }
 */
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

/** 
 * @brief  The ft_isalpha function tests if the 
 * character for which islower(3) or isupper(3) is true. 
 * @param[in] c {int} The character to test.
 * @retval 1  if c is a letter.
 * @retval 0 if c not a letter.
 * @test  
 *	#include <stdio.h>
 *	int	main(int argc, char *argv[])
 *	{
 *		if (argc == 2)
 *			printf("%d", ft_isalpha(*argv[1]));
 *		return (0);
 *	}
 */
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/** 
 * @brief  The ft_isascii function check if the 
 * character is included in the ascii table. 
 * @param[in] c {int} The character to test.
 * @retval 1  if c is in ascii table.
 * @retval 0  if c is not in ascii table.
 * @test  
 *	#include <stdio.h>
 *	int	main(void)
 *	{
 *		printf("%d", ft_isascii(128));
 *		printf("%d", ft_isascii(9));
 *		printf("%d", ft_isascii('0'));
 *		return (0);
 *	}
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/** 
 * @brief  The ft_isdigit function check if the 
 * character is a digit or not 
 * @param[in] c {int} The character to test.
 * @retval 1 if c is a digit.
 * @retval 0 if c is not a digit.
 * @test  
 *	#include <stdio.h>
 *	int	main(void)
 *	{
 *		printf("%d", ft_isdigit(10));
 *		printf("%d", ft_isdigit(9));
 *		printf("%d", ft_isdigit('0'));
 *		return (0);
 *	}
 */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/** 
 * @brief  The ft_isprint function check if the character
 *  is a printable character from the ascii table or not 
 * @param[in] c {int} The character to test.
 * @retval 1 if c is a printable character
 * @retval 0 if c is not a printable character
 * @test  
 *	 #include <stdio.h>
 *	int	main(void)
 *	{
 *		printf("%d", ft_isprint(128));
 *		printf("%d", ft_isprint(9));
 *		printf("%d", ft_isprint('0'));
 *		printf("%d", ft_isprint(300));
 *		return (0);
 *	}
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
