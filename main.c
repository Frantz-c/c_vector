#include "vector.h"

int main(void)
{
	t_vector	*vec;

	/*
	**	Allocate a new vector of type VECTOR_(type)
	**
	** if type is VECTOR_PTR, pointers will be free
	** when calling t_vector->free(),
	** t_vector->delete() or t_vector->pop_*()
	*/
	vec = new_vector(VECTOR_INT);

	vec->push_front(vec, 0);	// {0}
	vec->push_back(vec, 1);		// {0, 1}
	vec->push_back(vec, 2);		// {0, 1, 2}
	vec->push_back(vec, 155);	// {0, 1, 2, 155}
	vec->push_front(vec, -1);	// {-1, 0, 1, 2, 155}
	vec->insert(vec, 3, 4);		// {-1, 0, 1, 2, 3, 155}
	vec->delete(vec, 0);		// {0, 1, 2, 3, 155}
	// delete() return poped value or NULL if it's a pointer
	// cast the return value to avoid warning. ?
	vec->pop_back(vec);			// {0, 1, 2, 3}
	// pop_*() return poped value or NULL if it's a pointer
	// cast the return value to avoid warning. ?

	for (int n = 4; n < 70; ++n)
		vec->push_back(vec, n);

	for (int i = 0; i < vec->len; i++)
		printf("vec[%d] = %d\n", i, IVEC_4(vec, i));

	/*
	** free() return always NULL
	*/
	vec = vec->free(vec);
	return (0);
}
