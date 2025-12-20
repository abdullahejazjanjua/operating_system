#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/*
 * Queue
 *
 * In the similar vien as task 2, you are to write code
 * implementing a queue with the following operations:
 * enqueue():
 * inserts an element at the tail of a queue
 *
 * dequeue():
 * removes an element from the head of a queue
 *
 * search():
 * searches for an element in a queue. returns true if found
 *
 * print(): helper function prints the queue.
 *
 * The TASK:
 *
 * Your task is to make it work correctly even when multiple
 * threads manipulate the queue concurrently.
 *
 * Similar to the BST example, first create list of operations,
 * and then divide them among multiple threads to be performed
 * concurrently on a global queue.
 *
 * Try to go for maximum parallelism.
 * Remember in a queue it is possible for two threads to
 * enqueue() and dequeue() in parallel if the queue contains
 * more than 2 elements.

*/

typedef struct node_t
{
    int val;
    struct node_t *next;
} node_t;

node_t *head, *tail;

pthread_mutex_t hlock, tlock;

#define NUMOPS 800000
#define NUMTHREADS 8
#define MODULAND 10
#define ENQUEUE_LIMIT 5

typedef enum { ENQUEUE, DEQUEUE } OPTYPE;

typedef struct op {
    OPTYPE type;
    int val;
} op;

typedef struct thread_arg {
    op *op_start;
    int count;
} thread_arg;

void enqueue(int val)
{
    node_t *node = (node_t*) malloc(sizeof(node_t));
    node->val = val;
    node->next = NULL;
    
    pthread_mutex_lock(&tlock);
    tail->next = node;
    tail = node;
    pthread_mutex_unlock(&tlock);
    
    return;
}



void dequeue()
{
    pthread_mutex_lock(&hlock);
    node_t *tmp = head;
    node_t *node  = head->next;
    if (node == NULL) // if head is NULL, don't update to preserve the dummy node
    {
        pthread_mutex_unlock(&hlock);
        return; 
    }
    
    head = node; 
    free(tmp);
    pthread_mutex_unlock(&hlock);
}

void print()
{
    pthread_mutex_lock(&hlock);
    node_t *current = head->next; // skip dummy node
    while(current != NULL)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
    pthread_mutex_unlock(&hlock);
}

void *thread_func(void *arg)
{
    thread_arg *targ = (thread_arg *)arg;
    for (int i = 0; i < targ->count; i++)
    {
        if (targ->op_start[i].type == ENQUEUE)
        {
            enqueue(targ->op_start[i].val);
        }
        else if (targ->op_start[i].type == DEQUEUE)
        {
            dequeue();
        }
    }
    return NULL;
}

int main()
{
    srand(time(NULL));

    // Initialize locks
    pthread_mutex_init(&hlock, NULL);
    pthread_mutex_init(&tlock, NULL);

    // Initialize Dummy Node
    node_t *dummy = (node_t*) malloc(sizeof(node_t));
    dummy->val = -1; 
    dummy->next = NULL;
    
    head = dummy;
    tail = dummy;

    // Generate random operations array
    op *ops = malloc(sizeof(op) * NUMOPS);
    for (int i = 0; i < NUMOPS; i++)
    {
        ops[i].val = rand() % 100;
        if ((rand() % MODULAND) < ENQUEUE_LIMIT) 
            ops[i].type = ENQUEUE;
        else 
            ops[i].type = DEQUEUE;
    }

    pthread_t tids[NUMTHREADS];
    thread_arg targs[NUMTHREADS];

    printf("Starting %d operations using %d threads...\n", NUMOPS, NUMTHREADS);

    for (int i = 0; i < NUMTHREADS; i++) 
    {
        targs[i].count = NUMOPS / NUMTHREADS;
        targs[i].op_start = ops + (i * targs[i].count);
        pthread_create(&tids[i], NULL, thread_func, &targs[i]);
    }

    for (int i = 0; i < NUMTHREADS; i++) 
    {
        pthread_join(tids[i], NULL);
    }

    printf("Test complete. Final queue (first 20 elements): ");
    
    pthread_mutex_lock(&hlock);
    node_t *curr = head->next;
    for(int i = 0; i < 20 && curr != NULL; i++) 
    {
        printf("%d ", curr->val);
        curr = curr->next;
    }
    printf("...\n");
    pthread_mutex_unlock(&hlock);

    // Cleanup
    free(ops);
    pthread_mutex_destroy(&hlock);
    pthread_mutex_destroy(&tlock);

    return 0;
}