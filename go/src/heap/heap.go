// Package heap funcs
package heap

import "golang.org/x/exp/constraints"

import (
	"errors"
)

/// MinHeap heap that always keeps a weak ordering making access to the smallest element in the data structure O(1).
///
/// Implemented as an array under the hood, turning operations between parents and children into operations on indeces.
type MinHeap[T constraints.Ordered] struct{
  data []T;
}

func New[T constraints.Ordered]() MinHeap[T] {
  return MinHeap[T]{[]T{}}
}

func (h *MinHeap[T]) Peek(val T) T {
  return h.data[0]
}

func (h *MinHeap[T]) Insert(val T) {
  h.data = append(h.data, val)
  h.heapifyUp(len(h.data) - 1)
  // h.length++ // handled by the slice itself
}

func (h *MinHeap[T]) Pop() (T, error) {
  // h.length-- // handled by the slice itself
  if len(h.data) == 0 {
    return *new(T), errors.New("cannot pop off empty heap")
  }
  outVal := h.data[0]
  h.data[0] = h.data[len(h.data) - 1]
  h.data = h.data[:len(h.data)-1] // slice off the last element
  h.heapifyDown(0)
  return outVal, nil
}

func (h *MinHeap[T]) swap(idx1 int, idx2 int) {
  temp := h.data[idx1]
  h.data[idx1] = h.data[idx2]
  h.data[idx2] = temp
}

func (h *MinHeap[T]) parent(idx int) int {
  return (idx - 1) / 2
}

func (h *MinHeap[T]) children(idx int) (int, int) {
  child1 := 2 * idx + 1
  return child1, child1 + 1
}

func (h *MinHeap[T]) heapifyUp(idx int) {
  if idx == 0 {
    return
  }

  parentIdx := h.parent(idx)
  parentVal := h.data[parentIdx]
  thisVal := h.data[idx]

  if (parentVal > thisVal) {
    h.swap(idx, parentIdx)
    h.heapifyUp(parentIdx)
  }
}
func (h *MinHeap[T]) heapifyDown(idx int) {
  leftIdx, rightIdx := h.children(idx)

  if idx >= len(h.data) || leftIdx >= len(h.data) {
    return
  }

  leftVal := h.data[leftIdx]
  rightVal := h.data[rightIdx]
  thisVal := h.data[idx]

  // This can probably be refactored to just identify the smallest value directly and swap with that value's idx
  if leftVal > rightVal && thisVal > rightVal {
    // if rightVal is the smallest of the three values, we want it to bubble up
    h.swap(idx, rightIdx)
    h.heapifyDown(rightIdx)
  } else if rightVal > leftVal && thisVal > leftVal {
    // if leftVal is the smallest of the three values, we want it to bubble up
    h.swap(idx, leftIdx)
    h.heapifyDown(leftIdx)
  }
}
