/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:03:09 by fmai              #+#    #+#             */
/*   Updated: 2022/01/05 22:42:28 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_digit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

int	atoi(const char *str)
{
	int				sign;
	unsigned int	n;

	while (is_space(*str))
		str++;
	if (*str == '-')
		sign = -1;
	else
		sign = 1;
	if (*str == '-' || *str == '+')
		str++;
	n = 0;
	while (is_digit(*str))
	{
		if (sign == 1 && ((unsigned int)10 * n + (*str - '0')) > 2147483647)
			return (-1);
		if (sign == -1 && ((unsigned int)10 * n + (*str - '0')) > 2147483648)
			return (0);
		n = 10 * n + (*str - '0');
		str++;
	}
	return (sign * n);
}
