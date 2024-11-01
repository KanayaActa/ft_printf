/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_padding.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:09:35 by miwasa            #+#    #+#             */
/*   Updated: 2024/10/30 23:29:31 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "format.h"

int	print_padding(t_printf_opts *fmt_opts, int len, int after)
{
	int		i;
	size_t	ret;
	int		bytes_read;
	char	fill_char;

	i = 0;
	ret = 0;
	if ((fmt_opts->flag & FLAG_ZERO) && !after)
		fill_char = '0';
	else
		fill_char = ' ';
	if (fmt_opts->width != -1 && !((fmt_opts->flag & FLAG_LEFT) || after))
	{
		while (fmt_opts->width - len > i)
		{
			bytes_read = write(1, &fill_char, 1);
			if (bytes_read == -1)
				return (bytes_read);
			ret += bytes_read;
			i++;
		}
	}
	return (ret);
}
