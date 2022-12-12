#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stddef.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/mman.h>
# include "./libftprintf/libftprintf.h"

# define TINY_HEAP_ALLOC_SIZE			(size_t)(4 * getpagesize())
# define TINY_BLOCK_SIZE				(size_t)(TINY_HEAP_ALLOC_SIZE / 128)
# define is_tiny_block(block)			(block->data_size <= TINY_BLOCK_SIZE)
# define is_tiny_heap(heap)				(heap->size == TINY_HEAP_ALLOC_SIZE)

# define SMALL_HEAP_ALLOC_SIZE			(size_t)(16 * getpagesize())
# define SMALL_BLOCK_SIZE				(size_t)(SMALL_HEAP_ALLOC_SIZE / 128)
# define is_small_block(block)			(block->data_size <= SMALL_BLOCK_SIZE && block->data_size > TINY_BLOCK_SIZE)
# define is_small_heap(heap)			(heap->size == SMALL_HEAP_ALLOC_SIZE)

# define BLOCK_HEADER_SIZE				sizeof(t_block)
# define HEAP_HEADER_SIZE				sizeof(t_heap)
# define is_large_block(block)			(block->data_size > SMALL_BLOCK_SIZE)
# define large_heap_alloc_size(size)	(size_t)(size + sizeof(t_heap) + sizeof(t_block))

typedef struct		s_heap
{
	struct s_heap	*prev;
	struct s_heap	*next;
	size_t			size;
	size_t			free_size;
	size_t			block_count;
}					t_heap;

# define heap2block(heap)		(t_block*)((size_t)heap + sizeof(t_heap))

typedef struct		s_block
{
	struct s_block	*prev;
	struct s_block	*next;
	size_t			data_size;
	bool			freed;
}					t_block;

# define block2mem(p)			(void*)((size_t)p + sizeof(t_block))
# define mem2block(mem)			(t_block*)((size_t)mem - sizeof(t_block))
# define nextblock(block, size)	(t_block*)((size_t)block + sizeof(t_block) + size)

t_heap *g_heap_list;

/*
**	Memory management
*/

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

/*
**	Debug
*/

void show_alloc_mem(void);
void show_alloc_mem_ex(void);

/*
**	Block management helper
*/

t_heap	*block2heap(t_block *block);
t_block	*merge_block(t_block *block);
void	init_block(t_block *block, size_t size, bool freed, t_block *next_block, t_block *prev_block);
t_block *defragment(t_block *block);

#endif // LIBFT_MALLOC_H
