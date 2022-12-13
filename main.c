#include "libft_malloc.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
	ft_printf("Page size = %d bytes\n", getpagesize());
	ft_printf("heap header size = %d bytes\n", HEAP_HEADER_SIZE);
	ft_printf("block header size = %d bytes\n", BLOCK_HEADER_SIZE);
	ft_printf("TINY heap alloc size = %d bytes\n", TINY_HEAP_ALLOC_SIZE);
	ft_printf("TINY block max size = %d bytes\n", TINY_BLOCK_SIZE);
	ft_printf("SMALL heap alloc size = %d bytes\n", SMALL_HEAP_ALLOC_SIZE);
	ft_printf("SMALL block max size = %d bytes\n\n", SMALL_BLOCK_SIZE);

	t_heap h;
	t_heap *h_p = &h;
	h.size = TINY_HEAP_ALLOC_SIZE;
	ft_printf("is_tiny_heap(TINY_HEAP_ALLOC_SIZE) = %d\n", is_tiny_heap(h_p));
	ft_printf("is_small_heap(TINY_HEAP_ALLOC_SIZE) = %d\n", is_small_heap(h_p));
	h.size = SMALL_HEAP_ALLOC_SIZE;
	ft_printf("is_tiny_heap(SMALL_HEAP_ALLOC_SIZE) = %d\n", is_tiny_heap(h_p));
	ft_printf("is_small_heap(SMALL_HEAP_ALLOC_SIZE) = %d\n\n", is_small_heap(h_p));

	ft_printf("heap adresse = %p\n", (size_t)h_p);
	ft_printf("first block adresse = %p\n", (size_t)heap2block(h_p));
	ft_printf("diff = %u bytes\n\n", (size_t)((void*)heap2block(h_p) - (void*)h_p));

	t_block *b = heap2block(h_p);
	ft_printf("first block adresse = %p\n", (size_t)b);
	ft_printf("mem adresse = %p\n", (size_t)block2mem(b));
	ft_printf("diff = %u bytes\n\n", (size_t)((void*)block2mem(b) - (void*)b));

	char *test = NULL;
	size_t alloc = 0;
	int i = 0;
	void *alloc_tab[150];

#ifdef malloc_test
	ft_putendl_fd("--------------------- TESTING MALLOC ---------------------", STDOUT_FILENO);
	test = malloc(42 * sizeof(char));
	memset(test, 42, 42);
	free(test);
	test = malloc(128 * sizeof(char));
	memset(test, 51, 128);
	free(test);
	test = malloc(129 * sizeof(char));
	memset(test, 69, 129);
	free(test);
	test = malloc(420 * sizeof(char));
	free(test);
	test = malloc(512 * sizeof(char));
	free(test);
	test = malloc(5120 * sizeof(char));
	free(test);
	test = malloc(42 * sizeof(char));
	free(test);
	test = malloc(128 * sizeof(char));
	free(test);
	test = malloc(129 * sizeof(char));
	free(test);
	test = malloc(5120 * sizeof(char));
	free(test);
	show_alloc_mem();
#endif // malloc

#ifdef nb_block
	ft_putendl_fd("--------------------- NB TINY BLOCK IN TINY HEAP ---------------------", STDOUT_FILENO);
	i = 0;
	while (i < 150)
	{
		alloc_tab[i] = malloc(TINY_BLOCK_SIZE);
		++i;
	}

	show_alloc_mem();

	while (i > 0)
	{
		--i;
		free(alloc_tab[i]);
	}

	ft_putendl_fd("--------------------- NB SMALL BLOCK IN SMALL HEAP ---------------------", STDOUT_FILENO);
	i = 0;
	while (i < 150)
	{
		alloc_tab[i] = malloc(SMALL_BLOCK_SIZE);
		++i;
	}

	show_alloc_mem();

	while (i > 0)
	{
		--i;
		free(alloc_tab[i]);
	}
#endif //nb_block

#ifdef realloc_test
	ft_putendl_fd("--------------------- TESTING REALLOC ---------------------", STDOUT_FILENO);
	test = malloc(42 * sizeof(char));
	test = realloc(test, 42);
	test = realloc(test, 84);
	test = realloc(test, 129);
	test = realloc(test, 42);
	free(test);

	alloc = 16;
	test = NULL;
	while (alloc < SMALL_HEAP_ALLOC_SIZE)
	{
		show_alloc_mem();
		test = realloc(test, alloc);
		alloc *= 2;
	}
	free(test);
	test = NULL;
	show_alloc_mem();
#endif	// realloc

#ifdef max_alloc
	ft_putendl_fd("--------------------- MAX ALLOC ---------------------", STDOUT_FILENO);
	alloc = 8;

	test = malloc(alloc);
	free(test);
	while (test != NULL)
	{
		alloc *= 2;
		test = malloc(alloc);
		printf("malloc %16zu bytes: %16p\n", alloc, test);
		free(test);
	}
	ft_putendl_fd("", STDOUT_FILENO);	
#endif

	ft_putendl_fd("--------------------- END ---------------------", STDOUT_FILENO);
	show_alloc_mem();
	// show_alloc_mem_ex();

	return (0);
}