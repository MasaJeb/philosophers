/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbejaoui <sbejaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:50:48 by sbejaoui          #+#    #+#             */
/*   Updated: 2022/01/27 23:11:26 by sbejaoui         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_errac(int ac)
{
	if (ac >= 6)
	{
		ft_putstr_fd("ERROR(1B)\nToo much Args\n", 2);
		exit(-1);
	}
	ft_putstr_fd("ERROR(1A)\nMissing Arg(s)\n", 2);
	if (ac <= 4)
		ft_putstr_fd(" Time to sleep", 2);
	if (ac <= 3)
		ft_putstr_fd(", Time to eat", 2);
	if (ac <= 2)
		ft_putstr_fd(", Time to die", 2);
	if (ac == 1)
		ft_putstr_fd(", Number of philosophers", 2);
	write(2, "\n", 1);
	exit(-1);
}

void	ft_erravdigit(int avi, int bool)
{
	if (!bool)
		ft_putstr_fd("ERROR(2A)\nNot Digit Arg\n", 2);
	else
		ft_putstr_fd("ERROR(2B)\nNegative Arg\n", 2);
	if (avi == 1)
		ft_putstr_fd(" ARG 1 : Number of philosophers", 2);
	if (avi == 2)
		ft_putstr_fd(" ARG 2 : Time to die", 2);
	if (avi == 3)
		ft_putstr_fd(" ARG 3 : Time to eat", 2);
	if (avi == 4)
		ft_putstr_fd(" ARG 4 : Time to die", 2);
	if (avi == 5)
		ft_putstr_fd(" ARG 5 : number_of_times_philosopher_eat", 2);
	write(2, "\n", 1);
	exit(-2);
}

void	ft_erravnull(int avi)
{
	ft_putstr_fd("ERROR(3)\nNULL Arg\n", 2);
	if (avi == 1)
		ft_putstr_fd(" ARG 1 : Number of philosophers", 2);
	if (avi == 2)
		ft_putstr_fd(" ARG 2 : Time to die", 2);
	if (avi == 3)
		ft_putstr_fd(" ARG 3 : Time to eat", 2);
	if (avi == 4)
		ft_putstr_fd(" ARG 4 : Time to die", 2);
	if (avi == 5)
		ft_putstr_fd(" ARG 5 : number_of_times_philosopher_eat", 2);
	write(2, "\n", 1);
	exit(-3);
}

void	ft_verifav(int ac, char **av)
{
	int		i;
	int		j;

	if (ac <= 4 || ac > 6)
		ft_errac(ac);
	i = 1;
	while (i < ac)
	{
		j = 0;
		if (!av[i][j])
			ft_erravnull(i);
		while (av[i][j])
		{
			if (av[i][j] && (!ft_isdigit(av[i][j]) && av[i][0] != '+'
			&& av[i][0] != '-'))
				ft_erravdigit(i, 0);
			if (av[i][0] == '-')
				ft_erravdigit(i, 1);
			j++;
		}
		i++;
	}
}

t_params	*ft_parse(int ac, char **av)
{
	t_params	*prm;
	int			i;

	ft_verifav(ac, av);
	prm = malloc(sizeof(t_params));
	prm->nph = atoi(av[1]);
	prm->ttd = atoi(av[2]);
	prm->tte = atoi(av[3]);
	prm->tts = atoi(av[4]);
	if (ac == 6)
		prm->ect = atoi(av[5]);
	else
		prm->ect = 0;
	return (prm);
}
