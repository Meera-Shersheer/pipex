/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:47:17 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 19:51:03 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/** 
 * @brief The ft_putchar_adv_fd function prints the character into the 
 * spacified file discriptor.
 * @param[in] c {char} The character to print.
 * @param[in] fd {int} The file discriptor to print in.
 * @return the number of printed chars
 */
int	ft_putchar_adv_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

/** 
 * @brief The ft_putstr_adv_fd function prints a string into the 
 * spacified file discriptor.
 * @param[in] s {char *} The string to print.
 * @param[in] fd {int} The file discriptor to print in.
 * @return the number of characters printed
 */
int	ft_putstr_adv_fd(char *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}

/** 
 * @brief The ft_putnbr_unsigned_fd function prints an unsigned  
 * integer in decimal numbering system into the spacified file descriptor.
 * @param[in]  nb {unsigned int} The  unsigned integer number to print.
 * @param[in] fd {int} The file discriptor to print in.
 * @return the number of characters printed
 */
int	ft_putnbr_unsigned_fd(unsigned int nb, int fd)
{
	char	s;
	int		count;

	count = 0;
	if (nb / 10 > 0)
		count += ft_putnbr_unsigned_fd(nb / 10, fd);
	s = (nb % 10) + '0';
	count += write(fd, &s, 1);
	return (count);
}

/** 
 * @brief The ft_putnbr_hex_fd function prints an integer in hexadecimal 
 * numbering system into the spacified file discriptor using
 *  capital or small letters.
 * @param[in]  n {size_t} The integer number to print .
 * @param[in] fd {int} The file descriptor to print in .
 * @param[in] Cap {int} 0 --> use small letters.
 * 						1 --> use Capital letters.
 * @return the number of characters printed
 */
int	ft_putnbr_hex_fd(size_t n, int fd, int Cap)
{
	size_t	nb;
	size_t	d;
	int		count;
	char	s;

	nb = n;
	count = 0;
	if (nb / 16 > 0)
		count += ft_putnbr_hex_fd(nb / 16, fd, Cap);
	d = (nb % 16);
	if (d <= 9)
		s = d + '0';
	else if (d > 9 && d < 16)
	{
		if (Cap)
			s = 'A' + (d - 10);
		else
			s = 'a' + (d - 10);
	}
	count += write(fd, &s, 1);
	return (count);
}

/** 
 * @brief The ft_putnbr_adv_fd function prints an 
 * integer in decimal numbering system into the spacified file discriptor .
 * @param[in]  n {int} The integer number to print .
 * @param[in] fd {int} The file discriptor to print in .
 * @return the number of characters printed
 */
int	ft_putnbr_adv_fd(int n, int fd)
{
	int	nb;
	int	count;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		count += write(fd, "-", 1);
		if (nb == -2147483648)
		{
			count += write(fd, "2147483648", 10);
			return (count);
		}
		nb *= -1;
	}
	if (nb / 10 > 0)
		count += ft_putnbr_adv_fd(nb / 10, fd);
	count += write(fd, &"0123456789"[nb % 10], 1);
	return (count);
}
