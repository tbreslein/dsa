#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once

typedef struct LinkedListIntNode {
    int data;
    struct LinkedListIntNode *next;
} linked_list_int_node;

typedef struct LinkedListInt {
    int len;
    struct LinkedListIntNode *head;
    struct LinkedListIntNode *tail;
} linked_list_int;

linked_list_int *lli_new() {
    struct LinkedListInt *l = (struct LinkedListInt *)malloc(sizeof(struct LinkedListInt));
    assert(l != NULL);
    l->len = 0;
    l->head = NULL;
    l->tail = NULL;
    return l;
}

linked_list_int_node *lli_new_node(int data) {
    struct LinkedListIntNode *n = (struct LinkedListIntNode *)malloc(sizeof(struct LinkedListIntNode));
    assert(n != NULL);
    n->data = data;
    n->next = NULL;
    return n;
}

void lli_free_node(linked_list_int_node *n) {
    if (n == NULL) {
        return;
    }
    if (n->next != NULL) {
        lli_free_node(n->next);
    }
    free(n);
    return;
}

void lli_free(linked_list_int *l) {
    assert(l != NULL);
    lli_free_node(l->head);
    l->tail = NULL;
    free(l);
    return;
}

linked_list_int_node *lli_seek(const linked_list_int *l, size_t idx) {
    assert(l != NULL);
    assert(l->head != NULL);
    linked_list_int_node *curr = l->head;
    for (size_t j = 0; j < idx && curr != NULL; j++, curr = curr->next)
        ;
    return curr;
}

void lli_push_front(linked_list_int *l, int data) {
    assert(l != NULL);
    linked_list_int_node *new_node = lli_new_node(data);
    l->len++;
    if (l->head == NULL) {
        l->head = new_node;
        l->tail = new_node;
        return;
    }
    new_node->next = l->head;
    l->head = new_node;
}

void lli_push_back(linked_list_int *l, int data) {
    assert(l != NULL);
    linked_list_int_node *new_node = lli_new_node(data);
    if (l->len == 0) {
        l->head = new_node;
    } else {
        linked_list_int_node *prev = lli_seek(l, l->len - 1);
        prev->next = new_node;
    }
    l->tail = new_node;
    l->len++;
    return;
}

void lli_insert_at(linked_list_int *l, int data, size_t idx) {
    if (idx == 0) {
        lli_push_front(l, data);
        return;
    }
    if (idx == l->len) {
        lli_push_back(l, data);
        return;
    }
    linked_list_int_node *curr = lli_seek(l, idx - 1);
    linked_list_int_node *new_node = lli_new_node(data);
    new_node->next = curr->next;
    curr->next = new_node;
    l->len++;
}

int lli_pop_front(linked_list_int *l) {
    assert(l != NULL);
    assert(l->head != NULL);
    int out = l->head->data;
    linked_list_int_node *next = l->head->next;
    free(l->head);
    l->len--;
    if (l->len == 0) {
        l->tail = NULL;
    }
    l->head = next;
    return out;
}

int lli_pop_back(linked_list_int *l) {
    assert(l != NULL);
    assert(l->tail != NULL);
    int out = l->tail->data;
    linked_list_int_node *tail = l->tail;
    if (l->len == 1) {
        l->head = NULL;
        l->tail = NULL;
    } else {
        linked_list_int_node *prev = lli_seek(l, l->len - 2);
        prev->next = NULL;
        l->tail = prev;
    }
    free(tail);
    l->len--;
    return out;
}

int lli_remove_at(linked_list_int *l, size_t idx) {
    if (idx == 0) {
        return lli_pop_front(l);
    }
    if (idx == l->len - 1) {
        return lli_pop_back(l);
    }
    linked_list_int_node *prev = lli_seek(l, idx - 1);
    assert(prev->next != NULL);
    linked_list_int_node *curr = prev->next;
    int out = curr->data;
    prev->next = curr->next;
    free(curr);
    l->len--;
    return out;
}

void lli_print(const linked_list_int *l) {
    printf("[ ");
    if (l->head != NULL) {
        linked_list_int_node *curr;
        for (curr = l->head; curr != NULL; curr = curr->next) {
            printf("%d ", curr->data);
        }
    }
    printf("]; len = %d\n", l->len);
}

int lli_peek_front(const linked_list_int *l) {
    assert(l != NULL);
    assert(l->head != NULL);
    return l->head->data;
}

int lli_peek_back(const linked_list_int *l) {
    assert(l != NULL);
    assert(l->tail != NULL);
    return l->tail->data;
}

int lli_peek_at(const linked_list_int *l, size_t idx) {
    const linked_list_int_node *curr = lli_seek(l, idx);
    return curr->data;
}

void lli_test(void) {
    // creation
    linked_list_int *l = lli_new();
    int foo;
    assert(l != NULL);
    assert(l->len == 0);
    assert(l->head == NULL);
    assert(l->tail == NULL);

    // push
    lli_push_front(l, 2);
    assert(l->len == 1);
    assert(l->head != NULL);
    assert(l->tail != NULL);
    assert(l->head->data == 2);
    assert(l->tail->data == 2);
    foo = lli_peek_front(l);
    assert(foo == 2);
    foo = lli_peek_back(l);
    assert(foo == 2);

    lli_push_back(l, 1);
    assert(l->len == 2);
    assert(l->head != NULL);
    assert(l->tail != NULL);
    assert(l->head->data == 2);
    assert(l->tail->data == 1);
    foo = lli_peek_front(l);
    assert(foo == 2);
    foo = lli_peek_back(l);
    assert(foo == 1);

    lli_push_back(l, 3);
    assert(l->len == 3);
    assert(l->head != NULL);
    assert(l->tail != NULL);
    assert(l->head->data == 2);
    assert(l->tail->data == 3);
    foo = lli_peek_front(l);
    assert(foo == 2);
    foo = lli_peek_back(l);
    assert(foo == 3);

    // pop
    foo = lli_pop_front(l);
    assert(l->len == 2);
    assert(foo == 2);
    foo = lli_peek_front(l);
    assert(foo == 1);
    foo = lli_peek_back(l);
    assert(foo == 3);

    foo = lli_pop_back(l);
    assert(l->len == 1);
    assert(foo == 3);
    foo = lli_peek_front(l);
    assert(foo == 1);
    foo = lli_peek_back(l);
    assert(foo == 1);

    // insert_at
    lli_insert_at(l, 2, 0);
    foo = lli_peek_at(l, 0);
    assert(foo == 2);

    lli_insert_at(l, 3, 1);
    foo = lli_peek_at(l, 1);
    assert(foo == 3);

    lli_insert_at(l, 4, 2);
    foo = lli_peek_at(l, 2);
    assert(foo == 4);

    // // remove_at
    foo = lli_remove_at(l, 1);
    assert(foo == 3);
    foo = lli_remove_at(l, 2);
    assert(foo == 1);
    foo = lli_remove_at(l, 0);
    assert(foo == 2);

    lli_free(l);
    printf("Finished LinkedList tests!\n");
}
