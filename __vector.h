#ifndef __VECTOR_H
# define __VECTOR_H

# include "vector.h"

# define VECTOR_BLOCK	64

typedef struct s_vector_sys	t_vector_sys;

struct s_vector_sys
{
	// PUBLIC
	void		(*push_back)(t_vector*, t_all);
	void		(*push_front)(t_vector*, t_all);
	void		(*insert)(t_vector*, t_all, int);
	t_all		(*delete)(t_vector*, int);
	t_all		(*pop_back)(t_vector*);
	t_all		(*pop_front)(t_vector*);
	void		*(*free)(t_vector*);
	void		(*reduce)(t_vector*);
	t_all		(*get)(t_vector*, int);
	// READ ONLY
	int			len;
	// PRIVATE
	char		*tab;
	int			rem;
	int			elem;
	int			type;
};

void		vector_reduce(t_vector *this);
t_all		vector_delete(t_vector *usr_this, int index);
void		vector_insert(t_vector *usr_this, t_all val, int index);
void		vector_push_front(t_vector *usr_this, t_all val);
void		vector_push_back(t_vector *usr_this, t_all val);
t_all		vector_pop_front(t_vector *usr_this);
t_all		vector_pop_back(t_vector *this);
t_all		vector_get_index(t_vector *this, int i);
void		*vector_free(t_vector *this);

#endif
