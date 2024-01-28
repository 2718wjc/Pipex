/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:45:40 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/06 19:54:45 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	if (*str >= '0' && *str <= '9')
	{
		num = 0;
		while (1)
		{
			if (*str < '0' || *str > '9')
				break ;
			num = num * 10 + *str++ - '0';
		}
		return (sign * num);
	}
	return (0);
}
