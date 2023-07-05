#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma once

typedef struct ArrayBufferInt {
    size_t len;
    size_t capacity;
    int *arr;
} array_buffer_int;

array_buffer_int *abi_new(size_t cap) {
    array_buffer_int *a = (array_buffer_int *)malloc(sizeof(array_buffer_int));
    assert(a != NULL);
    a->len = 0;
    a->capacity = cap;
    a->arr = (int *)malloc(cap * sizeof(int));
    return a;
}

void abi_free(array_buffer_int *a) {
    if (a == NULL) {
        return;
    }
    free(a->arr);
    free(a);
    return;
}

void abi_grow(array_buffer_int *a) {
    a->capacity *= 2;
    a->arr = (int *)realloc(a->arr, a->capacity * sizeof(int));
}

void abi_push(array_buffer_int **a, int data) {
    if ((*a)->len >= (*a)->capacity) {
        abi_grow(*a);
    }
    (*a)->arr[(*a)->len] = data;
    (*a)->len++;
}

int abi_pop(array_buffer_int **a) {
    (*a)->len--;
    return (*a)->arr[(*a)->len];
}

void abi_set(array_buffer_int **a, size_t idx, int data) {
    assert(idx < (*a)->len);
    (*a)->arr[idx] = data;
}

int abi_get(array_buffer_int **a, size_t idx) {
    assert(idx < (*a)->len);
    return (*a)->arr[idx];
}

void abi_insert(array_buffer_int **a, size_t idx, int data) {
    assert(idx <= (*a)->len);
    if (idx == (*a)->len) {
        return abi_push(a, data);
    }
    if ((*a)->len >= (*a)->capacity) {
        abi_grow(*a);
    }
    memmove((*a)->arr + idx + 1, (*a)->arr + idx, (*a)->len - idx);
    (*a)->arr[idx] = data;
    (*a)->len++;
}

int abi_remove(array_buffer_int **a, size_t idx) {
    assert(idx < (*a)->len);
    if (idx == (*a)->len - 1) {
        return abi_pop(a);
    }
    int out = (*a)->arr[idx];
    memmove((*a)->arr + idx, (*a)->arr + idx + 1, (*a)->len - idx);
    (*a)->len--;
    return out;
}

void abi_print(array_buffer_int **a) {
    fprintf(stdout, "[ ");
    for (size_t i = 0; i < (*a)->len; i++) {
        fprintf(stdout, "%d ", (*a)->arr[i]);
    }
    fprintf(stdout, "]\n");
}

void abi_test() {
    // creation
    array_buffer_int *a = abi_new(1);
    int foo;
    assert(a != NULL);
    assert(a->len == 0);
    assert(a->capacity == 1);
    assert(a->arr != 0);

    // push
    abi_push(&a, 2);
    assert(a->len == 1);
    assert(a->capacity == 1);
    foo = abi_get(&a, 0);
    assert(foo == 2);

    abi_push(&a, 1);
    assert(a->len == 2);
    assert(a->capacity == 2);
    foo = abi_get(&a, 0);
    assert(foo == 2);
    foo = abi_get(&a, 1);
    assert(foo == 1);

    // insert
    abi_insert(&a, 1, 3);
    assert(a->len == 3);
    assert(a->capacity == 4);
    foo = abi_get(&a, 0);
    assert(foo == 2);
    foo = abi_get(&a, 1);
    assert(foo == 3);
    foo = abi_get(&a, 2);
    assert(foo == 1);

    // set
    abi_set(&a, 2, 4);
    assert(a->len == 3);
    foo = abi_get(&a, 0);
    assert(foo == 2);
    foo = abi_get(&a, 1);
    assert(foo == 3);
    foo = abi_get(&a, 2);
    assert(foo == 4);

    // remove
    foo = abi_remove(&a, 1);
    assert(foo == 3);
    assert(a->len == 2);
    foo = abi_get(&a, 0);
    assert(foo == 2);
    foo = abi_get(&a, 1);
    assert(foo == 4);

    // pop
    foo = abi_pop(&a);
    assert(foo == 4);
    assert(a->len == 1);
    foo = abi_pop(&a);
    assert(foo == 2);
    assert(a->len == 0);

    abi_free(a);
    printf("Finished ArrayBuffer tests!\n");
}
