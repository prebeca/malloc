#include "libft_malloc.h"

void free(void *ptr)
{
	if (ptr == NULL)
		return;

	t_block *block = mem2block(ptr);
	block->freed = true;

	defragment(block);

	t_heap *heap = block2heap(block);
	--heap->block_count;

	if (heap->block_count > 0)
		return;

	if (heap->prev)
		heap->prev->next = heap->next;
	if (heap->next)
		heap->next->prev = heap->prev;
	if (heap == g_heap_list)
		g_heap_list = heap->next;
	munmap(heap, heap->size);
}