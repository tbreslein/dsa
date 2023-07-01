#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once

typedef struct DoubleLinkedListIntNode {
    int data;
    struct DoubleLinkedListIntNode *prev;
    struct DoubleLinkedListIntNode *next;
} double_linked_list_int_node;

typedef struct DoubleLinkedListInt {
    int len;
    struct DoubleLinkedListIntNode *head;
    struct DoubleLinkedListIntNode *tail;
} double_linked_list_int;

double_linked_list_int *dlli_new() {
    struct DoubleLinkedListInt *l = (struct DoubleLinkedListInt *)malloc(sizeof(struct DoubleLinkedListInt));
    assert(l != NULL);
    l->len = 0;
    l->head = NULL;
    l->tail = NULL;
    return l;
}

double_linked_list_int_node *dlli_new_node(int data) {
    struct DoubleLinkedListIntNode *n =
        (struct DoubleLinkedListIntNode *)malloc(sizeof(struct DoubleLinkedListIntNode));
    assert(n != NULL);
    n->data = data;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

void dlli_free_node(double_linked_list_int_node *n) {
    if (n == NULL) {
        return;
    }
    if (n->next != NULL) {
        dlli_free_node(n->next);
    }
    free(n);
    return;
}

void dlli_free(double_linked_list_int *l) {
    assert(l != NULL);
    dlli_free_node(l->head);
    l->tail = NULL;
    free(l);
    return;
}

double_linked_list_int_node *dlli_seek(double_linked_list_int **l, size_t idx) {
    assert(l != NULL);
    assert((*l)->head != NULL);
    double_linked_list_int_node *curr = (*l)->head;
    for (size_t j = 0; j < idx && curr != NULL; j++, curr = curr->next)
        ;
    return curr;
}

void dlli_push_front(double_linked_list_int **l, int data) {
    assert(l != NULL);
    double_linked_list_int_node *new_node = dlli_new_node(data);
    (*l)->len++;
    if ((*l)->head == NULL) {
        (*l)->head = new_node;
        (*l)->tail = new_node;
        return;
    }
    new_node->next = (*l)->head;
    (*l)->head->prev = new_node;
    (*l)->head = new_node;
}

void dlli_push_back(double_linked_list_int **l, int data) {
    assert(l != NULL);
    double_linked_list_int_node *new_node = dlli_new_node(data);
    if ((*l)->len == 0) {
        (*l)->head = new_node;
    } else {
        new_node->prev = (*l)->tail;
        (*l)->tail->next = new_node;
    }
    (*l)->tail = new_node;
    (*l)->len++;
    return;
}

void dlli_insert_at(double_linked_list_int **l, int data, size_t idx) {
    if (idx == 0) {
        dlli_push_front(l, data);
        return;
    }
    if (idx == (*l)->len) {
        dlli_push_back(l, data);
        return;
    }
    double_linked_list_int_node *prev = dlli_seek(l, idx - 1);
    double_linked_list_int_node *next = prev->next;
    double_linked_list_int_node *new_node = dlli_new_node(data);
    new_node->next = next;
    new_node->prev = prev;
    prev->next = new_node;
    next->prev = new_node;
    (*l)->len++;
}

int dlli_pop_front(double_linked_list_int **l) {
    assert(*l != NULL);
    assert((*l)->head != NULL);
    int out = (*l)->head->data;
    if ((*l)->len == 1) {
        (*l)->head = NULL;
        (*l)->tail = NULL;
        free((*l)->head);
        return out;
    }
    double_linked_list_int_node *next = (*l)->head->next;
    next->prev = NULL;
    free((*l)->head);
    (*l)->head = next;
    (*l)->len--;
    return out;
}

int dlli_pop_back(double_linked_list_int **l) {
    assert(*l != NULL);
    assert((*l)->tail != NULL);
    int out = (*l)->tail->data;
    if ((*l)->len == 1) {
        (*l)->head = NULL;
        (*l)->tail = NULL;
        free((*l)->tail);
        return out;
    }
    double_linked_list_int_node *prev = (*l)->tail->prev;
    prev->next = NULL;
    free((*l)->tail);
    (*l)->tail = prev;
    (*l)->len--;
    return out;
}

int dlli_remove_at(double_linked_list_int **l, size_t idx) {
    if (idx == 0) {
        return dlli_pop_front(l);
    }
    if (idx == (*l)->len - 1) {
        return dlli_pop_back(l);
    }
    double_linked_list_int_node *curr = dlli_seek(l, idx);
    double_linked_list_int_node *next = curr->next;
    double_linked_list_int_node *prev = curr->prev;
    int out = curr->data;
    prev->next = next;
    curr->prev = prev;
    free(curr);
    (*l)->len--;
    return out;
}

void dlli_print(double_linked_list_int **l) {
    printf("[ ");
    if ((*l)->head != NULL) {
        double_linked_list_int_node *curr;
        for (curr = (*l)->head; curr != NULL; curr = curr->next) {
            printf("%d ", curr->data);
        }
    }
    printf("]; len = %d\n", (*l)->len);
}

int dlli_peek_front(const double_linked_list_int *l) {
    assert(l != NULL);
    assert(l->head != NULL);
    return l->head->data;
}

int dlli_peek_back(const double_linked_list_int *l) {
    assert(l != NULL);
    assert(l->tail != NULL);
    return l->tail->data;
}

int dlli_peek_at(double_linked_list_int **l, size_t idx) {
    const double_linked_list_int_node *curr = dlli_seek(l, idx);
    return curr->data;
}

void dlli_test() {
    printf("Running DoubleLinkedList tests!\n");
    // creation
    double_linked_list_int *l = dlli_new();
    assert(l != NULL);
    assert(l->len == 0);
    assert(l->head == NULL);
    assert(l->tail == NULL);
    printf("\nafter creating:\n  l should be [ ]\n  lli_print = ");
    dlli_print(&l);

    // push
    dlli_push_front(&l, 2);
    assert(l->len == 1);
    assert(l->head != NULL);
    assert(l->tail != NULL);
    assert(l->head->next == NULL);
    assert(l->head->prev == NULL);
    assert(l->tail->next == NULL);
    assert(l->tail->prev == NULL);
    assert(l->head->data == 2);
    assert(l->tail->data == 2);
    assert(dlli_peek_front(l) == 2);
    assert(dlli_peek_back(l) == 2);
    printf("\nafter pushing 2 to the front:\n  l should be [ 2 ]\n  lli_print = ");
    dlli_print(&l);

    dlli_push_back(&l, 1);
    assert(l->len == 2);
    assert(l->head != NULL);
    assert(l->tail != NULL);
    assert(l->head->data == 2);
    assert(l->tail->data == 1);
    assert(dlli_peek_front(l) == 2);
    assert(dlli_peek_back(l) == 1);
    printf("\nafter pushing 1 to the back:\n  l should be [ 2 1 ]\n  lli_print = ");
    dlli_print(&l);

    dlli_push_back(&l, 3);
    assert(l->len == 3);
    assert(l->head != NULL);
    assert(l->tail != NULL);
    assert(l->head->data == 2);
    assert(l->tail->data == 3);
    assert(dlli_peek_front(l) == 2);
    assert(dlli_peek_back(l) == 3);
    printf("\nafter pushing 3 to the back:\n  l should be [ 2 1 3 ]\n  lli_print = ");
    dlli_print(&l);

    // peek_at
    assert(dlli_peek_at(&l, 0) == 2);
    printf("\npeeking at 0: %d\n", dlli_peek_at(&l, 0));

    assert(dlli_peek_at(&l, 1) == 1);
    printf("\npeeking at 1: %d\n", dlli_peek_at(&l, 1));

    assert(dlli_peek_at(&l, 2) == 3);
    printf("\npeeking at 1: %d\n", dlli_peek_at(&l, 2));

    // pop
    int foo = dlli_pop_front(&l);
    printf("\npop_front: %d\n", foo);
    assert(l->len == 2);
    assert(foo == 2);
    assert(dlli_peek_front(l) == 1);
    assert(dlli_peek_back(l) == 3);
    printf("\nafter popping front\n  l should be [ 1 3 ]\n  lli_print = ");
    dlli_print(&l);

    foo = dlli_pop_back(&l);
    printf("\npop_back: %d\n", foo);
    assert(l->len == 1);
    assert(foo == 3);
    dlli_print(&l);
    assert(dlli_peek_front(l) == 1);
    assert(dlli_peek_back(l) == 1);
    printf("\nafter popping back\n  l should be [ 1 ]\n  lli_print = ");
    dlli_print(&l);

    // insert_at
    dlli_insert_at(&l, 2, 0);
    assert(dlli_peek_at(&l, 0) == 2);
    printf("\nafter insert 2 at idx 0\n  l should be [ 2 1 ]\n  lli_print = ");
    dlli_print(&l);

    dlli_insert_at(&l, 3, 1);
    dlli_print(&l);
    assert(dlli_peek_at(&l, 1) == 3);
    printf("\nafter insert 3 at idx 1\n  l should be [ 2 3 1 ]\n  lli_print = ");
    dlli_print(&l);

    dlli_insert_at(&l, 4, 2);
    dlli_print(&l);
    assert(dlli_peek_at(&l, 2) == 4);
    printf("\nafter insert 4 at idx 2\n  l should be [ 2 3 4 1 ]\n  lli_print = ");
    dlli_print(&l);

    // // remove_at
    assert(dlli_remove_at(&l, 1) == 3);
    printf("\nafter removing 3 at idx 1\n  l should be [ 2 4 1 ]\n  lli_print = ");
    dlli_print(&l);

    assert(dlli_remove_at(&l, 2) == 1);
    printf("\nafter removing 1 at idx 2\n  l should be [ 2 4 ]\n  lli_print = ");
    dlli_print(&l);

    assert(dlli_remove_at(&l, 0) == 2);
    printf("\nafter removing 2 at idx 0\n  l should be [ 4 ]\n  lli_print = ");
    dlli_print(&l);

    dlli_free(l);
    printf("Finished DoubleLinkedList tests!\n\n");
}
