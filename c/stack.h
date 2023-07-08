#include "linkedlist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once

typedef struct StackInt {
    int len;
    linked_list_int *list;
} stack_int;

stack_int *si_new() {
    struct StackInt *s = (struct StackInt *)malloc(sizeof(struct StackInt));
    assert(s != NULL);
    linked_list_int *l = lli_new();
    s->len = 0;
    s->list = l;
    return s;
}

void si_free(stack_int *s) {
    if (s == NULL) {
        return;
    }
    lli_free(s->list);
    free(s);
    return;
}

void si_push(stack_int *s, int data) {
    s->len++;
    lli_push_front(s->list, data);
}

int si_pop(stack_int *s) {
    s->len--;
    return lli_pop_front(s->list);
}

void si_print(const stack_int *s) { lli_print(s->list); }

int si_peek(const stack_int *s) {
    assert(s != NULL);
    return lli_peek_front(s->list);
}

void si_test(void) {
    // creation
    stack_int *s = si_new();
    assert(s != NULL);
    assert(s->len == 0);
    assert(s->list != NULL);
    assert(s->list->len == 0);
    assert(s->list->head == NULL);
    assert(s->list->tail == NULL);

    // push
    si_push(s, 2);
    assert(s->len == 1);
    assert(si_peek(s) == 2);

    si_push(s, 1);
    assert(s->len == 2);
    assert(si_peek(s) == 1);

    si_push(s, 3);
    assert(s->len == 3);
    assert(si_peek(s) == 3);

    // pop
    int foo;
    foo = si_pop(s);
    assert(foo == 3);
    foo = si_pop(s);
    assert(foo == 1);
    foo = si_pop(s);
    assert(foo == 2);

    si_free(s);
    printf("Finished Stack tests!\n");
}
