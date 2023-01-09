/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbejaoui <sbejaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:11:24 by sbejaoui          #+#    #+#             */
/*   Updated: 2023/01/09 18:38:02 by sbejaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_routine(void *tmp)
{
    t_philo	*tpm;
	t_env	*table;

	tpm = (t_philo *)tmp;
	table = tpm->table;
	table->mphilo = tpm;
    while (1)
    {
		if (*table->dead)
			return (NULL);
		if(table->mphilo->myforkl == 1 && table->mphilo->myforkr == 1)
			ft_eat();

    }
}