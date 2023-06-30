#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once

typedef struct LinkedListInt {
    int data;
    struct LinkedListInt *next;
} linked_list_int;

linked_list_int *lli_new(int data) {
    struct LinkedListInt *new_node = (struct LinkedListInt *)malloc(sizeof(struct LinkedListInt));
    assert(new_node != NULL);
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void lli_free(linked_list_int *l) {
    assert(l != NULL);
    if (l->next != NULL) {
        lli_free(l->next);
    }
    free(l);
    return;
}

size_t lli_len(linked_list_int *l) {
    size_t len = 0;
    linked_list_int *curr = l;
    while (curr != NULL) {
        len++;
        curr = curr->next;
    }
    return len;
}

linked_list_int *lli_seek(linked_list_int **l, size_t idx) {
    assert(l != NULL);
    linked_list_int *curr = *l;
    for (size_t j = 0; j < idx && curr != NULL; j++, curr = curr->next)
        ;
    assert(curr != NULL);
    return curr;
}

void lli_push(linked_list_int **l, int data) {
    linked_list_int *new_node = lli_new(data);
    if (*l != NULL) {
        new_node->next = *l;
    }
    *l = new_node;
}

void lli_insert_at(linked_list_int **l, int data, size_t idx) {
    if (idx == 0) {
        lli_push(l, data);
        return;
    }
    linked_list_int *curr = lli_seek(l, idx - 1);
    linked_list_int *new_node = lli_new(data);
    new_node->next = curr->next;
    curr->next = new_node;
}

int lli_pop(linked_list_int **l) {
    assert(*l != NULL);
    int out = (*l)->data;
    linked_list_int *next_node = (*l)->next;
    free(*l);
    *l = next_node;
    return out;
}

int lli_remove_at(linked_list_int **l, size_t idx) {
    if (idx == 0) {
        return lli_pop(l);
    }
    linked_list_int *prev = lli_seek(l, idx - 1);
    assert(prev->next != NULL);
    linked_list_int *curr = prev->next;
    int out = curr->data;
    prev->next = curr->next;
    free(curr);
    return out;
}

void lli_print(linked_list_int **l) {
    printf("[ ");
    linked_list_int *curr = *l;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]\n");
}

int lli_peek(const linked_list_int *l) {
    assert(l != NULL);
    return l->data;
}

int lli_peek_at(linked_list_int **l, size_t idx) {
    const linked_list_int *curr = lli_seek(l, idx);
    return curr->data;
}

void lli_test() {
    printf("Running LinkedList tests!\n");
    int foo;
    // creation
    linked_list_int *l = lli_new(1);
    assert(lli_len(l) == 1);
    assert(l != NULL);
    assert(l->next == NULL);
    assert(l->data == 1);
    assert(lli_peek(l) == 1);
    printf("\nafter creating with 1:\n  l should be [ 1 ]\n  lli_print = ");
    lli_print(&l);

    // push
    lli_push(&l, 2);
    assert(lli_len(l) == 2);
    assert(l->next != NULL);
    assert(l->data == 2);
    assert(lli_peek(l) == 2);
    assert(l->next->data == 1);
    printf("\nafter pushing 2:\n  l should be [ 2 1 ]\n  lli_print = ");
    lli_print(&l);

    // peek_at
    foo = lli_peek_at(&l, 0);
    assert(foo == 2);
    printf("\npeeking at 0: %d\n", foo);

    foo = lli_peek_at(&l, 1);
    assert(foo == 1);
    printf("\npeeking at 1: %d\n", foo);

    // pop
    foo = lli_pop(&l);
    printf("\npop: %d\n", foo);
    assert(lli_len(l) == 1);
    assert(foo == 2);
    assert(l != NULL);
    assert(l->next == NULL);
    assert(l->data == 1);
    assert(lli_peek(l) == 1);
    printf("\nafter popping\n  l should be [ 1 ]\n  lli_print = ");
    lli_print(&l);

    // insert_at
    lli_insert_at(&l, 2, 0);
    foo = lli_peek_at(&l, 1);
    assert(foo == 1);
    printf("\nafter insert 2 at idx 0\n  l should be [ 2 1 ]\n  lli_print = ");
    lli_print(&l);

    lli_insert_at(&l, 3, 1);
    foo = lli_peek_at(&l, 1);
    assert(foo == 3);
    printf("\nafter insert 3 at idx 1\n  l should be [ 2 3 1 ]\n  lli_print = ");
    lli_print(&l);

    lli_insert_at(&l, 4, 2);
    foo = lli_peek_at(&l, 2);
    assert(foo == 4);
    printf("\nafter insert 4 at idx 2\n  l should be [ 2 3 4 1 ]\n  lli_print = ");
    lli_print(&l);

    // remove_at
    foo = lli_remove_at(&l, 1);
    assert(foo == 3);
    printf("\nafter removing 3 at idx 1\n  l should be [ 2 4 1 ]\n  lli_print = ");
    lli_print(&l);

    foo = lli_remove_at(&l, 2);
    assert(foo == 1);
    printf("\nafter removing 1 at idx 2\n  l should be [ 2 4 ]\n  lli_print = ");
    lli_print(&l);

    foo = lli_remove_at(&l, 0);
    assert(foo == 2);
    printf("\nafter removing 2 at idx 0\n  l should be [ 4 ]\n  lli_print = ");
    lli_print(&l);

    lli_free(l);
    printf("Finished LinkedList tests!\n\n");
}
