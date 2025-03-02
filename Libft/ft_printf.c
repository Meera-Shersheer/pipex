/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:51:04 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/06 18:59:13 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/** 
 * @brief  the form function see what spacifier is used 
 * after the percentage sign  and redirect it to other function
 *  to handel it  
 * @see ft_putchar_adv_fd | putint | va_arg | put_s | putunsigned | putpointer
 * @param[in] format {const char *} the string to handle
 * @param[in] i {int} the index of the specifier to check 
 * @param[in] args {va list} the variadic function argument
 * @return {int} the number of characters printed
 */
static int	form(const char *format, int i, va_list args)
{
	int	count;

	count = 0;
	if (format[i] == '%')
		count = ft_putchar_adv_fd('%', 1);
	else if (format[i] == 'c' || format[i] == 'd' || format[i] == 'i')
		count = putint(format, i, va_arg(args, int));
	else if (format[i] == 's')
		count = put_s(va_arg(args, char *));
	else if (format[i] == 'u' || format[i] == 'X' || format[i] == 'x')
		count = putunsigned(format, i, va_arg(args, unsigned int));
	else if (format[i] == 'p')
		count = putpointer(va_arg(args, size_t));
	else
		count = -1;
	return (count);
}

/** 
 * @brief  the printf function prints the specified string 
 * 'format' with replacing its specifiers with
 *  the values given with the variadic function argument on the
 *  terminal (file descriptor = 1)  
 * @see  ft_strchr | ft_putstr_adv_fd |va_start | form | ft_putchar_adv_fd | 
 * va_end
 * @param[in] format {const char *} the string to handle
 * @return {int} the number of characters printed
 */
int	ft_printf(const char *format, ...)
{
	int		count;
	int		error;
	int		i;
	va_list	args;

	count = 0;
	error = 0;
	i = -1;
	if (ft_strchr(format, '%') == NULL)
		return (ft_putstr_adv_fd((char *)format, 1));
	va_start(args, format);
	while (format[++i] != '\0' && error != -1)
	{
		error = 0;
		if (format[i] == '%')
			error = form(format, ++i, args);
		else
			error = ft_putchar_adv_fd(format[i], 1);
		if (error == -1)
			count = error;
		else
			count += error;
	}
	va_end(args);
	return (count);
}
