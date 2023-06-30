// Package list funcs
package list

import (
	"bytes"
	"errors"
	"fmt"
	"strings"
)

type Node[T any] struct {
	Value T
	next  *Node[T]
	prev  *Node[T]
}

// List double linked list
type List[T comparable] struct {
	Head   *Node[T]
	Tail   *Node[T]
	Length int
}

// NewList create a new empty list
func NewList[T comparable]() List[T] {
	return List[T]{Head: nil, Tail: nil, Length: 0}
}

// PeekFront returns copy of value at head or an error
func (l *List[T]) PeekFront() (T, error) {
	if l.Head == nil {
		return *new(T), errors.New("cannot peek at empty list")
	}
	return l.Head.Value, nil
}

// PeekBack returns copy of value at tail or an error
func (l *List[T]) PeekBack() (T, error) {
	if l.Tail == nil {
		return *new(T), errors.New("cannot peek at empty list")
	}
	return l.Tail.Value, nil
}

// PushFront push new val to the front of the list
func (l *List[T]) PushFront(val T) {
	newNode := Node[T]{Value: val, next: l.Head, prev: nil}
	l.Length++
	if l.Head == nil && l.Tail == nil {
		l.Tail = &newNode
	}
	if l.Head != nil {
		l.Head.prev = &newNode
	}
	l.Head = &newNode
}

// PushBack push new val to the back of the list
func (l *List[T]) PushBack(val T) {
	newNode := Node[T]{Value: val, next: nil, prev: l.Tail}
	l.Length++
	if l.Head == nil && l.Tail == nil {
		l.Head = &newNode
	}
	if l.Tail != nil {
		l.Tail.next = &newNode
	}
	l.Tail = &newNode
}

// PopFront pop the front of the list and return the value, unless the list is empty
func (l *List[T]) PopFront() (T, error) {
	if l.Head == nil {
		return *new(T), errors.New("cannot pop of empty list")
	}
	val := l.Head.Value
	if l.Head.next != nil {
		l.Head.next.prev = nil
		l.Head = l.Head.next
	} else {
		// this is the last element
		l.Head = nil
		l.Tail = nil
	}
	l.Length--
	return val, nil
}

// PopBack pop the back of the list and return the value, unless the list is empty
func (l *List[T]) PopBack() (T, error) {
	if l.Tail == nil {
		return *new(T), errors.New("cannot peek at empty list")
	}
	val := l.Tail.Value
	if l.Tail.prev != nil {
		l.Tail = l.Tail.prev
		l.Tail.next = nil
	} else {
		// this is the last element
		l.Head = nil
		l.Tail = nil
	}
	l.Length--
	return val, nil
}

// InsertAt inserts value at index; may return an error
func (l *List[T]) InsertAt(val T, idx int) error {
	if idx > l.Length {
		return errors.New("cannot insert out of bounds of list")
	} else if idx == l.Length {
		l.PushBack(val)
		return nil
	} else if idx == 0 {
		l.PushFront(val)
		return nil
	}
	l.Length++

	// find node in front of idx
	currentNode := l.Head
	for i := 0; i < idx; i++ {
		currentNode = currentNode.next
	}
	// attach new node first...
	newNode := Node[T]{Value: val, next: currentNode.next, prev: currentNode}

	// ... then break old links
	currentNode.prev.next = &newNode
	currentNode.prev = &newNode
	return nil
}

// Remove finds the value and removes it from the list
func (l *List[T]) Remove(val T) error {
	if l.Length == 0 {
		return errors.New("cannot remove items from an empty list")
		// the else if l.head.value == val will be handled by the for loop directly
	} else if l.Tail.Value == val {
		l.PopBack()
	}

	l.Length--
	currentNode, err := l.find(val)
  if err != nil {
    return err
  }

	prevNode := currentNode.prev
	nextNode := currentNode.next
	currentNode.prev.next = nextNode
	currentNode.next.prev = prevNode

	if currentNode == l.Head {
		l.Head = currentNode.next
	}
	if currentNode == l.Tail {
		l.Tail = currentNode.prev
	}

	// now that nothing is pointing at currentNode anymore, we need to make sure that currentNode isn't pointing
	// to anything either
	currentNode.next = nil
	currentNode.prev = nil

	// now currentNode will be swept by the GC

	return nil
}

// Get returns a copy of the element at idx, or an error
func (l *List[T]) Get(idx int) (T, error) {
  node, err := l.findAt(idx)
  return node.Value, err
}

// RemoveAt removes element at idx returns the value of that element, unless an error ocurred
func (l *List[T]) RemoveAt(idx int) (T, error) {
  currentNode, err := l.findAt(idx)
  if err != nil {
    return *new(T), err
  }

  if idx == 0 {
    return l.PopFront()
  } else if idx == l.Length-1 {
    return l.PopBack()
  }

  l.Length--

  prevNode := currentNode.prev
  nextNode := currentNode.next
  val := currentNode.Value

  prevNode.next = nextNode
  nextNode.prev = prevNode
  currentNode.prev = nil
  currentNode.next = nil

  return val, nil
}

func (l *List[T]) find(val T) (*Node[T], error) {
  currentNode := l.Head
  for currentNode != nil {
    if currentNode.Value == val {
      break
    }
    currentNode = currentNode.next
  }
  if currentNode == nil {
    return *new(*Node[T]), errors.New("unable to find value in list")
  }
  return currentNode, nil
}

func (l *List[T]) findAt(idx int) (*Node[T], error) {
  currentNode := l.Head
  if currentNode == nil {
    return *new(*Node[T]), errors.New("list is empty")
  } else if idx < l.Length {
    return *new(*Node[T]), errors.New("idx out of bounds")
  }

  if idx == l.Length-1 {
    return l.Tail, nil
  } else if idx == 0 {
    return l.Head, nil
  }

  for i := 0; currentNode != nil && i <= idx; i++ {
    currentNode = currentNode.next
  }
  return currentNode, nil
}

// ToString Convert the list to a string
func (l *List[T]) ToString() string {
	var buf bytes.Buffer
	buf.WriteString("[ ")
	n := l.Head
	for n != nil {
		buf.WriteString(fmt.Sprintf("%v ", n.Value))
		n = n.next
	}
	buf.WriteString("]\n")
	return strings.TrimSpace(buf.String())
}
