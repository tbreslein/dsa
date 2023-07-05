#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma once

typedef struct RingBufferInt {
    size_t len;
    size_t capacity;
    size_t start;
    size_t end;
    int *arr;
} ring_buffer_int;

ring_buffer_int *rbi_new(size_t cap) {
    ring_buffer_int *r = (ring_buffer_int *)malloc(sizeof(ring_buffer_int));
    assert(r != NULL);
    r->len = 0;
    r->capacity = cap;
    r->start = 0;
    r->end = 0;
    r->arr = (int *)malloc(cap * sizeof(int));
    return r;
}

void rbi_free(ring_buffer_int *r) {
    if (r == NULL) {
        return;
    }
    free(r->arr);
    free(r);
    return;
}

void rbi_grow(ring_buffer_int *r) {
    r->arr = (int *)realloc(r->arr, 2 * r->capacity * sizeof(int));
    r->capacity *= 2;
}

void rbi_push(ring_buffer_int **r, int data) {
    if ((*r)->len >= (*r)->capacity) {
        rbi_grow(*r);
    }
    (*r)->arr[(*r)->len] = data;
    (*r)->len++;
}

int rbi_pop(ring_buffer_int **r) {
    (*r)->len--;
    return (*r)->arr[(*r)->len];
}

void rbi_set(ring_buffer_int **r, size_t idx, int data) {
    assert(idx < (*r)->len);
    (*r)->arr[idx] = data;
}

int rbi_get(ring_buffer_int **r, size_t idx) {
    assert(idx < (*r)->len);
    return (*r)->arr[idx];
}

void rbi_insert(ring_buffer_int **r, size_t idx, int data) {
    assert(idx <= (*r)->len);
    if (idx == (*r)->len) {
        return rbi_push(r, data);
    }
    if ((*r)->len >= (*r)->capacity) {
        rbi_grow(*r);
    }
    memmove((*r)->arr + idx + 1, (*r)->arr + idx, (*r)->len - idx);
    (*r)->arr[idx] = data;
    (*r)->len++;
}

int rbi_remove(ring_buffer_int **r, size_t idx) {
    assert(idx < (*r)->len);
    if (idx == (*r)->len - 1) {
        return rbi_pop(r);
    }
    int out = (*r)->arr[idx];
    memmove((*r)->arr + idx, (*r)->arr + idx + 1, (*r)->len - idx);
    (*r)->len--;
    return out;
}

void rbi_print(ring_buffer_int **r) {
    fprintf(stdout, "[ ");
    for (size_t i = 0; i < (*r)->len; i++) {
        fprintf(stdout, "%d ", (*r)->arr[i]);
    }
    fprintf(stdout, "]\n");
}

void rbi_test() {
    // creation
    ring_buffer_int *r = rbi_new(1);
    int foo;
    // assert(r != NULL);
    // assert(r->len == 0);
    // assert(r->capacity == 1);
    // assert(r->arr != 0);
    //
    // // push
    // rbi_push(&r, 2);
    // assert(r->len == 1);
    // assert(r->capacity == 1);
    // foo = rbi_get(&r, 0);
    // assert(foo == 2);
    //
    // rbi_push(&r, 1);
    // assert(r->len == 2);
    // assert(r->capacity == 2);
    // foo = rbi_get(&r, 0);
    // assert(foo == 2);
    // foo = rbi_get(&r, 1);
    // assert(foo == 1);
    //
    // // insert
    // rbi_insert(&r, 1, 3);
    // assert(r->len == 3);
    // assert(r->capacity == 4);
    // foo = rbi_get(&r, 0);
    // assert(foo == 2);
    // foo = rbi_get(&r, 1);
    // assert(foo == 3);
    // foo = rbi_get(&r, 2);
    // assert(foo == 1);
    //
    // // set
    // rbi_set(&r, 2, 4);
    // assert(r->len == 3);
    // foo = rbi_get(&r, 0);
    // assert(foo == 2);
    // foo = rbi_get(&r, 1);
    // assert(foo == 3);
    // foo = rbi_get(&r, 2);
    // assert(foo == 4);
    //
    // // remove
    // rbi_print(&r);
    // foo = rbi_remove(&r, 1);
    // rbi_print(&r);
    // assert(foo == 3);
    // assert(r->len == 2);
    // foo = rbi_get(&r, 0);
    // assert(foo == 2);
    // foo = rbi_get(&r, 1);
    // assert(foo == 4);
    //
    // // pop
    // foo = rbi_pop(&r);
    // assert(foo == 4);
    // assert(r->len == 1);
    // foo = rbi_pop(&r);
    // assert(foo == 2);
    // assert(r->len == 0);

    rbi_free(r);
    printf("Finished RingBuffer tests!\n");
}
