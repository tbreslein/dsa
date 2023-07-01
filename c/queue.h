#include "linkedlist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once

typedef struct QueueInt {
    int len;
    linked_list_int *list;
} queue_int;

queue_int *qi_new() {
    struct QueueInt *q = (struct QueueInt *)malloc(sizeof(struct QueueInt));
    assert(q != NULL);
    linked_list_int *l = lli_new();
    q->len = 0;
    q->list = l;
    return q;
}

void qi_free(queue_int *q) {
    if (q == NULL) {
        return;
    }
    lli_free(q->list);
    free(q);
    return;
}

void qi_push(queue_int **q, int data) {
    (*q)->len++;
    lli_push_front(&(*q)->list, data);
}
int qi_pop(queue_int **q) {
    (*q)->len--;
    return lli_pop_back(&(*q)->list);
}

void qi_print(queue_int **q) { lli_print(&(*q)->list); }

int qi_peek(const queue_int *q) {
    assert(q != NULL);
    return lli_peek_back(q->list);
}

void qi_test() {
    // creation
    queue_int *q = qi_new();
    assert(q != NULL);
    assert(q->len == 0);
    assert(q->list != NULL);
    assert(q->list->len == 0);
    assert(q->list->head == NULL);
    assert(q->list->tail == NULL);

    // push
    qi_push(&q, 2);
    assert(q->len == 1);
    assert(qi_peek(q) == 2);

    qi_push(&q, 1);
    assert(q->len == 2);
    assert(qi_peek(q) == 2);

    qi_push(&q, 3);
    assert(q->len == 3);
    assert(qi_peek(q) == 2);

    // pop
    int foo;
    foo = qi_pop(&q);
    assert(foo == 2);
    foo = qi_pop(&q);
    assert(foo == 1);
    foo = qi_pop(&q);
    assert(foo == 3);

    qi_free(q);
    printf("Finished Queue tests!\n");
}
