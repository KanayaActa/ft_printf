/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:33:40 by miwasa            #+#    #+#             */
/*   Updated: 2024/10/30 17:53:18 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "format.h"

size_t	print_sign(int n, int flag)
{
	size_t	ret;

	ret = 0;
	if (n < 0)
		ret = write(1, "-", 1);
	else if (flag & FLAG_SPACE)
		ret = write(1, " ", 1);
	else if (flag & FLAG_SIGN)
		ret = write(1, "+", 1);
	return (ret);
}
