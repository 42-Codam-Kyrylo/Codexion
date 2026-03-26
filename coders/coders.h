/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coders.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/24 20:16:39 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/03/26 16:18:59 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// compile -> debug -> refactor

#ifndef CODERS_H
# define CODERS_H

# include <pthread.h>

typedef enum e_sched
{
	CODERS_SCHED_FIFO,
	CODERS_SCHED_EDF,
}					t_sched;

typedef enum e_coder_status
{
	CODER_COMPILE,
	CODER_DEBUG,
	CODER_REFACTOR,
}					t_coder_status;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_coder_status	status;
	t_data			*data;
	long long		last_compiling_at;
}					t_coder;

typedef enum e_dongle_status
{
	DONGLE_FREE,
	DONGLE_OCCUPIED,
}					t_dongle_status;

typedef struct s_dongle
{
	int				id;
	t_dongle_status	status;
	long long		last_released_at;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}					t_dongle;

typedef struct s_data
{
	int				number_of_coders;
	long long		time_to_burnout;
	long long		time_to_compile;
	long long		time_to_debug;
	long long		time_to_refactor;
	int				number_of_compiles_required;

	long long		dongle_cooldown;
	t_sched			scheduler;

	pthread_mutex_t	print_mutex;
	t_coder			*coders;
	t_dongle		*dongles;
}					t_data;

int					parse(t_data *data, int argc, char *argv[]);
int					ft_isdigit(int c);
int					ft_isdigitstr(char *s);
long long			ft_atoll(const char *str);
long long			get_current_time(void);

#endif
