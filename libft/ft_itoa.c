/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:49:34 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/24 16:56:12 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	numlen(int n)
{
	int	len;
	int	copy;

	if (!n)
		return (1);
	len = 0;
	copy = n;
	while (n)
	{
		n /= 10;
		len++;
	}
	if (copy < 0)
		len++;
	return (len);
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	abs;
	int				len;

	len = numlen(n);
	if (n < 0)
		abs = (unsigned int) -n;
	else
		abs = n;
	result = malloc((len + 1) * sizeof(char));
	while (!result)
		result = malloc((len + 1) * sizeof(char));
	*(result + len--) = 0;
	if (!abs)
		*(result + len--) = '0';
	while (abs)
	{
		*(result + len--) = abs % 10 + '0';
		abs /= 10;
	}
	if (n < 0)
		*(result + len--) = '-';
	return (result);
}
