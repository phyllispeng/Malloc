

#ifndef __SFMM_H
#define __SFMM_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>
#include <errno.h>
#include <time.h>



/* Add Includes, prototypes, and preprocessor macros here */
#define FOUR_GB  4294967296




/*
* initialize your memory allocator
*/

void sf_mem_init(void);


/*
* implementation of malloc 
*/
void *sf_malloc(size_t size);


/*
* marks a dynamically allocated region as no longer in use
*/
void sf_free(void *ptr);


/*
* resizeds the memory pointed to by ptr to be size bytes
*/
void* sf_realloc(void* ptr, size_t size);


/*
* Allocate an array of nmem elements each of size bytes
*/
void* sf_calloc(size_t nmemb, size_t size);

/*
* funciton which outputs the state of the free-list to stdout
*/
void sf_snapshot(void);

#endif


