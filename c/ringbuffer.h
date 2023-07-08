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

ring_buffer_int *rbi_new(void) {
    const size_t cap = 2;
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
    const size_t new_cap = 2 * r->capacity;
    r->arr = (int *)realloc(r->arr, new_cap * sizeof(int));
    if (r->start > r->end) {
        const size_t n_to_move = r->capacity - r->start;
        const size_t new_start = new_cap - n_to_move;
        memmove(r->arr + new_start, r->arr + r->start, n_to_move * sizeof(int));
        r->start = new_start;
    }
    r->capacity = new_cap;
}

void rbi_clear(ring_buffer_int *r) {
    r->len = 0;
    r->start = 0;
    r->end = 0;
}

size_t rbi_idx(const ring_buffer_int *r, size_t idx) {
    assert(idx < r->len);
    return (r->start + idx) % r->capacity;
}

void rbi_set(ring_buffer_int *r, size_t idx, int data) {
    assert(idx < r->len);
    r->arr[rbi_idx(r, idx)] = data;
}

int rbi_get(ring_buffer_int *r, size_t idx) {
    assert(idx < r->len);
    return r->arr[rbi_idx(r, idx)];
}

void rbi_push_back(ring_buffer_int *r, int data) {
    if (r->len + 2 > r->capacity) {
        rbi_grow(r);
    }
    r->arr[r->end] = data;
    r->end = (r->end + 1) % r->capacity;
    r->len++;
}

void rbi_push_front(ring_buffer_int *r, int data) {
    if (r->len + 2 > r->capacity) {
        rbi_grow(r);
    }
    r->start = r->start == 0 ? r->capacity - 1 : r->start - 1;
    r->arr[r->start] = data;
    r->len++;
}

int rbi_pop_back(ring_buffer_int *r) {
    int out = r->arr[r->end];
    r->end = r->end == 0 ? r->capacity - 1 : r->end - 1;
    r->len--;
    return out;
}

int rbi_pop_front(ring_buffer_int *r) {
    int out = r->arr[r->start];
    r->start = (r->start + 1) % r->capacity;
    r->len--;
    return out;
}

void rbi_insert(ring_buffer_int *r, size_t idx, int data) {
    assert(idx <= r->len);
    if (r->len + 2 > r->capacity) {
        rbi_grow(r);
    }
    if (idx == 0) {
        return rbi_push_front(r, data);
    }
    if (idx == r->len) {
        return rbi_push_back(r, data);
    }
    const size_t real_idx = rbi_idx(r, idx);
    if (r->start > r->end && real_idx > r->start) {
        // in this case, we need to wrap elements around the edge

        // first: make room at the beginning of the buffer
        memmove(r->arr + 1, r->arr, (r->end) * sizeof(int));

        // second: move the element at the end of the buffer over the edge
        memcpy(r->arr, r->arr + r->capacity - 1, sizeof(int));

        // third: move the remaining elements up
        const size_t n_to_move = r->capacity - real_idx - 1;
        memmove(r->arr + real_idx + 1, r->arr + real_idx, n_to_move * sizeof(int));
    } else {
        // in this case we just need to move a couple of elements near the
        // beginning of the list up
        const size_t n_to_move = r->end - real_idx;
        memmove(r->arr + real_idx + 1, r->arr + real_idx, n_to_move * sizeof(int));
    }
    // either way, we can now safely set data into the correct slot
    r->arr[real_idx] = data;
    r->end = (r->end + 1) % r->capacity;
    r->len++;
}

int rbi_remove(ring_buffer_int *r, size_t idx) {
    assert(idx < r->len);
    if (idx == 0) {
        return rbi_pop_front(r);
    } else if (idx == r->len - 1) {
        return rbi_pop_back(r);
    }
    const size_t real_idx = rbi_idx(r, idx);
    int out = r->arr[real_idx];
    if (r->start > r->end && real_idx > r->start) {
        // in this case, we need to wrap elements around the edge

        // first: make room at the end of the buffer
        const size_t n_to_move = r->capacity - real_idx - 1;
        memmove(r->arr + real_idx, r->arr + real_idx + 1, n_to_move * sizeof(int));

        // second: move the element at the beginning of the buffer over the edge
        memcpy(r->arr + r->capacity - 1, r->arr, sizeof(int));

        // third: move the remaining elements down
        memmove(r->arr, r->arr + 1, r->end * sizeof(int));
    } else {
        // in this case we just need to move a couple of elements near the
        // beginning of the list down
        const size_t n_to_move = r->end - real_idx - 1;
        memmove(r->arr + real_idx, r->arr + real_idx + 1, n_to_move * sizeof(int));
    }
    r->end = r->end == 0 ? r->capacity - 1 : r->end - 1;
    r->len--;
    return out;
}

void rbi_print(ring_buffer_int *r) {
    fprintf(stdout, "virtual array = [ ");
    for (size_t i = 0; i < r->len; i++) {
        fprintf(stdout, "%d ", r->arr[rbi_idx(r, i)]);
    }
    fprintf(stdout, "]\n");
}

void rbi_print_arr(ring_buffer_int *r) {
    fprintf(stdout, "real array = [ ");
    for (size_t i = 0; i < r->capacity; i++) {
        fprintf(stdout, "%d ", r->arr[i]);
    }
    fprintf(stdout, "]\n");
}

void rbi_test(void) {
    // creation
    ring_buffer_int *r = rbi_new();
    int foo;
    assert(r != NULL);
    assert(r->len == 0);
    assert(r->start == 0);
    assert(r->end == 0);
    assert(r->capacity == 2);
    assert(r->arr != NULL);

    rbi_push_front(r, 1);
    foo = rbi_get(r, 0);
    assert(foo == 1);
    assert(r->start == 1);
    assert(r->end == 0);
    assert(r->len == 1);
    assert(r->capacity == 2);

    rbi_pop_front(r);
    assert(r->start == 0);
    assert(r->end == 0);
    assert(r->len == 0);
    assert(r->capacity == 2);

    rbi_push_front(r, 2);
    foo = rbi_get(r, 0);
    assert(foo == 2);
    assert(r->start == 1);
    assert(r->end == 0);
    assert(r->len == 1);
    assert(r->capacity == 2);

    rbi_push_front(r, 3);
    foo = rbi_get(r, 0);
    assert(foo == 3);
    foo = rbi_get(r, 1);
    assert(foo == 2);
    assert(r->start == 2);
    assert(r->end == 0);
    assert(r->len == 2);
    assert(r->capacity == 4);

    rbi_push_front(r, 4);
    foo = rbi_get(r, 0);
    assert(foo == 4);
    foo = rbi_get(r, 1);
    assert(foo == 3);
    foo = rbi_get(r, 2);
    assert(foo == 2);
    assert(r->start == 1);
    assert(r->end == 0);
    assert(r->len == 3);
    assert(r->capacity == 4);

    rbi_clear(r);
    assert(r->start == 0);
    assert(r->end == 0);
    assert(r->len == 0);
    assert(r->capacity == 4);

    rbi_push_back(r, 2);
    foo = rbi_get(r, 0);
    assert(foo == 2);
    assert(r->start == 0);
    assert(r->end == 1);
    assert(r->len == 1);
    assert(r->capacity == 4);

    rbi_push_back(r, 3);
    foo = rbi_get(r, 0);
    assert(foo == 2);
    foo = rbi_get(r, 1);
    assert(foo == 3);
    assert(r->start == 0);
    assert(r->end == 2);
    assert(r->len == 2);
    assert(r->capacity == 4);

    rbi_push_back(r, 4);
    foo = rbi_get(r, 0);
    assert(foo == 2);
    foo = rbi_get(r, 1);
    assert(foo == 3);
    foo = rbi_get(r, 2);
    assert(foo == 4);
    assert(r->start == 0);
    assert(r->end == 3);
    assert(r->len == 3);
    assert(r->capacity == 4);

    rbi_push_front(r, 5);
    foo = rbi_get(r, 0);
    assert(foo == 5);
    foo = rbi_get(r, 1);
    assert(foo == 2);
    foo = rbi_get(r, 2);
    assert(foo == 3);
    foo = rbi_get(r, 3);
    assert(foo == 4);
    assert(r->start == 7);
    assert(r->end == 3);
    assert(r->len == 4);
    assert(r->capacity == 8);

    rbi_push_front(r, 6);
    foo = rbi_get(r, 0);
    assert(foo == 6);
    foo = rbi_get(r, 1);
    assert(foo == 5);
    foo = rbi_get(r, 2);
    assert(foo == 2);
    foo = rbi_get(r, 3);
    assert(foo == 3);
    foo = rbi_get(r, 4);
    assert(foo == 4);
    assert(r->start == 6);
    assert(r->end == 3);
    assert(r->len == 5);
    assert(r->capacity == 8);

    rbi_insert(r, 3, 7);
    foo = rbi_get(r, 0);
    assert(foo == 6);
    foo = rbi_get(r, 1);
    assert(foo == 5);
    foo = rbi_get(r, 2);
    assert(foo == 2);
    foo = rbi_get(r, 3);
    assert(foo == 7);
    foo = rbi_get(r, 4);
    assert(foo == 3);
    foo = rbi_get(r, 5);
    assert(foo == 4);
    assert(r->start == 6);
    assert(r->end == 4);
    assert(r->len == 6);
    assert(r->capacity == 8);

    rbi_remove(r, 3);
    foo = rbi_get(r, 0);
    assert(foo == 6);
    foo = rbi_get(r, 1);
    assert(foo == 5);
    foo = rbi_get(r, 2);
    assert(foo == 2);
    foo = rbi_get(r, 3);
    assert(foo == 3);
    foo = rbi_get(r, 4);
    assert(foo == 4);
    assert(r->start == 6);
    assert(r->end == 3);
    assert(r->len == 5);
    assert(r->capacity == 8);

    rbi_insert(r, 1, 7);
    foo = rbi_get(r, 0);
    assert(foo == 6);
    foo = rbi_get(r, 1);
    assert(foo == 7);
    foo = rbi_get(r, 2);
    assert(foo == 5);
    foo = rbi_get(r, 3);
    assert(foo == 2);
    foo = rbi_get(r, 4);
    assert(foo == 3);
    foo = rbi_get(r, 5);
    assert(foo == 4);
    assert(r->start == 6);
    assert(r->end == 4);
    assert(r->len == 6);
    assert(r->capacity == 8);

    rbi_remove(r, 1);
    foo = rbi_get(r, 0);
    assert(foo == 6);
    foo = rbi_get(r, 1);
    assert(foo == 5);
    foo = rbi_get(r, 2);
    assert(foo == 2);
    foo = rbi_get(r, 3);
    assert(foo == 3);
    foo = rbi_get(r, 4);
    assert(foo == 4);
    assert(r->start == 6);
    assert(r->end == 3);
    assert(r->len == 5);
    assert(r->capacity == 8);

    rbi_free(r);
    printf("Finished RingBuffer tests!\n");
}
