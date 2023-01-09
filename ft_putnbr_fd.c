/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbejaoui <sbejaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:23:41 by sbejaoui          #+#    #+#             */
/*   Updated: 2021/11/05 20:48:21 by sbejaoui         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	int	diviseurb;

	diviseurb = 10;
	if (nb == -2147483648)
		write(fd, "-2147483648", 11);
	else if (nb < 0)
	{
		ft_putchar('-', fd);
		nb *= -1;
	}	
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar((nb % 10) + '0', fd);
	}
	else if (nb < 10 && nb >= 0)
		ft_putchar(nb + '0', fd);
}
