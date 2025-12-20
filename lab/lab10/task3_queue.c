#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Queue
 *
 * In the similar vien as task 2, you are to write code
 * implementing a queue with the following operations:
 * enqueue():
 *   inserts an element at the tail of a queue
 *
 * dequeue():
 *   removes an element from the head of a queue
 *
 * search():
 *   searches for an element in a queue. returns true if found
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
