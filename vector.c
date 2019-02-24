#include "__vector.h"
#include "vector.h"

static int	get_size(int type)
{
	static const void *const	jump[] =
	{
		&&vector_char,
		&&vector_short,
		&&vector_int,
		&&vector_long,
		&&vector_float,
		&&vector_double,
		&&vector_ptr
	};

	goto *(jump[type]);
	vector_char:
		return (1);
	vector_short:
		return (sizeof(short));
	vector_int:
		return (sizeof(int));
	vector_long:
		return (sizeof(long));
	vector_float:
		return (sizeof(float));
	vector_double:
		return (sizeof(double));
	vector_ptr:
		return (sizeof(char*));
}

t_vector	*new_vector(int type)
{
	t_vector_sys	*new;

	if (type > 6 || type < 0 || (new = malloc(sizeof(t_vector_sys))) == NULL)
		return (NULL);
	new->push_back = &vector_push_back;
	new->push_front = &vector_push_front;
	new->pop_back = &vector_pop_back;
	new->pop_front = &vector_pop_front;
	new->insert = &vector_insert;
	new->delete = &vector_delete;
	new->get = &vector_get_index;
	new->free = &vector_free;
	new->reduce = &vector_reduce;
	new->len = 0;
	new->type = type;
	new->elem = get_size(type);
	new->rem = VECTOR_BLOCK;
	new->tab = malloc(new->elem * VECTOR_BLOCK);
	if (!new->tab)
	{
		free(new);
		return (NULL);
	}
	return ((t_vector*)new);
}

static int	vector_new_alloc_after_index(t_vector_sys *this, int index)
{
	char	*new;

	new = realloc(this->tab, this->elem * (this->len + VECTOR_BLOCK));
	if (!new)
	{
		free(this->tab);
		this->tab = NULL;
		this->len = 0;
		this->rem = 0;
		return (-1);
	}
	this->tab = new;
	this->rem += VECTOR_BLOCK;
	memcpy(this->tab, this->tab + index * this->elem, this->elem * (this->len - index));
	return (0);
}

static int	vector_new_alloc_after(t_vector_sys *this)
{
	char	*new;

	new = realloc(this->tab, this->elem * (this->len + VECTOR_BLOCK));
	if (!new)
	{
		free(this->tab);
		this->tab = NULL;
		this->len = 0;
		this->rem = 0;
		return (-1);
	}
	this->tab = new;
	this->rem += VECTOR_BLOCK;
	memcpy(this->tab + this->elem, this->tab, this->elem * this->len);
	return (0);
}

static int	vector_new_alloc(t_vector_sys *this)
{
	char	*new;

	new = realloc(this->tab, this->elem * (this->len + VECTOR_BLOCK));
	if (!new)
	{
		free(this->tab);
		this->tab = NULL;
		this->len = 0;
		this->rem = 0;
		return (-1);
	}
	this->tab = new;
	this->rem += VECTOR_BLOCK;
	return (0);
}

void		vector_reduce(t_vector *this)
{
	(void)this;
}

t_all		vector_delete(t_vector *usr_this, int index)
{
	static const void *const	jump[] =
	{
		&&vector_char,
		&&vector_short,
		&&vector_int,
		&&vector_long,
		&&vector_float,
		&&vector_double,
		&&vector_ptr
	};
	register t_vector_sys	*this;
	t_all					ret;

	this = (t_vector_sys*)usr_this;
	this->len--;
	this->rem++;

	goto *(jump[this->type]);
	vector_char:
		ret = (t_all)this->tab[index];
		goto end;
	vector_short:
		ret = (t_all)((short*)this->tab)[index];
		goto end;
	vector_int:
		ret = (t_all)((int*)this->tab)[index];
		goto end;
	vector_long:
		ret = (t_all)((long*)this->tab)[index];
		goto end;
	vector_float:
		ret = (t_all)((float*)this->tab)[index];
		goto end;
	vector_double:
		ret = (t_all)((double*)this->tab)[index];
		goto end;
	vector_ptr:
		ret = 0;
		free(((char**)this->tab)[index]);
	end:
		memmove(this->tab + index * this->elem, this->tab + (index + 1) * this->elem, this->len * this->elem);
	return (ret);
}

void		vector_insert(t_vector *usr_this, t_all val, int index)
{
	static const void *const	jump[] =
	{
		&&vector_char,
		&&vector_short,
		&&vector_int,
		&&vector_long,
		&&vector_float,
		&&vector_double,
		&&vector_ptr
	};
	register t_vector_sys	*this = (t_vector_sys*)usr_this;

	if (this->rem == 0)
	{
		if (vector_new_alloc_after_index(this, index) == -1)
			return ;
	}
	else
		memmove(this->tab + (index + 1) * this->elem, this->tab + index * this->elem, this->len * this->elem);
	this->len++;
	this->rem--;

	goto *(jump[this->type]);
	vector_char:	
		this->tab[index] = (char)val;
		return ;
	vector_short:
		((short*)this->tab)[index] = (short)val;
		return ;
	vector_int:
		((int*)this->tab)[index] = (int)val;
		return ;
	vector_long:
		((long*)this->tab)[index] = (long)val;
		return ;
	vector_float:
		((float*)this->tab)[index] = (float)val;
		return ;
	vector_double:
		((double*)this->tab)[index] = (double)val;
		return ;
	vector_ptr:
		((char**)this->tab)[index] = (char*)val;
}

void		vector_push_front(t_vector *usr_this, t_all val)
{
	static const void *const	jump[] =
	{
		&&vector_char,
		&&vector_short,
		&&vector_int,
		&&vector_long,
		&&vector_float,
		&&vector_double,
		&&vector_ptr
	};
	register t_vector_sys	*this = (t_vector_sys*)usr_this;

	if (this->rem == 0)
	{
		if (vector_new_alloc_after(this) == -1)
			return ;
	}
	else
		memmove(this->tab + this->elem, this->tab, this->len * this->elem);
	this->len++;
	this->rem--;

	goto *(jump[this->type]);
	vector_char:
		this->tab[0] = (char)val;
		return ;
	vector_short:
		((short*)this->tab)[0] = (short)val;
		return ;
	vector_int:
		((int*)this->tab)[0] = (int)val;
		return ;
	vector_long:
		((long*)this->tab)[0] = (long)val;
		return ;
	vector_float:
		((float*)this->tab)[0] = (float)val;
		return ;
	vector_double:
		((double*)this->tab)[0] = (double)val;
		return ;
	vector_ptr:
		((char**)this->tab)[0] = (char*)val;
}

void		vector_push_back(t_vector *usr_this, t_all val)
{
	static const void *const	jump[] =
	{
		&&vector_char,
		&&vector_short,
		&&vector_int,
		&&vector_long,
		&&vector_float,
		&&vector_double,
		&&vector_ptr
	};
	register t_vector_sys	*this = (t_vector_sys*)usr_this;

	if (this->rem == 0)
	{
		if (vector_new_alloc(this) == -1)
			return ;
	}
	this->rem--;

	goto *(jump[this->type]);
	vector_char:
		this->tab[this->len++] = (char)val;
		return ;
	vector_short:
		((short*)this->tab)[this->len++] = (short)val;
		return ;
	vector_int:
		((int*)this->tab)[this->len++] = (int)val;
		return ;
	vector_long:
		((long*)this->tab)[this->len++] = (long)val;
		return ;
	vector_float:
		((float*)this->tab)[this->len++] = (float)val;
		return ;
	vector_double:
		((double*)this->tab)[this->len++] = (double)val;
		return ;
	vector_ptr:
		((char**)this->tab)[this->len++] = (char*)val;
		return ;
}

t_all		vector_pop_front(t_vector *usr_this)
{
	static const void *const	jump[] =
	{
		&&vector_char,
		&&vector_short,
		&&vector_int,
		&&vector_long,
		&&vector_float,
		&&vector_double,
		&&vector_ptr
	};
	register t_vector_sys	*this = (t_vector_sys*)usr_this;
	t_all					ret;

	this->len--;
	this->rem++;
	goto *(jump[this->type]);
	vector_char:
		ret = (t_all)this->tab[0];
		goto end;
	vector_short:
		ret = (t_all)((short*)this->tab)[0];
		goto end;
	vector_int:
		ret = (t_all)((int*)this->tab)[0];
		goto end;
	vector_long:
		ret = (t_all)((long*)this->tab)[0];
		goto end;
	vector_float:
		ret = (t_all)((float*)this->tab)[0];
		goto end;
	vector_double:
		ret = (t_all)((double*)this->tab)[0];
		goto end;
	vector_ptr:
		ret = 0;
		free(((char**)this->tab)[0]);
	end:
		memmove(this->tab, this->tab + this->elem, this->len * this->elem);
	return (ret);
}

t_all		vector_pop_back(t_vector *usr_this)
{
	static const void *const	jump[] =
	{
		&&vector_char,
		&&vector_short,
		&&vector_int,
		&&vector_long,
		&&vector_float,
		&&vector_double,
		&&vector_ptr
	};
	t_vector_sys	*this = (t_vector_sys*)usr_this;

	this->len--;
	this->rem++;
	goto *(jump[this->type]);
	vector_char:
		return (this->tab[this->len]);
	vector_short:
		return (((short*)this->tab)[this->len]);
	vector_int:
		return (((int*)this->tab)[this->len]);
	vector_long:
		return (((long*)this->tab)[this->len]);
	vector_float:
		return (((float*)this->tab)[this->len]);
	vector_double:
		return (((double*)this->tab)[this->len]);
	vector_ptr:
		free(((char**)this->tab)[this->len]);
	return (0);
}

t_all		vector_get_index(t_vector *usr_this, int i)
{
	t_vector_sys	*this;

	this = (t_vector_sys*)usr_this;
	return (*(t_all*)(this->tab + (i * this->elem)));
}

void		*vector_free(t_vector *usr_this)
{
	t_vector_sys	*this;
	int				i;

	this = (t_vector_sys*)usr_this;
	if (this->type == VECTOR_PTR)
	{
		i = 0;
		while (i < this->len)
			free(((char**)this->tab)[i++]);
	}
	free(this->tab);
	free(this);
	return (NULL);
}
