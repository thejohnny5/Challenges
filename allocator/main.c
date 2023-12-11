#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "string.h"
pthread_mutex_t global_malloc_lock;

typedef char ALIGN[16];

union header {
	struct {
		size_t size;
		unsigned is_free;
		union header *next;
	} s;
	ALIGN stub;
};
typedef union header header_t;

// keep track of header_t
header_t *head, *tail;

header_t *get_free_block(size_t size)
{
    header_t *curr = head;
    while(curr){
        if (curr->s.is_free && curr->s.size >= size) return curr;
        curr = curr->s.next;
    }
    return NULL;
}
void *malloc(size_t size)
{
    size_t total_size;
    void *block;
    header_t *header;
    if (!size) return NULL; // No size provided

    // lock 
    pthread_mutex_lock(&global_malloc_lock);
    header = get_free_block(size);
    if (header){
        header->s.is_free = 0;
        pthread_mutex_unlock(&global_malloc_lock);
        return (void*)(header+1);
    }
    total_size = sizeof(header_t) + size;
    block = sbrk(total_size);
    if (block == (void*) -1) {
        // couldn't get memory on block
        pthread_mutex_unlock(&global_malloc_lock);
        return NULL;
    }
    header = block;
    header->s.size = size;
    header->s.is_free = 0;
    header->s.next = NULL;
    if (!head) head = header;
    if (tail) tail->s.next = header;
    tail = header;
    pthread_mutex_unlock(&global_malloc_lock);
    return (void *)(header + 1); // Returns the space to the block of memory adjacent to header
}


void free(void *block)
{
    header_t *header, *tmp;
    void *programbreak;
    if (!block) return;
    pthread_mutex_lock(&global_malloc_lock);
    header = (header_t*)block - 1;
    programbreak = sbrk(0);
    // then program break is the tail
    if ((char*)block + header->s.size == programbreak){
        if (head == tail){
            head = tail = NULL;
        } else {
            tmp = head;
            while (tmp){
                // remove last element from linked list
                if (tmp->s.next == tail) {
                    tmp->s.next = NULL;
                    tail = tmp;
                }
                tmp = tmp->s.next;
            }
        }
        sbrk(0 - sizeof(header_t) - header->s.size); // program break at last eleement
        pthread_mutex_unlock(&global_malloc_lock);
        return;
    }
    header->s.is_free = 1; // since not program break, set memory to free
    pthread_mutex_unlock(&global_malloc_lock);
}

// allocates memory for an array of num elements of nsize bytes 
void *calloc(size_t num, size_t nsize)
{
    size_t size;
    void *block;
    if (!num || !nsize) return NULL;
    size = num * nsize;
    if (nsize != size/num) return NULL; // mul overflow
    block = malloc(size);
    if (!block) return NULL;
    memset(block, 0, size);
    return block;
}

void *realloc(void *block, size_t size)
{
    header_t * header;
    void *ret;
    if (!block || !size) return malloc(size);
    header = (header_t*)block - 1;
    if (header->s.size >= size) return block; // block is smaller
    ret = malloc(size); // Malloc new block size
    if (ret) {
        memcpy(ret, block, header->s.size); // copy memory from block of s.size
        free(block);
    }
    return ret;
}

int main(int argc, char** argv){
   return EXIT_SUCCESS;
}
