/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:25:51 by mshershe          #+#    #+#             */
/*   Updated: 2024/09/13 20:27:54 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_putnbr_unsigned_fd(unsigned int nb, int fd);
int	ft_putnbr_hex_fd(size_t n, int fd, int Cap);
int	ft_putnbr_adv_fd(int n, int fd);
int	ft_putchar_adv_fd(char c, int fd);
int	ft_putstr_adv_fd(char *s, int fd);
int	putint(const char *format, int i, int arg);
int	putunsigned(const char *format, int i, unsigned int arg);
int	putpointer(size_t arg);
int	put_s(char *arg);
#endif
