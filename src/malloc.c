#include "libft_malloc.h"

t_heap	*new_heap(size_t size)
{
	t_heap *new_heap = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

	if (new_heap == MAP_FAILED)
		return (NULL);

	new_heap->block_count = 0;
	new_heap->free_size = size - BLOCK_HEADER_SIZE;
	new_heap->next = NULL;
	new_heap->prev = NULL;
	new_heap->size = size;

	t_block *first_block = heap2block(new_heap);
	init_block(first_block, new_heap->free_size, true, NULL, NULL);

	return (new_heap);
}

void allocate_block(t_block *block, size_t size)
{
	size_t remaining_data_size;
	t_block *new_next_block = NULL;

	remaining_data_size = block->data_size - size;

	if (remaining_data_size > BLOCK_HEADER_SIZE)
	{
		new_next_block = nextblock(block, size);
		init_block(new_next_block, remaining_data_size, true, block->next, block);
		block->next = new_next_block;
		block->data_size = size;
	}

	block->freed = false;
}

void *malloc(size_t size)
{
	t_heap **heap_iter = NULL;
	t_heap *prev_heap = NULL;
	t_block *block_iter;

	// search for free block in correct heap size
	heap_iter = &g_heap_list;
	while (*heap_iter)
	{
		if (size <= SMALL_BLOCK_SIZE)
			if ((size <= TINY_BLOCK_SIZE && is_tiny_heap((*heap_iter))) ||
				(size > TINY_BLOCK_SIZE && is_small_heap((*heap_iter))))
			{
				
				block_iter = heap2block(*heap_iter);
				while (block_iter)
				{
					if (block_iter->freed && block_iter->data_size >= size)
					{
						// free block of corresponding size found
						allocate_block(block_iter, size);
						++(*heap_iter)->block_count;
						return (block2mem(block_iter));
					}
					block_iter = block_iter->next;
				}
			}
		prev_heap = *heap_iter;
		heap_iter = &(*heap_iter)->next;
	}

	// no free block found, create new corresponding heap
	if (size <= TINY_BLOCK_SIZE)
		*heap_iter = new_heap(TINY_HEAP_ALLOC_SIZE);
	else if (size <= SMALL_BLOCK_SIZE)
		*heap_iter = new_heap(SMALL_HEAP_ALLOC_SIZE);
	else
		*heap_iter = new_heap(large_heap_alloc_size(size));

	if (*heap_iter == NULL)
		return (NULL);

	(*heap_iter)->prev = prev_heap;

	block_iter = heap2block(*heap_iter);

	allocate_block(block_iter, size);
	++(*heap_iter)->block_count;
	return (block2mem(block_iter));
}