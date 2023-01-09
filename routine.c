/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbejaoui <sbejaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:50:08 by sbejaoui          #+#    #+#             */
/*   Updated: 2023/01/09 18:47:53 by sbejaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "libft.h"

void	ft_isdying(t_env *table)
{
	// ft_putnbr_fd(table->mphilo->pos, 1);
	// ft_putstr_fd(" Philo time from sleep : ", 1);
	// ft_putnbr_fd((int)time_ms(&table->mphilo->etime, &table->mphilo->end), 1);
	// ft_putstr_fd("\n", 1);
	if (time_ms(&table->mphilo->etime, &table->mphilo->end) >= (unsigned long long)table->set->ttd)
		ft_writertn(table, DIE);
}

void	ft_wait(t_env *table, int event)
{
	ft_isdying(table);
	if (event == 1)
		ft_sleep(table->set->tte, table);
	else if (event == 2)
		ft_sleep(table->set->tts, table);
	else if (event == 3)
	{
		table->mphilo->hthinked = 1;
		while (!table->mphilo->hungry)
			ft_sleep(1, table);
	}
}

void	ft_writertn(t_env *table, int event)
{
	pthread_mutex_lock(table->write);
	if (!*table->dead)
	{
		ft_putnbr_fd(time_ms(&table->start, &table->mphilo->end), 1);
		write(1, " ", 2);
		ft_putnbr_fd(table->mphilo->pos, 1);
		write(1, " ", 2);
		if (event == 5)
			write(1, "has taken a fork\n", 18);
		else if (event == 2)
		{
			gettimeofday(&table->mphilo->stime, NULL);
			write(1, "is sleeping\n", 13);
		}
		else if (event == 3 || event == 4 || event == 1)
			ft_triche(table, &event);
		pthread_mutex_unlock(table->write);
		if (event >= 1 && event <= 3)
			ft_wait(table, event);
		ft_isdying(table);
	}
	else
		pthread_mutex_unlock(table->write);
}

void	ft_eat(t_env *table)
{
	if (table->mphilo->left == table->mphilo->right && !table->mphilo->myforkl)
	{
		*table->mphilo->left = 0;
		table->mphilo->myforkl = 1;
		ft_writertn(table, FRK);
	}
	else if (table->mphilo->left && *table->mphilo->right && !*table->dead)
	{
		// ft_isdying(table);
		pthread_mutex_lock(table->mphilo->forkl);
		pthread_mutex_lock(table->mphilo->forkr);
		if (!*table->dead && *table->mphilo->left)
			ft_triche2(table);
		if (!*table->dead && table->mphilo->myforkl)
			ft_triche3(table);
		else
		{
			pthread_mutex_unlock(table->mphilo->forkl);
			pthread_mutex_unlock(table->mphilo->forkr);
		}
	}
}

void	*ft_routine(void *tmp)
{
	t_philo			*tpm;
	t_env			*table;

	tpm = (t_philo *)tmp;
	table = tpm->table;
	table->mphilo = tpm;
	while (1)
	{
		// ft_putnbr_fd(*table->dead, 1);
		// ft_putstr_fd("\n", 1);
		if (*table->dead)
			return (NULL);
		ft_eat(table);
		if (!table->mphilo->hthinked)
			ft_writertn(table, THINK);
		ft_isdying(table);
	}
}
