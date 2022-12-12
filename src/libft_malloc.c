#include "libft_malloc.h"

t_heap *g_heap_list = NULL;

t_heap *block2heap(t_block *block)
{
	while (block->prev)
		block = block->prev;
	return ((t_heap*)((size_t)block - HEAP_HEADER_SIZE));
}

t_block *merge_block(t_block *block)
{
	block->data_size += block->next->data_size + BLOCK_HEADER_SIZE;
	block->next = block->next->next;
	return (block);
}

void	init_block(t_block *block, size_t size, bool freed, t_block *next_block, t_block *prev_block)
{
	block->data_size = size - BLOCK_HEADER_SIZE;
	block->freed = freed;
	block->next = next_block;
	block->prev = prev_block;
}

t_block *defragment(t_block *block)
{
	t_block *prev = block->prev;
	t_block *next = block->next;

	if (next && next->freed)
		block = merge_block(block);
	
	if (prev && prev->freed)
		block = merge_block(prev);
	
	return (block);
}