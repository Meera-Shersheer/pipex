/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:36:39 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 19:51:21 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/** 
 * @brief  the putint function see if the spacifier is a decimal
 *  number or a character and handel it accordingly  
 * @see ft_putchar_adv_fd | ft_putnbr_adv_fd
 * @param[in] format {const char *} the string to handle
 * @param[in] i {int} the index of the specifier to check 
 * @param[in] args {va list} the variadic function argument
 * @return {int} the number of characters printed
 */
int	putint(const char *format, int i, int arg)
{
	int	count;

	count = 0;
	if (format[i] == 'c')
		count = ft_putchar_adv_fd(arg, 1);
	else
		count = ft_putnbr_adv_fd(arg, 1);
	return (count);
}

/** 
 * @brief  the putunsigned function see if the spacifier is a
 *  hexadecimal or unsigned number and handel it accordingly  
 * @see ft_putnbr_unsigned_fd | ft_putnbr_hex_fd
 * @param[in] format {const char *} the string to handle
 * @param[in] i {int} the index of the specifier to check 
 * @param[in] args {va list} the variadic function argument
 * @return {int} the number of characters printed
 */
int	putunsigned(const char *format, int i, unsigned int arg)
{
	int	count;

	count = 0;
	if (format[i] == 'u')
		count = ft_putnbr_unsigned_fd(arg, 1);
	else if (format[i] == 'X')
		count = ft_putnbr_hex_fd(arg, 1, 1);
	else if (format[i] == 'x')
		count = ft_putnbr_hex_fd(arg, 1, 0);
	return (count);
}

/** 
 * @brief  the putpointer function prints the address passed by 
 * 'arg' in hexadicimal format 
 * @see ft_putstr_adv_fd | ft_putnbr_hex_fd
 * @param[in] arg {size_t} the address to print 
 * @return {int} the number of characters printed
 */
int	putpointer(size_t arg)
{
	int	count;

	count = 0;
	if (arg == 0)
		count = ft_putstr_adv_fd("(nil)", 1);
	else
	{
		count = ft_putstr_adv_fd("0x", 1);
		count += ft_putnbr_hex_fd(arg, 1, 0);
	}
	return (count);
}

/** 
 * @brief  the put_s function prints the string passed by 'arg'
 * @see ft_putstr_adv_fd 
 * @param[in] arg {char *} the string to print 
 * @return {int} the number of characters printed
 */
int	put_s(char *arg)
{
	int	count;

	count = 0;
	if (arg == NULL)
		arg = "(null)";
	count = ft_putstr_adv_fd(arg, 1);
	return (count);
}
