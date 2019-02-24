#ifndef VECTOR_H
# define VECTOR_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define	VECTOR_CHAR		0
# define	VECTOR_UCHAR	0
# define	VECTOR_SHORT	1
# define	VECTOR_USHORT	1
# define	VECTOR_INT		2
# define	VECTOR_UINT		2
# define	VECTOR_LONG		3
# define	VECTOR_ULONG	3
# define	VECTOR_FLOAT	4
# define	VECTOR_DOUBLE	5
# define	VECTOR_PTR		6

# define	IVEC_1(vector, index)	(char)vector->get(vector, index)
# define	IVEC_2(vector, index)	(short)vector->get(vector, index)
# define	IVEC_4(vector, index)	(int)vector->get(vector, index)
# define	IVEC_8(vector, index)	(long)vector->get(vector, index)
# define	UVEC_1(vector, index)	(unsigned char)vector->get(vector, index)
# define	UVEC_2(vector, index)	(unsigned short)vector->get(vector, index)
# define	UVEC_4(vector, index)	(unsigned int)vector->get(vector, index)
# define	UVEC_8(vector, index)	(unsigned long)vector->get(vector, index)
# define	FVEC(vector, index)		(float)vector->get(vector, index)
# define	DVEC(vector, index)		(double)vector->get(vector, index)
# define	SVEC(vector, index)		(char*)vector->get(vector, index)
# define	PVEC(vector, index)		(void*)vector->get(vector, index)


typedef long				t_all;
typedef struct s_vector		t_vector;

struct s_vector
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
	const int	len;
};

t_vector	*new_vector(int type);

#endif
