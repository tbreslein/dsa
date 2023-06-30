#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once

typedef struct DoubleLinkedListInt {
    int data;
    struct DoubleLinkedListInt *next;
    struct DoubleLinkedListInt *prev;
} double_linked_list_int;

double_linked_list_int *dlli_new(int data) {
    struct DoubleLinkedListInt *new_node = (struct DoubleLinkedListInt *)malloc(sizeof(struct DoubleLinkedListInt));
    assert(new_node != NULL);
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void dlli_free(double_linked_list_int *l) {
    assert(l != NULL);
    if (l->next != NULL) {
        dlli_free(l->next);
    }
    free(l);
    return;
}

size_t dlli_len(double_linked_list_int *l) {
    size_t len = 0;
    double_linked_list_int *curr = l;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }
    return len;
}

double_linked_list_int *dlli_seek(double_linked_list_int **l, size_t idx) {
    assert(l != NULL);
    double_linked_list_int *curr = *l;
    for (size_t j = 0; j < idx && curr != NULL; j++, curr = curr->next)
        ;
    assert(curr != NULL);
    return curr;
}

void dlli_push(double_linked_list_int **l, int data) {
    double_linked_list_int *new_node = dlli_new(data);
    if (*l != NULL) {
        new_node->next = *l;
    }
    *l = new_node;
}

void dlli_insert_at(double_linked_list_int **l, int data, size_t idx) {
    if (idx == 0) {
        dlli_push(l, data);
        return;
    }
    double_linked_list_int *curr = dlli_seek(l, idx - 1);
    double_linked_list_int *new_node = dlli_new(data);
    new_node->next = curr->next;
    new_node->prev = curr;
    if (curr->next != NULL) {
        curr->next->prev = new_node;
    }
    curr->next = new_node;
}

int dlli_pop(double_linked_list_int **l) {
    assert(*l != NULL);
    int out = (*l)->data;
    double_linked_list_int *next_node = (*l)->next;
    free(*l);
    *l = next_node;
    (*l)->prev = NULL;
    return out;
}

int dlli_remove_at(double_linked_list_int **l, size_t idx) {
    if (idx == 0) {
        return dlli_pop(l);
    }
    double_linked_list_int *prev = dlli_seek(l, idx - 1);
    assert(prev->next != NULL);
    double_linked_list_int *curr = prev->next;
    double_linked_list_int *next = curr->next;
    int out = curr->data;
    prev->next = next;
    if (next != NULL) {
        next->prev = prev;
    }
    free(curr);
    return out;
}

void dlli_print(double_linked_list_int **l) {
    printf("[ ");
    double_linked_list_int *curr = *l;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]\n");
}

int dlli_peek(const double_linked_list_int *l) {
    assert(l != NULL);
    return l->data;
}

int dlli_peek_at(double_linked_list_int **l, size_t idx) {
    const double_linked_list_int *curr = dlli_seek(l, idx);
    return curr->data;
}

void dlli_test() {
    printf("Running DoubleLinkedList tests!\n");
    int foo;
    // creation
    double_linked_list_int *l = dlli_new(1);
    assert(dlli_len(l) == 1);
    assert(l != NULL);
    assert(l->next == NULL);
    assert(l->data == 1);
    assert(dlli_peek(l) == 1);
    printf("\nafter creating with 1:\n  l should be [ 1 ]\n  lli_print = ");
    dlli_print(&l);

    // push
    dlli_push(&l, 2);
    assert(dlli_len(l) == 2);
    assert(l->next != NULL);
    assert(l->data == 2);
    assert(dlli_peek(l) == 2);
    assert(l->next->data == 1);
    printf("\nafter pushing 2:\n  l should be [ 2 1 ]\n  lli_print = ");
    dlli_print(&l);

    // peek_at
    foo = dlli_peek_at(&l, 0);
    assert(foo == 2);
    printf("\npeeking at 0: %d\n", foo);

    foo = dlli_peek_at(&l, 1);
    assert(foo == 1);
    printf("\npeeking at 1: %d\n", foo);

    // pop
    foo = dlli_pop(&l);
    printf("\npop: %d\n", foo);
    assert(dlli_len(l) == 1);
    assert(foo == 2);
    assert(l != NULL);
    assert(l->next == NULL);
    assert(l->data == 1);
    assert(dlli_peek(l) == 1);
    printf("\nafter popping\n  l should be [ 1 ]\n  lli_print = ");
    dlli_print(&l);

    // insert_at
    dlli_insert_at(&l, 2, 0);
    foo = dlli_peek_at(&l, 1);
    assert(foo == 1);
    printf("\nafter insert 2 at idx 0\n  l should be [ 2 1 ]\n  lli_print = ");
    dlli_print(&l);

    dlli_insert_at(&l, 3, 1);
    foo = dlli_peek_at(&l, 1);
    assert(foo == 3);
    printf("\nafter insert 3 at idx 1\n  l should be [ 2 3 1 ]\n  lli_print = ");
    dlli_print(&l);

    dlli_insert_at(&l, 4, 2);
    foo = dlli_peek_at(&l, 2);
    assert(foo == 4);
    printf("\nafter insert 4 at idx 2\n  l should be [ 2 3 4 1 ]\n  lli_print = ");
    dlli_print(&l);

    // remove_at
    foo = dlli_remove_at(&l, 1);
    assert(foo == 3);
    printf("\nafter removing 3 at idx 1\n  l should be [ 2 4 1 ]\n  lli_print = ");
    dlli_print(&l);

    foo = dlli_remove_at(&l, 2);
    assert(foo == 1);
    printf("\nafter removing 1 at idx 2\n  l should be [ 2 4 ]\n  lli_print = ");
    dlli_print(&l);

    foo = dlli_remove_at(&l, 0);
    assert(foo == 2);
    printf("\nafter removing 2 at idx 0\n  l should be [ 4 ]\n  lli_print = ");
    dlli_print(&l);

    dlli_free(l);
    printf("Finished DoubleLinkedList tests!\n\n");
}
