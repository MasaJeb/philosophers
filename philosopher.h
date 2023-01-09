/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbejaoui <sbejaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 11:51:02 by sbejaoui          #+#    #+#             */
/*   Updated: 2022/01/31 17:27:40 by sbejaoui         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define FRK 5

// libft
# include "libft.h"

// printf
# include <stdio.h>

// write, Open, usleep
# include <unistd.h>

// gettimeofday
# include <sys/time.h>

// pthread_create, pthread_detach, pthread_join, pthread_mutex_init
// pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
# include <pthread.h>

// nph : Number of philos
// ttd : Time to die
// tte : Time to eat
// tts : Time to sleep
// ect : Eating count
typedef struct s_params
{
	int	nph;
	int	ttd;
	int	tte;
	int	tts;
	int	ect;
}	t_params;

// tid : Thread ID
// pos : position
// l : Left
// r : Right
typedef struct s_philo
{
	pthread_t			tid;
	int					pos;
	int					hungry;
	int					phect;
	int					hthinked;
	int					myforkl;
	int					myforkr;
	pthread_mutex_t		*forkl;
	pthread_mutex_t		*forkr;
	struct s_env		*table;
	struct timeval		etime;
	struct timeval		stime;
	struct timeval		end;
	int					*left;
	int					*right;
}	t_philo;

typedef struct s_env
{
	struct s_philo		**philo;
	struct s_philo		*mphilo;
	struct s_params		*set;
	pthread_mutex_t		*write;
	struct timeval		start;
	int					*dead;
}	t_env;

// main.c
unsigned long long	time_ms(struct timeval *start, struct timeval *end);

// parse.c
t_params			*ft_parse(int ac, char **av);

// philofactory.c
void				ft_philofactory(int nph, t_env *table);

// routine.c
void				ft_writertn(t_env *table, int event);
void				*ft_routine(void *tmp);
void				ft_isdying(t_env *table);

// triche.c
void				ft_triche(t_env *table, int *event);
void				ft_triche2(t_env *table);
void				ft_triche3(t_env *table);
void				ft_sleep(int ms, t_env *table);

#endif