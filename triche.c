/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triche.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbejaoui <sbejaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 23:38:27 by sbejaoui          #+#    #+#             */
/*   Updated: 2022/01/31 17:35:12 by sbejaoui         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_sleep(int ms, t_env *table)
{
	int	i;

	i = 0;
	gettimeofday(&table->mphilo->stime, NULL);
	while (time_ms(&table->mphilo->stime,
			&table->mphilo->end) <= ms)
		usleep(50);
	ft_isdying(table);
}

void	ft_triche(t_env *table, int *event)
{
	if (*event == 1)
	{
		gettimeofday(&table->mphilo->etime, NULL);
		table->mphilo->phect++;
		write(1, "is eating\n", 11);
		if (table->set->ect && table->mphilo->phect >= table->set->ect)
		{
			*table->dead = 1;
			*event = 4;
		}
	}
	else if (*event == 3)
		write(1, "is thinking\n", 13);
	else if (*event == 4)
	{
		write(1, "died\n", 6);
		*table->dead = 1;
	}
}

void	ft_triche2(t_env *table)
{
	*table->mphilo->left = 0;
	table->mphilo->myforkl = 1;
	ft_writertn(table, FRK);
	*table->mphilo->right = 0;
	table->mphilo->myforkr = 1;
	ft_writertn(table, FRK);
}

void	ft_triche3(t_env *table)
{
	table->mphilo->hthinked = 0;
	ft_writertn(table, EAT);
	*table->mphilo->left = 1;
	table->mphilo->myforkl = 0;
	*table->mphilo->right = 1;
	table->mphilo->myforkr = 0;
	pthread_mutex_unlock(table->mphilo->forkl);
	pthread_mutex_unlock(table->mphilo->forkr);
	ft_writertn(table, SLEEP);
}
