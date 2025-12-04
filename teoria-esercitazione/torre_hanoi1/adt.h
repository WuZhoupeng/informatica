#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <err.h>
#include <errno.h>

typedef int data_type;

struct node {
  data_type data;
  struct node *next;
};

typedef struct node node;

static size_t node_size = sizeof(node);

typedef node *stack;
typedef node *queue;

void push(stack *, const data_type);
data_type pop(stack *);
void print_stack(const stack);
bool stack_is_empty(const stack);

void enqueue(queue *, const data_type);
data_type dequeue(queue *);
void print_queue(const queue);
bool queue_is_empty(const queue);