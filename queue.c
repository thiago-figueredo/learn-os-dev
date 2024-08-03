#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

int queue_size(queue_t *queue) {
  int size = 0;
  queue_t* head = queue;

  while (queue) {
    size++;

    if (queue->next == head) {
      break;
    }

    queue = queue->next;
  }

  return size;
}

void queue_print(char *name, queue_t *queue, void print_elem(void *)) {
  printf("%s", name);

  if (!queue) {
    printf("[]\n");
    return;
  }

  queue_t* head = queue;
  printf("[");

  do {
    print_elem(queue);

    if (queue->next != head) {
      printf(" ");
    }

    queue = queue->next;
  } while (queue != head);

  printf("]\n");
}

int queue_append(queue_t **queue, queue_t *elem) {
  if (!queue || !elem || elem->prev || elem->next) {
    return -1;
  }

  if (!*queue) {
    *queue = elem;
    elem->next = elem;
    elem->prev = elem;
    return 0;
  }

  queue_t *first_elem = *queue;
  queue_t *last_elem = first_elem->prev;

  first_elem->prev = elem;
  last_elem->next = elem;
  elem->prev = last_elem;
  elem->next = first_elem;
  
  return 0;
}

int queue_remove(queue_t **queue, queue_t *elem) {
  if (!queue || !*queue || !elem || !elem->prev || !elem->next) {
    return -1;
  }

  bool is_in_queue = false;
  queue_t* head = *queue;
  queue_t* aux = *queue;

  do {
    if (aux == elem) {
      is_in_queue = true;
      break;
    }

    aux = aux->next;
  } while (aux != head);

  if (!is_in_queue) {
    return -1;
  }

  if (*queue == elem && elem->next == elem) {
    *queue = NULL;
  } else if (*queue == elem) {
    queue_t* head = *queue;

    *queue = head->next;

    if (*queue) {
      (*queue)->prev = head->prev;
    }

    head->prev->next = *queue;
  } else {
    queue_t *aux = *queue;

    while (aux && aux->next != elem) {
      aux = aux->next;
    }

    queue_t* old_aux_next = aux->next;

    aux->next = old_aux_next->next;
    aux->next->prev = aux;
  }

  elem->prev = NULL;
  elem->next = NULL;

  return 0;
}

