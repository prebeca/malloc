#include "libft_malloc.h"

void *realloc_malloc_cpy(void *old_ptr, size_t new_size)
{
	void *new_ptr = NULL;
	
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (0);

	ft_memmove(new_ptr, old_ptr, (mem2block(old_ptr))->data_size);
	
	free(old_ptr);
	
	return (new_ptr);
}

void *realloc_shrink(void *ptr, size_t size)
{
	t_block	*block = NULL;
	size_t	remaining_space;

	block = mem2block(ptr);

	// if not enough remaining space to create a new free block, do nothing
	if (block->data_size - size < BLOCK_HEADER_SIZE)
		return (ptr);

	// resize block and create a new free block with remaining space, then defragment adjacent memory
	remaining_space = block->data_size - size;

	block->data_size = size;
	init_block(nextblock(block, block->data_size), remaining_space, true, block->next, block);
	block->next = nextblock(block, block->data_size);
	defragment(block->next);

	return (ptr);
}

void *realloc_enlarge(void *ptr, size_t size)
{
	t_block	*block = NULL;
	size_t	additional_space_request;
	size_t remaining_space;

	block = mem2block(ptr);
	additional_space_request = size - block->data_size;

	// if enought free space after current block, use part or all of the next block free space, else allocate new block
	if (block->next && block->next->freed && block->next->data_size + BLOCK_HEADER_SIZE >= additional_space_request)
	{
		remaining_space = block->next->data_size + BLOCK_HEADER_SIZE - additional_space_request;

		merge_block(block);
		if (remaining_space > BLOCK_HEADER_SIZE)
		{
			block->data_size = size;
			init_block(nextblock(block, block->data_size), remaining_space, true, block->next, block);
			block->next = nextblock(block, block->data_size);
		}
		return (ptr);
	}

	return (realloc_malloc_cpy(ptr, size));
}


void *realloc(void *ptr, size_t size)
{
	t_block *block = mem2block(ptr);

	// if null ptr act like malloc
	if (ptr == NULL)
		return (malloc(size));

	// if 0 size act like free
	if (size == 0){
		free(ptr);
		return (0);
	}

	// if no change in size do nothing
	if (size == block->data_size)
		return (ptr);

	// if new size is smaller than data_size, shrink the block
	if (size < block->data_size)
		return (realloc_shrink(ptr, size));

	// if new size is bigger than current block max size, reallocate in correct zone
	if ((is_tiny_block(block) && size > TINY_BLOCK_SIZE) || 
		(is_small_block(block) && size > SMALL_BLOCK_SIZE))
		return (realloc_malloc_cpy(ptr, size));

	return (realloc_enlarge(ptr, size));
}