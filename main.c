/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbejaoui <sbejaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:51:20 by sbejaoui          #+#    #+#             */
/*   Updated: 2022/01/31 18:01:11 by sbejaoui         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned long long	time_ms(struct timeval *start, struct timeval *end)
{
	gettimeofday(end, NULL);
	return ((end->tv_sec - start->tv_sec) * 1000
		+ (end->tv_usec - start->tv_usec) / 1000);
}

void	ft_freephilo(t_philo *p)
{
	free(p->left);
	free(p->forkl);
	free(p->table);
	free(p);
}

void	ft_freeall(t_env table)
{
	int	i;

	i = 0;
	while (i < table.set->nph)
	{
		pthread_detach(table.philo[i]->tid);
		ft_freephilo(table.philo[i++]);
	}
	free(table.philo);
	free(table.dead);
	free(table.write);
	free(table.set);
}

int	main(int ac, char **av)
{
	t_env		table;
	int			i;

	table.set = ft_parse(ac, av);
	ft_philofactory(table.set->nph, &table);
	table.write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table.write, NULL);
	gettimeofday(&table.start, NULL);
	i = 0;
	while (i < table.set->nph)
	{
		*table.philo[i]->table = table;
		pthread_mutex_init(table.philo[i]->forkl, NULL);
		pthread_mutex_init(table.philo[i]->forkr, NULL);
		gettimeofday(&table.philo[i]->etime, NULL);
		pthread_create(&table.philo[i]->tid, NULL,
			&ft_routine, (void *)table.philo[i]);
		i++;
	}
	i = 0;
	while (i < table.set->nph)
		pthread_join(table.philo[i++]->tid, NULL);
	ft_freeall(table);
	return (0);
}
