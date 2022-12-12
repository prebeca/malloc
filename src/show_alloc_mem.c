#include "libft_malloc.h"

void show_alloc_mem_ex(void)
{
	t_heap	*heap_iter = g_heap_list;

	while (heap_iter)
	{
		size_t end = (size_t)heap_iter + heap_iter->size;
		unsigned char *addr = (unsigned char*)heap_iter;
		while ((size_t)addr <= end)
		{
			ft_printf("%X ", addr);
			int i = 0;
			while (i < 8)
				ft_printf(" %02X", *(addr + i++));
			ft_printf(" ");
			while (i < 16)
				ft_printf(" %02X", *(addr + i++));
			ft_printf("  | ");
			write(STDOUT_FILENO, addr, 16);
			ft_printf(" |\n");
			addr += 16;
		}
		heap_iter = heap_iter->next;
	}
}

void show_alloc_mem(void)
{
	size_t	total_alloc = 0;
	t_heap	*heap_iter = g_heap_list;
	t_block	*block_iter = NULL;

	while (heap_iter)
	{
		block_iter = heap2block(heap_iter);

		if (heap_iter->size == TINY_HEAP_ALLOC_SIZE)
			ft_printf("TINY");
		else if (heap_iter->size == SMALL_HEAP_ALLOC_SIZE)
			ft_printf("SMALL");
		else
			ft_printf("LARGE");

		ft_printf(" :\t%p | %d blocks\n", block_iter, heap_iter->block_count);

		while (block_iter)
		{
			if (!block_iter->freed)
			{
				printf("\t%p - %p : %zu bytes\n", block2mem(block_iter), block2mem(block_iter) + block_iter->data_size, block_iter->data_size);
				total_alloc += block_iter->data_size;
			}

			block_iter = block_iter->next;
		}

		heap_iter = heap_iter->next;
	}
	ft_printf("Total : %u bytes\n", total_alloc);
}