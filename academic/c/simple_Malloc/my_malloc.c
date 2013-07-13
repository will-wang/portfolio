#include "my_malloc.h"

/* You *MUST* use this macro when calling my_sbrk to allocate the 
 * appropriate size. Failure to do so may result in an incorrect
 * grading!
 */
#define SBRK_SIZE 2048

/* If you want to use debugging printouts, it is HIGHLY recommended
 * to use this macro or something similar. If you produce output from
 * your code then you will receive a 20 point deduction. You have been
 * warned.
 */
#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x)
#endif


/* make sure this always points to the beginning of your current
 * heap space! if it does not, then the grader will not be able
 * to run correctly and you will receive 0 credit. remember that
 * only the _first_ call to my_malloc() returns the beginning of
 * the heap. sequential calls will return a pointer to the newly
 * added space!
 * Technically this should be declared static because we do not
 * want any program outside of this file to be able to access it
 * however, DO NOT CHANGE the way this variable is declared or
 * it will break the autograder.
 */
void* heap;

/* our freelist structure - this is where the current freelist of
 * blocks will be maintained. failure to maintain the list inside
 * of this structure will result in no credit, as the grader will
 * expect it to be maintained here.
 * Technically this should be declared static for the same reasons
 * as above, but DO NOT CHANGE the way this structure is declared
 * or it will break the autograder.
 */
metadata_t* freelist[8];
/**** SIZES FOR THE FREE LIST ****
 * freelist[0] -> 16
 * freelist[1] -> 32
 * freelist[2] -> 64
 * freelist[3] -> 128
 * freelist[4] -> 256
 * freelist[5] -> 512
 * freelist[6] -> 1024
 * freelist[7] -> 2048
 */


void* my_malloc(size_t size)
{
  /* FIX ME */
	
	int block_Size = 0;
	int free_i = 0;
	int found = 0;
	int split_Size = 0;
	void* re_Heap = NULL;

 	metadata_t m_data = {0,2048,0,0};
	metadata_t* tmp = 0;

 	/* Initialize heap */
	if (heap == 0) {
        	heap = my_sbrk(SBRK_SIZE);
		*(metadata_t *) heap = m_data;
		freelist[7] = heap;
	}

 	/* Find what size of block we need */
	if ((size + sizeof(metadata_t)) <= 16) {
		block_Size = 16;
		free_i = 0;
	}

	else if ((size + sizeof(metadata_t)) <= 32) {
		block_Size = 32;
		free_i = 1;
	}

	else if ((size + sizeof(metadata_t)) <= 64) {
		block_Size = 64;
		free_i = 2;
	}

	else if ((size + sizeof(metadata_t)) <= 128) {
		block_Size = 128;
		free_i = 3;
	}

	else if ((size + sizeof(metadata_t)) <= 256) {
		block_Size = 256;
		free_i = 4;
	}

	else if ((size + sizeof(metadata_t)) <= 512) {
		block_Size = 512;
		free_i = 5;
	}

	else if ((size + sizeof(metadata_t)) <= 1024) {
		block_Size = 1024;
		free_i = 6;
	}

	else if ((size + sizeof(metadata_t)) <= 2048) {
		block_Size = 2048;
		free_i = 7;
	}

	else {
		return NULL; /* If request exceeds 2048 bytes */
	}

	/* If user request is available at free list */
	if (freelist[free_i] != 0) {
		char* returnAdr = (char*) freelist[free_i];
		freelist[free_i] -> in_use = 1;
		freelist[free_i] = 0;
		return returnAdr + sizeof(metadata_t);     
	}

	else {
		split_Size = block_Size;

 		/* Find smallest block to split */
		while (found == 0) {
			free_i++;
			split_Size = split_Size * 2;

 			/* No blocks available in freelist (need to expand heap) */
			if (free_i > 7) {
				re_Heap = my_sbrk(SBRK_SIZE);
				*(metadata_t *) re_Heap = m_data;
				tmp = freelist[7];                   

                       		/* Add expanded memory to free list */
				if (tmp == 0) {
					freelist[7] = re_Heap;
				}

                        	else {
					while (tmp -> next != 0) {
						tmp = tmp -> next;
					}
					tmp -> next = re_Heap;
				}
				return my_malloc(size);
			}

 			if (freelist[free_i] != 0) {
				found = 1;
			}
		}

 		/* Split until the right size */
		while((split_Size >= block_Size) && ((split_Size / 2) >= block_Size)) {
			freelist[free_i] = freelist[free_i] -> next;
			if (freelist[free_i] != 0) {
				freelist[free_i] -> prev = 0;
			}
			split_Size = split_Size / 2;     
			free_i--;

			/* Organize freelist */
			m_data.size = split_Size;     
			*(metadata_t *) heap = m_data;
			*(metadata_t *) (((char*) heap) + split_Size) = m_data;
			((metadata_t *) heap) -> next = (metadata_t*) (((char *) heap) + split_Size);
			(((metadata_t *)heap) + split_Size) -> prev = heap;
			freelist[free_i] = heap;
		}

 		freelist[free_i] = freelist[free_i] -> next;
		if (freelist[free_i] != 0) {
			freelist[free_i] -> prev = 0;
		}
		(((metadata_t *) (((char*) heap) + split_Size)) -> in_use) = 1;
		return ((char *) heap + split_Size + sizeof(metadata_t));
	}
	return NULL;
}

void* my_realloc(void* ptr, size_t new_size)
{
  /* FIX ME */
	
	size_t tmp_size;
	void* dest;

 	/* If ptr==null; just malloc */
	if (ptr == NULL) {
		return my_malloc(new_size);
	} 

	/* If new_size==0; just free */
	if (new_size == 0) {
		my_free(ptr);
		return NULL;
	}

	tmp_size = ((metadata_t*) (((char*) ptr) - sizeof(metadata_t))) -> size;

	/* If new_size <= tmp_size; cannot realloc */
	if (new_size <= tmp_size) {
		return ptr;
	}

	/* Malloc */
	dest = my_malloc(new_size);
	if (dest == NULL) {
		return NULL;
	}
 
	/* Copy */
	my_memcpy(dest, ptr, tmp_size);
	/* Free */
	my_free(ptr);
	return dest;
}

void my_free(void* ptr)
{
  /* FIX ME */
	
	int x;
	int position;
	char* addr;
	short tmpAddr1;
	short tmpAddr2;
	short blk_Size;
	char* bddy_Addr;
	int match1;
	int match2;

	addr = (char*) (((char*) ptr) - sizeof(metadata_t));
	tmpAddr1 = addr - (char*) heap;
	blk_Size = ((metadata_t *) addr) -> size;

	/* Brute force find of block size */
	if (blk_Size == 16) {
		x = 4;
	}

	else if (blk_Size == 32) {
		x = 5;
	}

	else if (blk_Size == 64) {
		x = 6;
	}

	else if (blk_Size == 128) {
		x = 7;
	}

	else if (blk_Size == 256) {
		x = 8;
	}

	else if (blk_Size == 512) {
		x = 9;
	}

	else if (blk_Size == 1024) {
		x = 10;
	}

	else {
		x = 11;
	}

	/* If block size is 2048; just free */
	if (x == 11) {
		((metadata_t *) addr) -> in_use = 0;
		freelist[x - 4] = (metadata_t *) addr;
		return;
	}    

	/* Find which position this block is */
	if ((tmpAddr1 & (1 << (x))) >> (x) == 0) {
		position = 0;
		bddy_Addr = addr + blk_Size;
		tmpAddr2 = bddy_Addr - (char*) heap;
	}

	else {
		position = 1;
		bddy_Addr = addr - blk_Size;
		tmpAddr2 = bddy_Addr - (char*) heap;
	}

	match1 = (tmpAddr1 & (1 << (x + 1))) >> (x + 1);
	match2 = (tmpAddr2 & (1 << (x + 1))) >> (x + 1);

	/* Merge only if matcing pair bits, same block size, and buddy is empty */
	if ((((metadata_t *) bddy_Addr) -> in_use) == 0 && (((metadata_t *) bddy_Addr) -> size) == blk_Size && (match1 == match2) ) {
		if (position == 0) {
			((metadata_t *) addr) -> in_use = 0;
			((metadata_t *) addr) -> size = (((metadata_t *) addr) -> size) * 2;
			if (freelist[x - 3] == 0) {
				freelist[x - 4] = 0;
				freelist[x - 3] = (metadata_t *) addr;
			}
			else {
				freelist[x - 4] = 0;
				freelist[x - 3] -> next = (metadata_t *) addr;
				((metadata_t *) addr) -> prev = freelist[x-3];
			}

			my_free((void*)(addr + sizeof(metadata_t)));
		}
		else {
			((metadata_t *) bddy_Addr) -> in_use = 0;
			((metadata_t *) bddy_Addr) -> size = (((metadata_t *) bddy_Addr) -> size) * 2;
			if (freelist[x - 3] == 0) {
				freelist[x - 4] = 0;
				freelist[x - 3] = (metadata_t *) bddy_Addr;
			}
			else {
				freelist[x - 4] = 0;
				freelist[x-3] -> next = (metadata_t *) bddy_Addr;
				((metadata_t *) bddy_Addr) -> prev = freelist[x-3];
			}

			my_free((void*)(bddy_Addr + sizeof(metadata_t)));
		}
	}

	/* If no match; just free */
	else {
		((metadata_t *) addr) -> in_use = 0;
		freelist[x-4] = (metadata_t *) addr;
	}
}

void* my_memcpy(void* dest, const void* src, size_t num_bytes)
{
  /* FIX ME */
	
	char *new_dest = (char*) dest;
	char *new_src  = (char*) src;
	int i;

	for (i = 0; i < num_bytes; i++) {
		new_dest[i] = new_src[i]; /* Copy data */
	}
	return dest;
}
