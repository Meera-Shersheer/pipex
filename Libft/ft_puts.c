/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:04:28 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 18:59:41 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/** 
 * @brief The ft_putchar_fd function prints the character 
 * into the spacified file discriptor.
 * @param[in] c {char} The character to print.
 * @param[in] fd {int} The file discriptor to print in.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/** 
 * @brief The ft_putendl_fd function prints a string 
 * followed by a new line into the spacified file discriptor.
 * @param[in] s {char *} The string to print.
 * @param[in] fd {int} The file discriptor to print in.
 */
void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

/** 
 * @brief The ft_putstr_fd function prints a string into
 *  the spacified file discriptor.
 * @param[in] s {char *} The string to print.
 * @param[in] fd {int} The file discriptor to print in.
 */
void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

/** 
 * @brief The ft_putnbr_fd function prints an integer 
 * into the spacified file discriptor .
 * @param[in]  n {int} The integer number to print .
 * @param[in] fd {int} The file discriptor to print in .
 * @test
 *	 int	main(void)
 *	 {
 *	     int	fd;
 *	
 *	     fd = 1;
 *	     ft_putnbr_fd(0, fd);
 *	     write(fd, "\n", 1);
 *	     ft_putnbr_fd(-2147483648, fd);
 *	     write(fd, "\n", 1);
 *	     ft_putnbr_fd(2147483647, fd);
 *	     write(fd, "\n", 1);
 *	     ft_putnbr_fd(5000, fd);
 *	     write(fd, "\n", 1);
 *	     ft_putnbr_fd(123678, fd);
 *	     write(fd, "\n", 1);
 *	     ft_putnbr_fd(-123678, fd);
 *	     write(fd, "\n", 1);
 *	     ft_putnbr_fd(1234567890, fd);
 *	     write(fd, "\n", 1);
 *	     ft_putnbr_fd(30004, fd);
 *	     write(fd, "\n", 1);
 *	     ft_putnbr_fd(304, fd);
 *	     write(fd, "\n", 1);
 *	     ft_putnbr_fd(304, fd);
 *	     write(fd, "\n", 1);
 *	     ft_putnbr_fd(-2147483648LL, fd);
 *	     write(fd, "\n", 1);
 *	 }
 */
void	ft_putnbr_fd(int n, int fd)
{
	int		nb;
	char	s;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		if (nb == -2147483648)
		{
			write(fd, "2147483648", 10);
			return ;
		}
		nb *= -1;
	}
	if (nb / 10 > 0)
		ft_putnbr_fd(nb / 10, fd);
	s = (nb % 10) + '0';
	write(fd, &s, 1);
}
