/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:49:14 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/02/10 12:07:32 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			time_last_meal;
	int				c_meals;
	struct s_tools	*tools;
}	t_philo;

typedef struct s_tools
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	status;
	pthread_mutex_t	meal_time;
	bool			end;
	long			start_time;
	int				num_p;
	int				time_d;
	int				time_e;
	int				time_s;
	int				num_e;
}	t_tools;

// ft_atoi
int		ft_atoi(const char *str, int *ret);

// utils
void	free_philo_and_forks(t_tools *tools);
void	print_lock(char *str, int id, t_tools *tools, long ms);
int		join_threads(t_tools *tools);

// mutex
int		check_end(t_tools *tools);
void	change_end(t_tools *tools);
void	set_m_t(t_philo *philo);
long	read_m_t(t_philo *philo);

// philo
void	*life(void *tmp);

// monitoring
void	monitoring_wrapper(t_tools *tools);

// time
long	elapsed(long start);
long	find_ms(void);

#endif