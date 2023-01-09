/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philofactory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbejaoui <sbejaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:04:46 by sbejaoui          #+#    #+#             */
/*   Updated: 2022/01/31 17:42:50 by sbejaoui         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_philoassembly(t_env *table, int i, int nph)
{
	while (i < nph)
	{
		(table->philo[i])->pos = i + 1;
		*(table->philo[i])->left = 1;
		table->philo[i]->phect = 0;
		if (i == nph - 1)
		{
			(table->philo[i])->right = (table->philo[0])->left;
			(table->philo[i])->forkr = (table->philo[0])->forkl;
		}
		else
		{
			(table->philo[i])->right = table->philo[i + 1]->left;
			(table->philo[i])->forkr = table->philo[i + 1]->forkl;
		}
		if (i % 2 == 0)
			(table->philo[i])->hungry = 1;
		table->philo[i]->hthinked = 0;
		i++;
	}
}

void	ft_philofactory(int nph, t_env *table)
{
	t_philo	*philo;
	int		i;
	int		j;

	i = 0;
	table->philo = malloc(sizeof(t_philo *) * nph);
	table->dead = malloc(sizeof(int));
	*table->dead = 0;
	while (i < nph)
	{
		(table->philo[i]) = malloc(sizeof(t_philo));
		table->philo[i]->left = malloc(sizeof(int));
		table->philo[i]->forkl = malloc(sizeof(pthread_mutex_t));
		table->philo[i]->table = malloc(sizeof(t_env));
		i++;
	}
	i = 0;
	ft_philoassembly(table, i, nph);
}
