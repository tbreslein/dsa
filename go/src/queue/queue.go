// Package queue funcs
package queue

import "github.com/tbreslein/fem-dsa/src/list"

// Queue FIFO list structure
type Queue[T comparable] struct {
	List *list.List[T]
}

// NewQueue Construct a new queue
func NewQueue[T comparable]() Queue[T] {
	list := list.NewList[T]()
	return Queue[T]{List: &list}
}

// Push push a value into the queue
func (q *Queue[T]) Push(val T) {
	q.List.PushBack(val)
}

// Pop pop a value of the queue
func (q *Queue[T]) Pop() (T, error) {
	return q.List.PopFront()
}

// Peek returns a copy of the value at the front of the queue, unless the queue is empty
func (q *Queue[T]) Peek() (T, error) {
	return q.List.PeekFront()
}

// Length returns the length of the queue
func (q *Queue[T]) Length() int {
	return q.List.Length
}

// ToString convert the queue to a string
func (q *Queue[T]) ToString() string {
	return q.List.ToString()
}
