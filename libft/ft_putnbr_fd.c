/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:21:09 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/11 16:13:42 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	rev[11];
	int		len;
	int		n_cp;

	len = 0;
	if (!n)
		rev[len++] = '0';
	n_cp = n;
	while (n)
	{
		if (n < 0)
			rev[len++] = n % 10 * -1 + '0';
		else
			rev[len++] = n % 10 + '0';
		n /= 10;
	}
	if (n_cp < 0)
		rev[len++] = '-';
	while (len != 0)
		write(fd, &rev[--len], 1);
}
