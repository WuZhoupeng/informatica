#include "adt.h"

/* QUEUE (FIFO: First In First Out)
 * Add to the tail and remove from the head */

void enqueue(queue *p_queue, const data_type d) {
  if (p_queue == NULL) {
    errx(EXIT_FAILURE, "queue has not been initialized");
  }

  node *new_node;

  if ((new_node = malloc(node_size)) == NULL) {
    errx(EXIT_FAILURE, "cannot allocate memory for a new node");
  }
  new_node->data = d;
  new_node->next = NULL;

  /* If the queue is empty, the new node is the queue itself */
  if (*p_queue == NULL) {
    *p_queue = new_node;
  } else {
    /* Find the last node */
    node *curr = *p_queue;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    /* Append the new node */
    curr->next = new_node;
  }
}

data_type dequeue(queue *p_queue) {
  if (p_queue == NULL) {
    errx(EXIT_FAILURE, "queue has not been initialized");
  }

  if (queue_is_empty(*p_queue)) {
    errx(EXIT_FAILURE, "cannot dequeue from an empty queue");
  }

  data_type val = (*p_queue)->data;

  /* Remove the head */
  node *temp = *p_queue;
  *p_queue = (*p_queue)->next;
  free(temp);

  return val;
}

bool queue_is_empty(const queue q) { return q == NULL; }

void print_queue(const queue qu) {
  queue q = qu;

  printf("Queue: ");
  for (; q != NULL; q = q->next) {
    printf("%d ", q->data);
  }
  printf("\n");
}

/* STACK (LIFO: Last In First Out)
 * Add to the head and remove from the head */

void push(stack *p_stack, const data_type d) {
  if (p_stack == NULL) {
    errx(EXIT_FAILURE, "stack has not been initialized");
  }
  node *new_node;

  if ((new_node = malloc(node_size)) == NULL) {
    errx(EXIT_FAILURE, "cannot allocate memory to push data");
  }

  new_node->data = d;
  new_node->next = *p_stack;

  *p_stack = new_node;
}

data_type pop(stack *p_stack) {
  if (p_stack == NULL) {
    errx(EXIT_FAILURE, "stack has not been initialized");
  }

  if (*p_stack == NULL) {
    errx(EXIT_FAILURE, "cannot pop due empty stack");
  }

  data_type d = (*p_stack)->data;

  node *temp = *p_stack;
  *p_stack = (*p_stack)->next;
  free(temp);

  return d;
}

bool stack_is_empty(const stack s) { return s == NULL; }

void print_stack(const stack s) {
  printf("Stack: ");
  for (node *p = s; p != NULL; p = p->next) {
    printf("%d ", p->data);
  }
  printf("\n\n");
}