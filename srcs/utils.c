/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 11:28:17 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/10 12:39:11 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo_and_forks(t_tools *tools)
{
	free(tools->philo);
	free(tools->forks);
}

int	join_threads(t_tools *tools)
{
	int	i;

	i = 0;
	while (i < tools->num_p)
	{
		if (pthread_join(tools->philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (1);
}

void	print_lock(char *str, int id, t_tools *tools, long ms)
{
	pthread_mutex_lock(&tools->status);
	if (!tools->end)
		printf("%ld Philosopher %i %s\n", ms, id, str);
	pthread_mutex_unlock(&tools->status);
}
