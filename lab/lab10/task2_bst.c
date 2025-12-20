#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/*
 * BST Related data structures and functions
 *
 * This implements a binary search tree with functions like
 * insert(), delete(), search(), and print_tree_inorder().
 *
 *
 * At the start of the program, by calling the function init_ops(),
 * a list of operations (search, insert, delete) is generated and
 * stored in the array "ops". Each element of the array ops is an
 * element of type "op" which is a structure containing the type
 * of the operation and the value. The type can be any of the
 * "search", "insert", "delete".
 *
 * The main program creates one or more threads and these threads
 * divide the array of operations "ops" among themselves and each
 * thread then tries to perform its set of operation on the global
 * tree represented by the global variable "groot".
 *
 *
 * Currently this works for a single thread but not when there
 * are multiple threads trying to update the global tree (groot).

 * The TASK:
 *
 * Your task is to make it work correctly even when multiple
 * threads update the tree concurrently.
 *
 * you can comment the below line to use the multiple threads
 * and a large number of operations.
 *     #define SMALLSIZE
 *
 * There are also other constants that are defined and you can change.

 */

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} node;

/*
 * Tree root - GLOBAL
 */

node* groot = NULL;



typedef enum {SEARCH, INSERT, DELETE} OPTYPE;

node* new_node() {
    node *n = malloc (sizeof(node));
    if (n==NULL){
        fprintf(stderr, "Error allocating memory\n");
        exit(-1);
    }

    n->val = -1;
    n->left = NULL;
    n->right = NULL;

    return n;
}


node* insert (node* root, int val) {
    if (root==NULL) {
        root = new_node();
        root->val = val;
    }
    else if (val < root->val) {
        root->left = insert (root->left, val);
    }
    else {
        root->right = insert (root->right, val);
    }

    return root;
}

node* delete (node* root, int val) {
    if (root==NULL) {
        return NULL;
    }
    else if (val < root->val) {
        root->left = delete (root->left, val);
    }
    else if (val > root->val) {
        root->right = delete (root->right, val);
    }
    else { // equal: found node to be deleted
           // three cases
           // case1: left child is NULL
           if (root->left==NULL) {
               node *tmp = root->right;
               free (root);
               return tmp;
           }
           if (root->right==NULL) {
               node *tmp = root->left;
               free (root);
               return tmp;
           }
           else { // both children exist

               // find successor
               // successor is either the left-most child of right subtree
               // or the right-most child of the left subtree
               node * parent= root;
               node * succ = root->right;  // we are taking 1st approach
               while (succ->left != NULL){
                   parent = succ;
                   succ = succ->left;
               }

               // foudn successor
               // adjsut tree
               if (parent == root) // immediately found
                    parent->right = succ->right;
               else // found somewhere down belwo
                    parent->left = succ->right;

               root->val = succ->val;
               free (succ);
               return root;
           }
    }

    return root;
}

node* search (node *root, int val){
    if (root==NULL)
        return NULL;
    else {
        if (root->val==val)
            return root;
        else if (val < root->val)
            return search (root->left, val);
        else
            return search (root->right, val);
    }
}

void print_tree_inorder (node* root) {
    if (root==NULL)
        return;
    // else
    print_tree_inorder (root->left);
    fprintf(stdout, "%d, ", root->val);
    print_tree_inorder (root->right);
}

/*
 * Threads related data structures and functions
 */

/*
 * The op structure specifies the operation to perform
 */

typedef struct op {
    OPTYPE type;
    int val;
} op;

typedef struct thread_arg {
    // node* root; // made global
    op *op_start;
    int count;
} thread_arg;

pthread_mutex_t mlock;

// comment line below to test large multithreadded
// #define SMALLSIZE

#ifdef SMALLSIZE
#define NUMOPS 10
#define NUMTHREADS 1
#define MODULAND 10
#define SEARCHBIN 4
#define INSERTBIN 7
#define DELETEBIN 10
#else  // LARGESIZE
#define NUMOPS 800000
#define NUMTHREADS 8
#define MODULAND 10000
#define SEARCHBIN 3333
#define INSERTBIN 6666
#define DELETEBIN 10000
#endif

void init_ops (op *ops){
    for (int i=0; i<NUMOPS; i++){

        int num = rand();
        ops[i].val = num%100;

        int op = num%MODULAND;
        if (op < SEARCHBIN){
            ops[i].type = SEARCH;
        }
        else if (op < INSERTBIN) {
            ops[i].type = INSERT;
        }
        else {  // DELETEBIN
            ops[i].type = DELETE;
        }
    }
}

// thread operations

node* test_tree () {

    groot = insert(groot, 7);
    groot = insert(groot, 5);
    groot = insert(groot, 3);
    groot = insert(groot, 4);
    groot = insert(groot, 9);
    groot = insert(groot, 8);
    groot = insert(groot, 10);

    fprintf(stdout, "tree: ");
    print_tree_inorder(groot);
    fprintf(stdout, "\n");

    groot = delete (groot, 3);
    fprintf(stdout, "tree after deleting 3: ");
    print_tree_inorder(groot);
    fprintf(stdout, "\n");

    groot = delete (groot, 8);
    fprintf(stdout, "tree after deleting 8: ");
    print_tree_inorder(groot);
    fprintf(stdout, "\n");

    groot = delete (groot, 55);
    fprintf(stdout, "tree after deleting 55: ");
    print_tree_inorder(groot);
    fprintf(stdout, "\n");

    return groot;
}

void * thread_func (void *arg) {
    thread_arg *targ = (thread_arg *) arg;

    fprintf(stdout, "Thread: count = %d\n", targ->count);

    for (int i=0; i<targ->count; i++) 
    {
    	pthread_mutex_lock(&mlock);
        fprintf(stdout, "Thread: Op[%d] = %d, val=%d\n",
                i, targ->op_start[i].type, targ->op_start[i].val);
        if (targ->op_start[i].type == SEARCH)
            search (groot, targ->op_start[i].val);
        else if (targ->op_start[i].type == INSERT)
            groot = insert (groot, targ->op_start[i].val);
        else if (targ->op_start[i].type == DELETE)
            groot = delete (groot, targ->op_start[i].val);
        pthread_mutex_unlock(&mlock);
    }

    return NULL;
}


int main (int argc, char* argv[]){

    // see RandGen
    srand(time(NULL));
    
    pthread_mutex_init(&mlock, NULL);
    // test_tree();
    // return 0;

    // initialize the thread structures
    op ops[NUMOPS];
    init_ops(ops);

    // just in case
    groot = NULL;

    pthread_t tids[NUMTHREADS];
    thread_arg targs[NUMTHREADS];
    // create therads
    for (int i=0; i<NUMTHREADS; i++) 
    {
        targs[i].count = NUMOPS/NUMTHREADS; // assume perfect division
        targs[i].op_start = ops + (i * targs[i].count);
        pthread_create( &tids[i], NULL, thread_func, &targs[i]);
    }

    for (int i=0; i<NUMTHREADS; i++)
        pthread_join( tids[i], NULL);

    print_tree_inorder(groot);
    pthread_mutex_destroy(&mlock);

    return 0;
}
