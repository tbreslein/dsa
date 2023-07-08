#include "arraybuffer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once

typedef struct MinHeapInt {
    array_buffer_int *arr;
} min_heap_int;

min_heap_int *mhi_new(size_t cap) {
    min_heap_int *h = (min_heap_int *)malloc(sizeof(min_heap_int));
    assert(h != NULL);
    h->arr = abi_new(cap);
    return h;
}

void mhi_free(min_heap_int *h) {
    if (h == NULL) {
        return;
    }
    free(h->arr);
    free(h);
    return;
}

size_t mhi_parent(size_t idx) {
    assert(idx > 0);
    return (idx - 1) / 2;
}

void mhi_swap(min_heap_int *h, size_t idx1, size_t idx2) {
    int temp = abi_get(h->arr, idx1);
    abi_set(h->arr, idx1, abi_get(h->arr, idx2));
    abi_set(h->arr, idx2, temp);
}

size_t mhi_left_child(size_t idx) { return 1 + 2 * idx; }
size_t mhi_right_child(size_t idx) { return 2 + 2 * idx; }

void mhi_heapify_up(min_heap_int *h, size_t idx) {
    if (idx == 0) {
        return;
    }
    const size_t parent_idx = mhi_parent(idx);
    if (abi_get(h->arr, parent_idx) > abi_get(h->arr, idx)) {
        mhi_swap(h, idx, parent_idx);
        mhi_heapify_up(h, parent_idx);
    }
}

void mhi_heapify_down(min_heap_int *h, size_t idx) {
    const size_t left_child_idx = mhi_left_child(idx);
    const size_t right_child_idx = mhi_right_child(idx);
    if (idx > h->arr->len || left_child_idx >= h->arr->len) {
        return;
    }
    const int left_val = abi_get(h->arr, left_child_idx);
    const int this_val = abi_get(h->arr, idx);
    if (right_child_idx >= h->arr->len) {
        if (this_val > left_val) {
            mhi_swap(h, idx, left_child_idx);
            mhi_heapify_down(h, left_child_idx);
        }
        return;
    }
    const int right_val = abi_get(h->arr, right_child_idx);
    if (left_val > right_val && this_val > right_val) {
        mhi_swap(h, idx, right_child_idx);
        mhi_heapify_down(h, right_child_idx);
    } else if (right_val > left_val && this_val > left_val) {
        mhi_swap(h, idx, left_child_idx);
        mhi_heapify_down(h, left_child_idx);
    }
}

void mhi_insert(min_heap_int *h, int data) {
    if (h->arr->len >= h->arr->capacity) {
        abi_grow(h->arr);
    }
    abi_push(h->arr, data);
    mhi_heapify_up(h, h->arr->len - 1);
}

int mhi_pop(min_heap_int *h) {
    assert(h->arr->len > 0);
    const int out = abi_get(h->arr, 0);
    const int temp = abi_pop(h->arr);
    if (h->arr->len > 0) {
        abi_set(h->arr, 0, temp);
        mhi_heapify_down(h, 0);
    }
    return out;
}

int mhi_peek(min_heap_int *h) { return abi_get(h->arr, 0); }

void mhi_test(void) {
    min_heap_int *h = mhi_new(2);
    int foo;

    mhi_insert(h, 10);
    foo = mhi_peek(h);
    assert(foo == 10);

    mhi_insert(h, 12);
    foo = mhi_peek(h);
    assert(foo == 10);

    mhi_insert(h, 7);
    foo = mhi_peek(h);
    assert(foo == 7);

    mhi_insert(h, 11);
    foo = mhi_peek(h);
    assert(foo == 7);

    mhi_insert(h, 13);
    foo = mhi_peek(h);
    assert(foo == 7);

    mhi_insert(h, 2);
    foo = mhi_peek(h);
    assert(foo == 2);

    foo = mhi_pop(h);
    assert(foo == 2);

    foo = mhi_pop(h);
    assert(foo == 7);

    mhi_insert(h, 5);
    foo = mhi_peek(h);
    assert(foo == 5);

    foo = mhi_pop(h);
    assert(foo == 5);

    foo = mhi_pop(h);
    assert(foo == 10);

    foo = mhi_pop(h);
    assert(foo == 11);

    foo = mhi_pop(h);
    assert(foo == 12);

    foo = mhi_pop(h);
    assert(foo == 13);

    mhi_free(h);
    printf("Finished MinHeap tests!\n");
}
