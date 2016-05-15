#define EXT_DISABLE 1

#include "../include/ext_alloc.h"
#include "../include/mem_ds.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include <assert.h>


struct ext_stats debug_stats;

void* ext_malloc(size_t sz, const char *file, int line)
{
	(void)file, (void)line;

	void *ptr = malloc(sz);
	if (ptr == NULL)
	{
		fprintf(stderr, "Failed memory allocation in  in file %s at line %d, malloc() : memory is either unaccesible or null\n", file, line);

		debug_stats.fail_total++;
		debug_stats.fail_size += sz;
		return NULL;
	}

	debug_stats.active_allocs++;
	debug_stats.active_size += sz;
	debug_stats.total_allocs++;
	debug_stats.total_size += sz;

	list_insert(ptr, sz);

	return ptr;
}

void ext_free(void *ptr, const char *file, int line)
{
	(void)file, (void)line;

	unsigned long long remove_size = 0;
	list_find(ptr, &remove_size);
	if (ptr != NULL && remove_size != 0)
	{
		debug_stats.active_allocs--;
		debug_stats.active_size -= remove_size;
		list_remove(ptr);
		return free(ptr);
	}
	else
	{
		//printf("%p %10llu\n", ptr, remove_size);
		fprintf(stderr, "Invalid memory access in  in file %s at line %d, free() : memory is either unaccesible or null\n", file, line);
	}
}

void* ext_realloc(void *ptr, size_t sz, const char *file, int line)
{
	assert(ptr != NULL);

	void* new_mem = NULL;
	if (!sz)
	{
		fprintf(stderr, "Invalid size in %s at %d\n", file, line);
	}

	new_mem = ext_malloc(sz, file, line);

	if (new_mem == NULL)
	{
		fprintf(stderr, "Error allocating new memory of size (%lu) in %s at %d\n", sz, file, line);
	}

	unsigned long long memsize = 0;
	list_find(ptr, &memsize);
	memcpy(new_mem, ptr, memsize);

	ext_free(ptr, file, line);
	return new_mem;
}

void* ext_calloc(size_t nmemb, size_t sz, const char *file, int line)
{
	void *ptr = ext_malloc(nmemb * sz, file, line);
	if (ptr == NULL)
	{
		fprintf(stderr, "Segmentation Error  in file %s at line %d, calloc() : Null memory\n", file, line);
		return NULL;
	}

	memset(ptr, 0, nmemb * sz);

	return ptr;
}

void ext_getstats(struct ext_stats *getstats)
{
	memset(getstats, 255, sizeof(struct ext_stats));
	getstats->active_allocs = debug_stats.active_allocs;
	getstats->active_size = debug_stats.active_size;
	getstats->fail_size = debug_stats.fail_size;
	getstats->fail_total = debug_stats.fail_total;
	getstats->total_allocs = debug_stats.total_allocs;
	getstats->total_size = debug_stats.total_size;
	getstats->heap_min = list_gettop();
	getstats->heap_max = list_getend();
}

void ext_printstats(void)
{
	struct ext_stats pstats;
	ext_getstats(&pstats);

	printf("\nmalloc count: active %10llu total %10llu fail %10llu\n\n", pstats.active_allocs, pstats.total_allocs, pstats.fail_total);
	printf("malloc size:  active %10llu total %10llu fail %10llu\n\n", pstats.active_size, pstats.total_size, pstats.fail_size);
	printf("Heap min: %p  Heap max: %p\n\n", pstats.heap_min, pstats.heap_max);
}

void ext_printmem(void)
{
	list_show();
}
