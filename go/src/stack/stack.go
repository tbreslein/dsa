// Package stack funcs
package stack

import "github.com/tbreslein/fem-dsa/src/list"

// Stack simple LIFO list structure
type Stack[T comparable] struct {
	List *list.List[T]
}

// NewStack construct a new stack
func NewStack[T comparable]() Stack[T] {
	list := list.NewList[T]()
	return Stack[T]{List: &list}
}

// Push push value to the top of the stack
func (s *Stack[T]) Push(val T) {
	s.List.PushFront(val)
}

// Pop pop value of the top of the stack, unless the stack is empty
func (s *Stack[T]) Pop() (T, error) {
	return s.List.PopFront()
}

// Peek return a copy of the value at the top of the stack, unless the stack is empty
func (s *Stack[T]) Peek() (T, error) {
	return s.List.PeekFront()
}

// Length returns the length of the queue
func (s *Stack[T]) Length() int {
	return s.List.Length
}

// ToString converts the stack to a string
func (s *Stack[T]) ToString() string {
	return s.List.ToString()
}
