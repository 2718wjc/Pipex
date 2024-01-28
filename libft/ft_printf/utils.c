/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:57:10 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/06 18:40:06 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int	numlen(unsigned long long abs, int base)
{
	int	len;

	if (!abs)
		return (1);
	len = 0;
	while (abs)
	{
		abs /= base;
		len++;
	}
	return (len);
}

static char	*numstr(unsigned long long abs, int base, t_bool caps)
{
	char	*result;
	int		len;

	len = numlen(abs, base);
	result = malloc((len + 1) * sizeof(char));
	while (!result)
		result = malloc((len + 1) * sizeof(char));
	*(result + len--) = 0;
	if (!abs)
		*(result + len--) = '0';
	while (abs)
	{
		*(result + len--)
			= "0123456789abcdef0123456789ABCDEF"[abs % base + 16 * caps];
		abs /= base;
	}
	return (result);
}

char	*argstr(char spec, va_list argp)
{
	int		_int;

	if (spec == 's')
		return (va_arg(argp, char *));
	else if (spec == 'p')
		return (numstr(va_arg(argp, unsigned long long), 16, FALSE));
	else if (spec == 'd' || spec == 'i')
	{
		_int = va_arg(argp, int);
		if (_int < 0)
			return (numstr((unsigned int) -_int, 10, FALSE));
		else
			return (numstr(_int, 10, FALSE));
	}
	else if (spec == 'u')
		return (numstr(va_arg(argp, unsigned int), 10, FALSE));
	else if (spec == 'x')
		return (numstr(va_arg(argp, unsigned int), 16, FALSE));
	else if (spec == 'X')
		return (numstr(va_arg(argp, unsigned int), 16, TRUE));
	else
		return (0);
}

char	*padstr(char padc, int cnt)
{
	char	*result;

	if (cnt < 0)
		cnt = 0;
	result = malloc((cnt + 1) * sizeof(char));
	if (!result)
	{
		if (cnt > 64)
			return (0);
		else
			while (!result)
				result = malloc((cnt + 1) * sizeof(char));
	}
	ft_memset(result, padc, cnt);
	*(result + cnt) = 0;
	return (result);
}

size_t	sumlen(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		if (lst->content)
			len += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (len);
}
