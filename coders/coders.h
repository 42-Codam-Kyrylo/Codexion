/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coders.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/03/24 20:16:39 by kvolynsk      #+#    #+#                 */
/*   Updated: 2026/03/31 21:02:25 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// compile -> debug -> refactor
// deadline = last_compile_start + time_to_burnout

#ifndef CODERS_H
# define CODERS_H

# include <pthread.h>

typedef struct s_data	t_data;

typedef enum e_sched
{
	CODERS_SCHED_FIFO,
	CODERS_SCHED_EDF,
}						t_sched;

typedef enum e_coder_status
{
	CODER_INITIALIZING,
	CODER_REQUESTING,
	CODER_COMPILE,
	CODER_DEBUG,
	CODER_REFACTOR,
	CODER_BURNED_OUT,
}						t_coder_status;

typedef struct s_node
{
	int					coder_id;
	long long priority; // for edf - deadline time, for FIFO - request time
}						t_node;

typedef struct s_heap
{
	t_node				*array;
	int					size;
	int					capacity;
}						t_heap;

typedef struct s_coder
{
	int					id;
	pthread_t			thread;
	t_coder_status		status;
	t_data				*data;
	long long			last_compiling_at;
	int					compiles_done;
}						t_coder;

typedef enum e_dongle_status
{
	DONGLE_FREE,
	DONGLE_OCCUPIED,
}						t_dongle_status;

typedef struct s_dongle
{
	int					id;
	t_dongle_status		status;
	long long			last_released_at;
	t_heap				queue;
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
}						t_dongle;

struct					s_data
{
	int					number_of_coders;
	long long			time_to_burnout;
	long long			time_to_compile;
	long long			time_to_debug;
	long long			time_to_refactor;
	int					number_of_compiles_required;

	long long			dongle_cooldown;

	long long			start_time;
	int					simulation_end;
	// pthread_mutex_t stop_mutex;??
	t_sched				scheduler;

	pthread_mutex_t		print_mutex;
	pthread_t			monitor;
	t_coder				*coders;
	t_dongle			*dongles;
};

int						parse(t_data *data, int argc, char *argv[]);
int						ft_isdigit(int c);
int						ft_isdigitstr(char *s);
long long				ft_atoll(const char *str);
long long				get_current_time(void);

// heap
t_heap					*create_heap(int capacity);
void					swap_heap(t_node *a, t_node *b);
void					insert_heap(t_heap *heap, t_node node);
t_node					pop_heap(t_heap *heap);

int						get_left_child(int i);
int						get_right_child(int i);
int						get_parent(int i);

int						init_coders(t_data *data);
void					*coder_routine(void *arg);
int						start_coders(t_data *data);
int						join_coders(t_data *data);
int						init_start_time(t_data *data);

#endif
