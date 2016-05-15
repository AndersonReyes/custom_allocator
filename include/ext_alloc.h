#ifndef EXT_ALLOC_H
#define EXT_ALLOC_H

#include <stdlib.h>



void* ext_malloc(size_t sz, const char *file, int line);
void ext_free(void *ptr, const char *file, int line);
void* ext_realloc(void *ptr, size_t sz, const char *file, int line);
void* ext_calloc(size_t nmemb, size_t sz, const char *file, int line);

struct ext_stats
{
	unsigned long long active_allocs;
	unsigned long long active_size;
	unsigned long long total_allocs;
	unsigned long long total_size;
	unsigned long long fail_total;
	unsigned long long fail_size;
	void *heap_min;
	void *heap_max;
};

void ext_getstats(struct ext_stats *stats);
void ext_printstats(void);
void ext_printmem(void);


#if !EXT_DISABLE
#define malloc(sz)              ext_malloc((sz), __FILE__, __LINE__)
#define free(ptr)               ext_free((ptr), __FILE__, __LINE__)
#define realloc(ptr, sz)        ext_realloc((ptr), (sz), __FILE__, __LINE__)
#define calloc(nmemb, sz)       ext_calloc((nmemb), (sz), __FILE__, __LINE__)
#endif


#endif
